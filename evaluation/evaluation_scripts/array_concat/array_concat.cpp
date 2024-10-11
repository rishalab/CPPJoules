#include <vector>
#include <iostream>
#include <cppJoules.h>

int main()
{
  EnergyTracker tracker;
  tracker.start();
  std::vector<int> a(1e8), b(1e8);
  //a[0] = 11; a[1] = 12; a[2] = 13;
  //b[0] = 21; b[1] = 22; b[2] = 23; b[3] = 24;

  a.insert(a.end(), b.begin(), b.end());
  tracker.stop();
  tracker.calculate_energy();
  tracker.print_energy();
  //for (int i = 0; i < a.size(); ++i)
    //std::cout << "a[" << i << "] = " << a[i] << "\n";
}
