from pyJoules.energy_meter import measure_energy
import bisect
@measure_energy
def insertion_sort(seq):
    for i in range(1, len(seq)):
        bisect.insort(seq, seq.pop(i), 0, i)

if __name__ == "__main__":
   from random import shuffle
   testset = [_ for _ in range(100000)]
   testcase = testset.copy() # make a copy
   shuffle(testcase)
   insertion_sort(testcase)
