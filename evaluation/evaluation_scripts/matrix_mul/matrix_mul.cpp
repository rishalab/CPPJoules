#include <iostream>
#include "matrix.h"
#include <cppJoules.h>

#if !defined(ARRAY_SIZE)
#define ARRAY_SIZE(x) (sizeof((x)) / sizeof((x)[0]))
#endif

#define N 1000

int main()
{
    int am[N][N];
    int bm[N][N];

    Matrix<int> a(ARRAY_SIZE(am), ARRAY_SIZE(am[0]), am[0], ARRAY_SIZE(am) * ARRAY_SIZE(am[0]));
    Matrix<int> b(ARRAY_SIZE(bm), ARRAY_SIZE(bm[0]), bm[0], ARRAY_SIZE(bm) * ARRAY_SIZE(bm[0]));
    Matrix<int> c;
    EnergyTracker tracker;
    tracker.start();
    try
    {
        c = a * b;
        for (unsigned int i = 0; i < c.rowNum(); i++)
        {
            for (unsigned int j = 0; j < c.colNum(); j++)
            {
                std::cout << c[i][j] << "  ";
            }
            std::cout << std::endl;
        }
	tracker.stop();
    	tracker.calculate_energy();
    	tracker.print_energy();
    }
    catch (MatrixException &e)
    {
        std::cerr << e.message() << std::endl;
        return e.errorCode();
    }


} /* main() */
