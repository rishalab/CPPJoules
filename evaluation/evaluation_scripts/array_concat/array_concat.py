from pyJoules.energy_meter import measure_energy

@measure_energy
def main():
    a = [0 for i in range(100000000)]
    b = [0 for i in range(100000000)]

    a.extend(b)

main()
