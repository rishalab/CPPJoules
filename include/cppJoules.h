#ifndef CPP_JOULES
#define CPP_JOULES
#include <iostream>
#include <chrono>
#include <map>
#include <vector>

/**
 * Windows requires us to expose the classes in dlls
 */
#ifdef _WIN32
#define EXPOSE_DLL __declspec(dllexport)
#else
#define EXPOSE_DLL
#endif

/**
 * Forward Declarations
 */

class RAPLDevice;
class NVMLDevice;
class EnergyState;

enum TrackerState
{
  UNINITIALIZED,
  STARTED,
  STOPPED
};

class EXPOSE_DLL EnergyTracker
{
  /**
   * The energy tracker class. Contains the necessary
   * tools for tracking the energy.
   */
  RAPLDevice *RAPL_device;
  NVMLDevice *NVML_device;
  std::vector<EnergyState *> energy_readings;
  TrackerState state = UNINITIALIZED;
  std::map<std::string, long long> last_calculated_energies;
  float last_calculated_time;

public:
  EnergyTracker();
  void start();
  void stop();
  void calculate_energy();
  void print_energy();
  void save_csv(std::string file);
};
#endif