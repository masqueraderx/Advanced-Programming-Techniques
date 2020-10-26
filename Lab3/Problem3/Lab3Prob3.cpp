/*
Author: Xueren Ge
Class: ECE6122
Last Date Modified: 13-Oct-2020
Description:
The purpose of this file is to reate a multi-threaded
program that uses the fundamental theory and logic of the
Monte Carlo Simulation technique to solve the following optimization problem:
 Z = (exp(X1) + X2)^2 + 3(1 - X3)^2
 Subject to
 0 <= X1 <= 1
 0 <= X2 <= 2
 2 <= X3 <= 3
*/
#include <iostream>
#include <random>
#include <cmath>
#include <omp.h>
#include <fstream>
using namespace std;
// allocate memory in advance
double x1[1000005], x2[1000005], x3[1000005];

int main(int argc, char* argv[])
{
    const int N = atol(argv[1]); // number of trials
    double Z, temp = 0;
    int idx, j;
    // generate a random random values for each run
    random_device rd;
    uniform_real_distribution<double> X_1(0,1);
    uniform_real_distribution<double> X_2(0,2);
    uniform_real_distribution<double> X_3(2,3);
    default_random_engine generator {rd()};
    // store the random values into the static array
    for (int i = 1; i < N; ++i)
    {
        x1[i] = {X_1(rd)};
        x2[i] = {X_2(rd)};
        x3[i] = {X_3(rd)};
    }

    // use multi-thread to speed up
#pragma omp parallel shared(x1, x2, x3) private(j)
    {
#pragma omp for nowait
        // Iterate
        for (j = 1; j < N ; ++j)
        {
            Z = pow((exp(x1[j]) + x2[j]),2) + 3 * pow(1 - x3[j],2);
            // if find a maximum value, record its index and value
            if (Z > temp)
            {
                temp = Z;
                idx = j;
            }
        }
    }

    // write the value into Lab3Prob3.txt
    ofstream ofs ("./Lab3Prob3.txt", ofstream::out);
    ofs.precision(15);
    ofs << "X1: " << fixed << x1[idx] << endl;
    ofs << "X2: " << fixed << x2[idx] << endl;
    ofs << "X3: " << fixed << x3[idx] << endl;
    ofs.close();

    return 0;
}
