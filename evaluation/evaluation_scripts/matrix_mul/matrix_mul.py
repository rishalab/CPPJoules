from pyJoules.energy_meter import measure_energy

a=[[0 for i in range(1000)] for j in range(1000)]

b=[[0 for i in range(1000)] for j in range(1000)]

def mm(A, B):
    return [[sum(x * B[i][col] for i,x in enumerate(row)) for col in range(len(B[0]))] for row in A]
@measure_energy
def main():
    v = mm( a, b )
    print(v)
main()


