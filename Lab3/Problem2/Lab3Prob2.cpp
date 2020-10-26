/*
Author: Xueren Ge
Class: ECE6122
Last Date Modified: 13-Oct-2020
Description:
The purpose of this file is to create a multi-threaded
program to animate the ant on the move problem. In order
to use the program, you need to input -N 100000 -g 6
*/
#include <iostream>
#include <random>
#include <omp.h>
#include<cstring>
#include <fstream>
#include <thread>

using namespace std;

// define the move
const int dx[5] = {0,-1,1,0,0};
const int dy[5] = {0,0,0,-1,1};
int N, g;
// use hashtable to record previous visited points
bool hashtable[1005][1005];

// To determine whether (x,y) inside the boundary
bool Boundary(int x, int y)
{
    return (x >= 1 && x <= g && y >= 1 && y <= g);
}

int main(int argc, char* argv[])
{
    N = atoi(argv[2]);
    g = atoi(argv[4]);
    double pp;
    int xcoord, ycoord;
    int Num_Succ = 0;
    bool flag;

    // Use multi-thread to speed up
#pragma omp parallel for num_threads(thread::hardware_concurrency()) private(xcoord,ycoord,hashtable,flag) reduction(+:Num_Succ)
    for (int i = 0; i < N; ++i)
    {
        flag = true;
        memset(hashtable, 0, sizeof(hashtable));
        xcoord = ycoord = 1;
        while (true)
        {
            // mark the point is visited
            hashtable[xcoord][ycoord] = 1;
            // Success
            if (xcoord == g && ycoord == g)
            {
                ++Num_Succ;
                break;
            }
            flag = false;
            // if exists a point hasn't been visited previously and is in the area
            for (int j = 1; j <= 4; ++j)
            {
                if (Boundary(xcoord + dx[j], ycoord + dy[j]) && !hashtable[xcoord + dx[j]][ycoord + dy[j]])
                {
                    // If it is able to move left or right or up or down
                    flag = true;
                    break;
                }
            }
            if (flag)
            {
                random_device rd;
                uniform_int_distribution<int> distribution(1,4);
                default_random_engine generator {rd()};
                int k {distribution(rd)};
                // if it's out of boundary or previously visited, reselect a move
                while (!Boundary(xcoord + dx[k], ycoord + dy[k]) || hashtable[xcoord + dx[k]][ycoord + dy[k]])
                {
                    k = {distribution(rd)};
                }
                // move
                xcoord += dx[k];
                ycoord += dy[k];
            }
            else break;
        }
    }
    // calculate the probability
    pp = Num_Succ / (N * 1.0);
    // output
    ofstream ofs ("./Lab3Prob2.txt", ofstream::out);
    ofs.precision(12);
    ofs << fixed << pp <<endl;

    return 0;
}
