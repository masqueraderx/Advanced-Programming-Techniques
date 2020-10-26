/*
Author: your Xueren Ge Class: ECE 6122
Last Date Modified: 09-02-2020
Description:
This Program is used for counting the reflection amounts of a laser beam.
 ellipse's equation is 4x2 + y2 = 100.  −0.01 ≤ x ≤ +0.01 at the top is missing,
 light beam in this problem starts at the point (0.0,10.1) and the beam first impacts the mirror at (1.4,-9.6).
*/
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

int main()
{
    // (x1,y1) is the start point
    double x1 = 0.0;
    double y1 = 10.1;
    // (x2,y2) is first impact point
    double x2 = 1.4;
    double y2 = -9.6;
    // initialize the summation
    int cnt = 0;
    // if the x coordinate is not in the range (-0.01, 0.01) and y coordinate is less than 0
    // then continues to reflect
    while (x2 > 0.01 || x2 < -0.01 || y2 < 0)
    {
        // SlopeA: incidence slope
        double slopeA = (y2 - y1) / (x2 - x1);
        // SlopeM: tangent line at any point (x,y) of the given ellipse
        double slopeM = -4 * x2 / y2;
        // reflection angle in its own plate
        double ang = (slopeA - slopeM) / (1 + slopeA * slopeM);
        // reflection slope
        double slopeB = (slopeM - ang) / (1 + slopeM * ang);
        // reflection intercept
        double intcptB = y2 - slopeB * x2;
        // slove the equation y=kx+b and 4x2 + y2 = 100
        double a = 4 + slopeB * slopeB;
        double b = 2 * slopeB * intcptB;
        double c = intcptB * intcptB - 100;
        // calculate delta and two solutions
        double delta = sqrt(b * b - 4 * a * c);
        double res1 = (-b + delta) / (2 * a);
        double res2 = (-b - delta) / (2 * a);
        // update the starting point
        x1 = x2;
        y1 = y2;
        // update the impact point
        if (abs(res2 - x2) > abs(res1 - x2))
        {
            x2 = res2;
        }
        else
        {
            x2 = res1;
        }
        y2 = slopeB * x2 + intcptB;
        // one reflection finish
        cnt++;
    }
    // write the final answer into output4.txt
    ofstream ofs ("./output4.txt", ofstream::out);
    ofs << cnt << endl;
    ofs.close();
    return 0;
}
