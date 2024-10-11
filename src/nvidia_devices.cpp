#include "nvidia_devices.h"
#include <string>
#include <memory>
#include <iostream>
/**
 * Every function in the NVML API returns a STATUS CODE when run
 * We can procede only if the status code is NVML_SUCCESS
 */
/**
 * NVML Requires pointers to be passed for all APIs
 * Also dynamic loading nvml to make rapl usable even when
 * the nvml library is not available
 * */
typedef void (*nvmlfunction_void)();
typedef void (*nvmlfunction_uint32)(uint32_t *);
typedef void (*nvmlfunction_unit32_nvmlDevice)(uint32_t, nvmlDevice_t *);
typedef void (*nvmlfunction_nvmlDevice_unsignedlonglong)(nvmlDevice_t, unsigned long long *);

NVMLDevice::NVMLDevice()
{
  /**
   * In windows, the dll is found in the system32 folder.
   */
#ifdef _WIN64
  char tpath[MAX_PATH];
  GetSystemDirectoryA(tpath, MAX_PATH);
  // Directly building might not work, the string might be lost before applying .c_str
  std::string fullpath = std::string(tpath) + std::string("\\nvml.dll");
  const char *path = fullpath.c_str();

#endif
/**
 * In linux the so file is present in LD path
 */
#ifdef __linux__
  const char *path = PATH;
#endif

  nvmlhandle = OPENLIB(path);
  usable = true;
  if (!nvmlhandle)
  {
    std::cout << "Nvidia gpu not activated" << std::endl;
    usable = false;
    return;
  }
  /**
   * Getting the function pointers from the library
   */
  nvmlfunction_void _nvmlInit = reinterpret_cast<nvmlfunction_void>(GETFUNC(nvmlhandle, "nvmlInit_v2"));
  nvmlfunction_uint32 _nvmlDeviceGetCount = reinterpret_cast<nvmlfunction_uint32>(GETFUNC(nvmlhandle, "nvmlDeviceGetCount_v2"));
  nvmlfunction_unit32_nvmlDevice _nvmlDeviceGetHandleByIndex = reinterpret_cast<nvmlfunction_unit32_nvmlDevice>(GETFUNC(nvmlhandle, "nvmlDeviceGetHandleByIndex_v2"));
  /**
   * Initiliztion of nvml and handlers
   */
  _nvmlInit();

  device_count = std::make_unique<uint32_t>();
  _nvmlDeviceGetCount(device_count.get());

  devices.resize(*device_count.get());
  for (uint32_t i = 0; i < *device_count.get(); i++)
  {
    devices[i] = std::make_unique<nvmlDevice_t>();
    _nvmlDeviceGetHandleByIndex(i, devices[i].get());
  }
}

std::map<std::string, unsigned long long> NVMLDevice::getEnergy()
{
  /**
   * Returns energy as a map to make it compatible with RAPL
   */
  nvmlfunction_nvmlDevice_unsignedlonglong _nvmlDeviceGetTotalEnergyConsumption = reinterpret_cast<nvmlfunction_nvmlDevice_unsignedlonglong>(GETFUNC(nvmlhandle, "nvmlDeviceGetTotalEnergyConsumption"));
  std::map<std::string, unsigned long long> energies;
  for (uint32_t i = 0; i < *device_count.get(); i++)
  {
    std::unique_ptr<unsigned long long> energy_value = std::make_unique<unsigned long long>();
    _nvmlDeviceGetTotalEnergyConsumption(*devices[i].get(), energy_value.get());
    energies["nvidia_gpu_" + std::to_string(i)] = *energy_value.get();
  }
  return energies;
}