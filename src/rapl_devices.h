#ifndef RAPL_DEVICES
#define RAPL_DEVICES
#include <string>
#include <unordered_map>
#include <vector>
#include <map>

#ifdef _WIN32
#include "windows.h"
#define EXPOSE_DLL __declspec(dllexport)
#else
#define EXPOSE_DLL
#endif

class EXPOSE_DLL RAPLDevice
{
#ifdef _WIN64
  HINSTANCE handler;
#define RAPLDEVICETYPE std::unordered_map<std::string, std::pair<int, int>>
#elif __linux__
  std::string RAPL_API_PATH = "/sys/class/powercap/intel-rapl/";
#define RAPLDEVICETYPE std::unordered_map<std::string, std::string>
#elif __APPLE__
  void *handler;
#define RAPLDEVICETYPE std::unordered_map<std::string, std::pair<int, int>>
#endif
  std::string getName(std::string path);

public:
  RAPLDEVICETYPE devices;
#ifdef _W64
  bool initialized;
#endif
  std::unordered_map<std::string, std::string> max_energy_devices;
  std::map<std::string, unsigned long long> getEnergy();
  RAPLDevice();
};
#endif