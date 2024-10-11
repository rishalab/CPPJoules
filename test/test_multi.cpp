#include <iostream>
#include <thread>
#include <chrono>
#include <cppJoules.h>

int main()
{

  // Sleep for 3 seconds
  EnergyTracker tracker;
  tracker.start();
  std::this_thread::sleep_for(std::chrono::seconds(6));
  tracker.stop();
  std::this_thread::sleep_for(std::chrono::seconds(2));
  tracker.start();
  std::this_thread::sleep_for(std::chrono::seconds(3));
  tracker.stop();
  tracker.calculate_energy();
  tracker.print_energy();

  return 0;
}
