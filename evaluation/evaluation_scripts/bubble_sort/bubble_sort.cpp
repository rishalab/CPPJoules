#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <cppJoules.h>

template <typename RandomAccessIterator>
void bubble_sort(RandomAccessIterator begin, RandomAccessIterator end) {
  bool swapped = true;
  while (begin != end-- && swapped) {
    swapped = false;
    for (auto i = begin; i != end; ++i) {
      if (*(i + 1) < *i) {
        std::iter_swap(i, i + 1);
        swapped = true;
      }
    }
  }
}

int main(){
  std::vector<int> arr(1e4,0);
  for (int i=0;i<1e4;i++){
    arr[i] = i;
  }
  std::random_shuffle(arr.begin(),arr.end());
  EnergyTracker tracker;
  tracker.start();
  bubble_sort(arr.begin(),arr.end());
  tracker.stop();
  tracker.calculate_energy();
  tracker.print_energy();
}
