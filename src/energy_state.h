#ifndef ENERGY_STATE
#define ENERGY_STATE
#include <chrono>
#include <map>
#include <string>
class EnergyState
{
public:
  std::chrono::time_point<std::chrono::system_clock> timestamp;
  std::map<std::string, unsigned long long> energies;
  EnergyState(std::chrono::time_point<std::chrono::system_clock> timestamp, std::map<std::string, unsigned long long> energies);
};

#endif