#include "Gaus.h"
#include <cmath>
#include <chrono>

Real_valued GausInv(Real_valued A)
{
    if (A.Matrix.size() != A.Matrix[0].size())
        throw std::invalid_argument("this matrix is not square");

    Real_valued inversed(A.Matrix.size(), A.Matrix.size());

    Real_valued src(A);

    for (int i = 0; i < A.Matrix.size(); i++)
        inversed.Matrix[i][i] = 1;

    for (int k = 0; k < A.Matrix.size(); k++)
    {
        double diag = src.Matrix[k][k];
        if (!abs(diag))
            throw std::invalid_argument("Inverse matrix doesn't exist");

        for (int i = 0; i < A.Matrix.size(); i++)
        {
            inversed.Matrix[k][i] /= diag;
            src.Matrix[k][i] /= diag;
        }

        src.Matrix[k][k] = 1;
        for (int i = 0; i < A.Matrix.size(); i++)
        {
            if (k == i)
                continue;
            else if (abs(src.Matrix[i][k]) == 0)
                continue;
            else
            {
                double div = src.Matrix[i][k] / src.Matrix[k][k];
                for (int j = 0; j < A.Matrix.size(); j++)
                {
                    src.Matrix[i][j] -= div * src.Matrix[k][j];
                    inversed.Matrix[i][j] -= div * inversed.Matrix[k][j];
                }
            }
        }
    }

    return inversed;
}

void gausTest(int beg, int end, int step)
{
    using namespace std::chrono;

    for (int i = beg; i < end; i += step)
    {

        Real_valued init(i, i, true);

        auto start = high_resolution_clock::now();
        Real_valued inv = GausInv(init);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - start);

        Real_valued res = init.multiplication(inv);

        double error = 0;
        for (int y = 0; y < i; ++y)
        {
            for (int x = 0; x < i; ++x)
            {
                // cout << y << ' ' << x << endl;
                if (x != y)
                    error += fabsf64(res.Matrix[y][x]);
                else
                    error += fabsf64(1 - res.Matrix[y][x]);
            }
        }

        error /= (i * i);

        cout << "Size: " << i << 'x' << i << "\n  time: " << ((double)duration.count()) / 1000 << " sec \n  error: " << error << '\n'
             << endl;
    }
}