/*
Author: Xueren Ge
Class: ECE6122
Last Date Modified: 2020/11/30
Description:
This file draws the wall of maze
*/

#include <GL/glut.h> // Include the GLUT header file
#include "maze.h"

// draw wall of maze
void maze::sketchMaze()

{
	glColor3f(22.0 / 255.0, 142.0 / 255.0, 219.0 / 255.0);
	for (int i = 0; i < 66; i++)
	{
		if (mazeGraph[i][3] == 0)
		{
			glPushMatrix();
			glTranslatef(mazeGraph[i][0], 0.1, mazeGraph[i][1]);
			GLUquadricObj* objCylinder = gluNewQuadric();
			gluCylinder(objCylinder, 0.15, 0.15, mazeGraph[i][2], 32, 32);
			glPopMatrix();

            // fill the intersection of cylinders with spheres
			glPushMatrix();
			glTranslatef(mazeGraph[i][0], 0.1, mazeGraph[i][1]);
			glutSolidSphere(0.15, 20, 20);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(mazeGraph[i][0], 0.1, mazeGraph[i][1] + mazeGraph[i][2]);
			glutSolidSphere(0.15, 20, 20);
			glPopMatrix();

		}

		if (mazeGraph[i][3] == 1)
		{
			glPushMatrix();

			glTranslatef(mazeGraph[i][0], 0.1, mazeGraph[i][1]);
			glRotatef(90, 0, 1, 0);
			GLUquadricObj* objCylinder = gluNewQuadric();
			gluCylinder(objCylinder, 0.15, 0.15, mazeGraph[i][2], 32, 32);
			glPopMatrix();

			// fill the intersection of cylinders with spheres
			glPushMatrix();
			glTranslatef(mazeGraph[i][0], 0.1, mazeGraph[i][1]);
			glutSolidSphere(0.15, 20, 20);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(mazeGraph[i][0] + mazeGraph[i][2], 0.1, mazeGraph[i][1]);
			glutSolidSphere(0.15, 20, 20);
			glPopMatrix();

		}
	}
}