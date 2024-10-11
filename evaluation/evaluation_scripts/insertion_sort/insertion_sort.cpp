#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include "../include/cppJoules.h"

template <typename RandomAccessIterator, typename Predicate>
void insertion_sort(RandomAccessIterator begin, RandomAccessIterator end,
                    Predicate p) {
  for (auto i = begin; i != end; ++i) {
    std::rotate(std::upper_bound(begin, i, *i, p), i, i + 1);
  }
}

// calls with default Predicate std::less (sort ascending)
template <typename RandomAccessIterator>
void insertion_sort(RandomAccessIterator begin, RandomAccessIterator end) {
  insertion_sort(begin, end, std::less<typename std::iterator_traits<RandomAccessIterator>::value_type>());
}

int main(){
  std::vector<int> arr(1e5,0);
  for (int i=0;i<1e5;i++){
    arr[i] = i;
  }
  std::random_shuffle(arr.begin(),arr.end());
  EnergyTracker tracker;
  tracker.start();
  insertion_sort(arr.begin(),arr.end());
  tracker.stop();
  tracker.calculate_energy();
  tracker.print_energy();
}
