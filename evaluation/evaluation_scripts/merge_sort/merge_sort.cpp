#include <iterator>
#include <algorithm> // for std::inplace_merge
#include <functional> // for std::less
#include <cppJoules.h>
template<typename RandomAccessIterator, typename Order>
 void mergesort(RandomAccessIterator first, RandomAccessIterator last, Order order)
{
  if (last - first > 1)
  {
    RandomAccessIterator middle = first + (last - first) / 2;
    mergesort(first, middle, order);
    mergesort(middle, last, order);
    std::inplace_merge(first, middle, last, order);
  }
}

template<typename RandomAccessIterator>
 void mergesort(RandomAccessIterator first, RandomAccessIterator last)
{
  mergesort(first, last, std::less<typename std::iterator_traits<RandomAccessIterator>::value_type>());

}

int main(){
  std::vector<int> arr(1e7,0);
  for (int i=0;i<1e7;i++){
    arr[i] = i;
  }
  std::random_shuffle(arr.begin(),arr.end());
  EnergyTracker tracker;
  tracker.start();
  mergesort(arr.begin(),arr.end());
  tracker.stop();
  tracker.calculate_energy();
  tracker.print_energy();
}
