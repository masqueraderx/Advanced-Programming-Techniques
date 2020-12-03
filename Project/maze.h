/*
Author: Xueren Ge
Class: ECE6122
Last Date Modified: 2020/11/30
Description:
defines class maze member functions
*/
#pragma once
#include <iostream>
#include <GL/glut.h> // Include the GLUT header file
#include <stdio.h>
#include <math.h>
#include <stdlib.h> // standard definitions

class maze {
public:
    // draw maze
	void sketchMaze();
    //The first two parameters show the coordinates.
    // The third shows its height.
    // the last indicates rotation direction
	int mazeGraph[66][4] =
	{
		{-9,11,18,1},{-7,9,1,1},{-7,8,1,1},{-4,9,2,1},{-4,8,2,1},
		{2,9,2,1},{2,8,2,1},{6,9,1,1},{6,8,1,1},{-7,6,1,1},
		{-2,6,4,1},{6,6,1,1},{-9,4,3,1},{-4,4,2,1},{2,4,2,1},
		{6,4,3,1},{-9,2,3,1},{-2,2,1,1},{1,2,1,1},{6,2,3,1},
		{-9,0,3,1},{-2,0,4,1},{6,0,3,1},{-9,-2,3,1},{-2,-2,4,1},
		{6,-2,3,1},{-7,-4,1,1},{-4,-4,2,1},{2,-4,2,1},{6,-4,1,1},
		{-9,-6,1,1},{-2,-6,4,1},{8,-6,1,1},{-7,-8,5,1},{2,-8,5,1},
		{-9,-10,18,1},{-9,-10,8,0},{9,-10,8,0},{-4,-8,2,0},{4,-8,2,0},
		{0,-8,2,0},{-6,-6,2,0},{6,-6,2,0},{0,-4,2,0},{-6,-2,2,0},{-4,-2,2,0},
		{4,-2,2,0},{6,-2,2,0},{-2,0,2,0},{2,0,2,0},{-6,2,2,0},{-4,2,4,0},{4,2,4,0},
		{6,2,2,0},{-9,4,7,0},{9,4,7,0},{0,4,2,0},{-7,8,1,0},{-6,8,1,0},{-4,8,1,0},
		{-2,8,1,0},{2,8,1,0},{4,8,1,0},{6,8,1,0},{7,8,1,0},{0,8,3,0}
	};
};
