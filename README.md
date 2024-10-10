# CPP Joules

### Energy Measurement tool for CPP/CUDA programs

- Uses Intel RAPL interface to get energy values
- Uses NVML interface for getting GPU energy values
- Needs read access to powercap in linux
- Needs a 64bit windows system with nvml in system32
___
## Installation Instructions 

### Linux

- To use without installing into lib folder
```bash!=
chmod +x installer.sh
./installer.sh
```
- Install to lib (requires cmake and make)
```bash!=
  mkdir build
  cd build
  cmake ..
  sudo cmake --build . --target install
```
___
### Windows
```
.\installer.bat
```
- cppJoules folder will be added
- Can be included as #include "cppJoules/include/cppJoules.h" //Relative path
- To use with g++, nvcc use -lCPP_Joules along with -L./cppJoules to add this path to linker search
- Keep a copy of the dll along with you .exe file to run
  
___

### Usage
```c++=
#include "cppJoules/include/cppJoules.h"
int main()
{
  EnergyTracker tracker;
  tracker.start();
  // Code Snippet Here 
  tracker.stop();
  tracker.calculate_energy();
  tracker.print_energy();
  return 0;
}

```
To compile example file filename.cpp
```
  g++ filename.cpp -lCPP_Joules -L./cppJoules
```
___
### Common Errors
- undefined refrence
  ```
  /usr/bin/ld: /usr/local/lib/libCPP_Joules.so: undefined reference to `dlopen'
  /usr/bin/ld: /usr/local/lib/libCPP_Joules.so: undefined reference to `dlsym'
  ```
  - Use -ldl in the compile options

- cppJoules not found
    - Add -L/path/to/file
    - Example -L./cppJoules

- rapl domains are not visible
    - set read access to the sockets
    - One way would be to 
      ```
      sudo chmod +r -R /sys/class/powercap/  
      ```
      Make sure to remove access after experiments.
