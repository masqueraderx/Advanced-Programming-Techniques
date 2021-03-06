/*
Author: Xueren Ge
Class: ECE6122
Last Date Modified: 2020/11/30
Description:
this file defines the ECE_Ghost member function and path
*/
#pragma once
#include <iostream>
#include <GL/glut.h> // Include the GLUT header file
#include <stdio.h>
#include <math.h>
#include <stdlib.h> // standard definitions
#include <random>
#include <queue>
#include <thread>
#include <ctime>
using namespace std;

struct node{
	int xcoord;
	int zcoord;
	int forard;
	int distance;
	int position;
};

class ECE_Ghost {
public:
	void sketchGhost();

	ECE_Ghost(float x, float z, float R, float G, float B);

	float x, z;
	float R, G, B;
	int seq;
	float xBegin, zEnd;
    thread ghostThread;
    bool ghostMove = 0;
    static char gameBoard[22][19];
    void sketchCoinPowerUp();
	void setPath(int x, int z, int path[420][3], int point);
	int getPath(int x, int z, int path[420][3]);
	void gmove(int x, int z, int pacX, int pacZ);
	bool catchPac(int x, int z, int pacX, int pacZ);
	int BFS(int x, int z, int pacX, int pacZ);
    void ghostTime(int t);
    void init();

    int path[420][3] =
    { {9,11,2},{8,11,2},{7,11,2},{6,11,2},{5,11,2},{4,11,2},{3,11,2},{2,11,2},{1,11,2},{0,11,2},{-9,11,2},{-8,11,2},{-7,11,2},{-6,11,2},{-5,11,2},{-4,11,2},{-3,11,2},{-2,11,2},{-1,11,2},
      {9,10,2},{8,10,0},{7,10,0},{6,10,0},{5,10,0},{4,10,0},{3,10,0},{2,10,0},{1,10,0},{0,10,2},{-8,10,0},{-7,10,0},{-6,10,0},{-5,10,0},{-4,10,0},{-3,10,0},{-2,10,0},{-1,10,0},{-9,10,2},
      {9,9,2},{8,9,0},{7,9,2},{6,9,2},{5,9,0},{4,9,2},{3,9,2},{2,9,2},{1,9,0},{0,9,2},{-9,9,2},{-8,9,0},{-7,9,2},{-6,9,2},{-5,9,0},{-4,9,2},{-3,9,2},{-2,9,2},{-1,9,0},
      {9,8,2},{8,8,0},{7,8,2},{6,8,2},{5,8,0},{4,8,2},{3,8,2},{2,8,2},{1,8,0},{0,8,2},{-9,8,2},{-8,8,0},{-7,8,2},{-6,8,2},{-5,8,0},{-4,8,2},{-3,8,2},{-2,8,2},{-1,8,0},
      {9,7,2},{8,7,0},{7,7,0},{6,7,0},{5,7,0},{4,7,0},{3,7,0},{2,7,0},{1,7,0},{0,7,0},{-8,7,0},{-7,7,0},{-6,7,0},{-5,7,0},{-4,7,0},{-3,7,0},{-2,7,0},{-1,7,0},{-9,7,2},
      {9,6,2},{8,6,0},{7,6,2},{6,6,2},{5,6,0},{4,6,2},{3,6,0},{2,6,2},{1,6,2},{0,6,2},{-1,6,2},{-2,6,2},{-3,6,0},{-4,6,2},{-5,6,0},{-6,6,2},{-7,6,2},{-8,6,0},{-9,6,2},
      {9,5,2},{8,5,0},{7,5,0},{6,5,0},{5,5,0},{4,5,2},{3,5,0},{2,5,0},{1,5,0},{0,5,2},{-8,5,0},{-7,5,0},{-6,5,0},{-5,5,0},{-4,5,2},{-3,5,0},{-2,5,0},{-1,5,0},{-9,5,2},
      {9,4,2},{8,4,2},{7,4,2},{6,4,2},{5,4,0},{4,4,2},{3,4,2},{2,4,2},{1,4,0},{0,4,2},{-1,4,0},{-4,4,2},{-3,4,2},{-2,4,2},{-5,4,0},{-9,4,2},{-8,4,2},{-7,4,2},{-6,4,2},
      {9,3,2},{8,3,2},{7,3,2},{6,3,2},{5,3,0},{4,3,2},{3,3,0},{2,3,0},{1,3,0},{0,3,0},{-1,3,0},{-2,3,0},{-3,3,0},{-4,3,2},{-5,3,0},{-9,3,2},{-8,3,2},{-7,3,2},{-6,3,2},
      {9,2,2},{8,2,2},{7,2,2},{6,2,2},{5,2,0},{4,2,2},{3,2,0},{2,2,2},{1,2,2},{0,2,2},{-9,2,2},{-8,2,2},{-7,2,2},{-6,2,2},{-5,2,0},{-4,2,2},{-3,2,0},{-2,2,2},{-1,2,2},
      {9,1,0},{8,1,0},{7,1,0},{6,1,0},{5,1,0},{4,1,0},{3,1,0},{2,1,2},{1,1,2},{0,1,2},{-9,1,0},{-8,1,0},{-7,1,0},{-6,1,0},{-5,1,0},{-4,1,0},{-3,1,0},{-2,1,2},{-1,1,2},
      {9,0,2},{8,0,2},{7,0,2},{6,0,2},{5,0,0},{4,0,2},{3,0,0},{2,0,2},{1,0,2},{0,0,2},{-9,0,2},{-8,0,2},{-7,0,2},{-6,0,2},{-5,0,0},{-4,0,2},{-3,0,0},{-2,0,2},{-1,0,2},
      {9,-1,2},{8,-1,2},{7,-1,2},{6,-1,2},{5,-1,0},{4,-1,2},{3,-1,0},{2,-1,0},{1,-1,0},{0,-1,0},{-1,-1,0},{-2,-1,0},{-3,-1,0},{-4,-1,2},{-5,-1,0},{-9,-1,2},{-8,-1,2},{-7,-1,2},{-6,-1,2},
      {9,-2,2},{8,-2,2},{7,-2,2},{6,-2,2},{5,-2,0},{4,-2,2},{3,-2,0},{2,-2,2},{1,-2,2},{0,-2,2},{-2,-2,2},{-1,-2,2},{-3,-2,0},{-4,-2,2},{-5,-2,0},{-9,-2,2},{-8,-2,2},{-7,-2,2},{-6,-2,2},
      {9,-3,2},{8,-3,0},{7,-3,0},{6,-3,0},{5,-3,0},{4,-3,0},{3,-3,0},{2,-3,0},{1,-3,0},{0,-3,2},{-8,-3,0},{-7,-3,0},{-6,-3,0},{-5,-3,0},{-4,-3,0},{-3,-3,0},{-2,-3,0},{-1,-3,0},{-9,-3,2},
      {9,-4,2},{8,-4,0},{7,-4,2},{6,-4,2},{5,-4,0},{4,-4,2},{3,-4,2},{2,-4,2},{1,-4,0},{0,-4,2},{-1,-4,0},{-4,-4,2},{-3,-4,2},{-2,-4,2},{-5,-4,0},{-7,-4,2},{-6,-4,2},{-8,-4,0},{-9,-4,2},
      {9,-5,2},{8,-5,0},{7,-5,0},{6,-5,2},{5,-5,0},{4,-5,0},{3,-5,0},{2,-5,0},{1,-5,0},{0,-5,0},{-1,-5,0},{-2,-5,0},{-3,-5,0},{-4,-5,0},{-5,-5,0},{-6,-5,2},{-7,-5,0},{-8,-5,0},{-9,-5,2},
      {9,-6,2},{8,-6,2},{7,-6,0},{6,-6,2},{5,-6,0},{4,-6,2},{3,-6,0},{2,-6,2},{1,-6,2},{0,-6,2},{-1,-6,2},{-2,-6,2},{-3,-6,0},{-4,-6,2},{-5,-6,0},{-6,-6,2},{-7,-6,0},{-9,-6,2},{-8,-6,2},
      {9,-7,2},{8,-7,0},{7,-7,0},{6,-7,0},{5,-7,0},{4,-7,2},{3,-7,0},{2,-7,0},{1,-7,0},{0,-7,2},{-9,-7,2},{-8,-7,0},{-7,-7,0},{-6,-7,0},{-5,-7,0},{-4,-7,2},{-3,-7,0},{-2,-7,0},{-1,-7,0},
      {9,-8,2},{8,-8,0},{7,-8,2},{6,-8,2},{5,-8,2},{4,-8,2},{3,-8,2},{2,-8,2},{1,-8,0},{0,-8,2},{-1,-8,0},{-7,-8,2},{-6,-8,2},{-5,-8,2},{-4,-8,2},{-3,-8,2},{-2,-8,2},{-8,-8,0},{-9,-8,2},
      {9,-9,2},{8,-9,0},{7,-9,0},{6,-9,0},{5,-9,0},{4,-9,0},{3,-9,0},{2,-9,0},{1,-9,0},{0,-9,0},{-9,-9,2},{-8,-9,0},{-7,-9,0},{-6,-9,0},{-5,-9,0},{-4,-9,0},{-3,-9,0},{-2,-9,0},{-1,-9,0},
      {9,-10,2},{8,-10,2},{7,-10,2},{6,-10,2},{5,-10,2},{4,-10,2},{3,-10,2},{2,-10,2},{1,-10,2},{0,-10,2},{-9,-10,2},{-8,-10,2},{-7,-10,2},{-6,-10,2},{-5,-10,2},{-4,-10,2},{-3,-10,2},{-2,-10,2},{-1,-10,2},
      {10,1,2},{-10,1,2}
    };
};