#include <cppJoules_exceptions.h>
#include <cppJoules.h>
#include <iostream>
#include <fstream>
#include <filesystem>
#include "rapl_devices.h"
#include "nvidia_devices.h"
#include "energy_state.h"

EnergyTracker::EnergyTracker()
{
  RAPL_device = new RAPLDevice();
  NVML_device = new NVMLDevice();
}

void EnergyTracker::start()
{
  /**
   * Getting both the RAPL and NVML Energies
   */
  if (state == STARTED)
  {
    std::cout << "Tracker already started" << std::endl;
    return;
  }
  auto start_time = std::chrono::high_resolution_clock::now();
  std::map<std::string, unsigned long long> start_energy;
  auto rapl_energy = RAPL_device->getEnergy();
  start_energy.insert(rapl_energy.begin(), rapl_energy.end());

  std::map<std::string, unsigned long long> nvidia_energy;
  /**
   * Check if nvml can be used
   */
  if (NVML_device->usable)
  {
    nvidia_energy = NVML_device->getEnergy();
    start_energy.insert(nvidia_energy.begin(), nvidia_energy.end());
  }
  EnergyState *energy = new EnergyState(start_time, start_energy);
  energy_readings.push_back(energy);
  state = STARTED;
}

void EnergyTracker::stop()
{
  if (state == UNINITIALIZED)
  {
    std::cout << "Tracker never started" << std::endl;
    return;
  }
  if (state == STOPPED)
  {
    std::cout << "Tracker already stopped" << std::endl;
    return;
  }
  auto end_time = std::chrono::high_resolution_clock::now();
  auto stop_energy = RAPL_device->getEnergy();
  std::map<std::string, unsigned long long> nvidia_energy;

  if (NVML_device->usable)
  {
    nvidia_energy = NVML_device->getEnergy();
    stop_energy.insert(nvidia_energy.begin(), nvidia_energy.end());
  }
  EnergyState *energy = new EnergyState(end_time, stop_energy);
  energy_readings.push_back(energy);
  state = STOPPED;
}

void EnergyTracker::calculate_energy()
{
  if (state == UNINITIALIZED)
  {
    std::cout << "Tracker never started" << std::endl;
    return;
  }
  if (state != STOPPED)
  {
    std::cout << "Stop tracker before calculating Energy" << std::endl;
    return;
  }
  last_calculated_energies.clear();
  last_calculated_time = 0;
  for (uint32_t i = 0; i < energy_readings.size() - 1; i += 2)
  {
    auto start = energy_readings[i];
    auto stop = energy_readings[i + 1];
    float delta_time = static_cast<std::chrono::duration<float>>(stop->timestamp - start->timestamp).count();

    if (start->energies.size() != stop->energies.size())
    {
      std::cout << "Readings are off" << std::endl;
      return;
    }
    last_calculated_time += delta_time;
    for (auto domain : start->energies)
    {
      /**
       * If the energy counter had reset, we have to add the max energy
       */
      // std::cout << (long long)stop->energies[domain.first] - (long long)domain.second << std::endl;
      if ((long long)stop->energies[domain.first] - (long long)domain.second < 0)
      {
#ifdef __linux__
        if (RAPL_device->max_energy_devices.count(domain.first))
        {
          std::ifstream Filehandler(RAPL_device->max_energy_devices[domain.first]);
          std::string energy_s;
          getline(Filehandler, energy_s);
          long long energy = std::stoll(energy_s);

          last_calculated_energies[domain.first] += stop->energies[domain.first] - domain.second + energy;
        }
#endif
      }
      else
      {
        last_calculated_energies[domain.first] += (stop->energies[domain.first] - domain.second);
      }
    }
  }
  energy_readings.clear();
}
void EnergyTracker::print_energy()
{
  if (last_calculated_energies.empty())
  {
    std::cout << "No Value to print" << std::endl;
  }
  std::cout << "Time " << last_calculated_time << "\n";
  for (auto energy : last_calculated_energies)
  {
    std::cout << energy.first << " " << energy.second << "\n";
  }
}

void EnergyTracker::save_csv(std::string file)
{
  std::ofstream csv_file(file);
  csv_file << "Time" << ",";
  for (auto energy : last_calculated_energies)
  {
    csv_file << energy.first << ",";
  }
  csv_file << "\n";
  csv_file << last_calculated_time << ",";
  for (auto energy : last_calculated_energies)
  {
    csv_file << energy.second << ",";
  }
  csv_file << "\n";
  csv_file.close();
}