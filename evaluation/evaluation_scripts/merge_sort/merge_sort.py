from pyJoules.energy_meter import measure_energy
import bisect
from heapq import merge

@measure_energy
def sort(m):
    return merge_sort(m)

def merge_sort(m):
    if len(m) <= 1:
        return m

    middle = len(m) // 2
    left = m[:middle]
    right = m[middle:]

    left = merge_sort(left)
    right = merge_sort(right)
    return list(merge(left, right))
if __name__ == "__main__":
   from random import shuffle
   testset = [_ for _ in range(10000000)]
   testcase = testset.copy() # make a copy
   shuffle(testcase)
   sort(testcase)
