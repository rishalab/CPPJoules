from pyJoules.energy_meter import measure_energy

@measure_energy
def bubble_sort(seq):
    changed = True
    while changed:
        changed = False
        for i in range(len(seq) - 1):
            if seq[i] > seq[i+1]:
                seq[i], seq[i+1] = seq[i+1], seq[i]
                changed = True
    return seq

if __name__ == "__main__":
   from random import shuffle
   testset = [_ for _ in range(10000)]
   testcase = testset.copy() 
   shuffle(testcase)
   bubble_sort(testcase)
