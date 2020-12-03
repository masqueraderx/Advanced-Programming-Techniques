/*
Author: Xueren Ge
Class: ECE6122
Last Date Modified: 2020/11/30
Description:
This is the cpp file for pacman, its function is to draw pacman and its color.
*/
#include "pacman.h"
#include <GL/glut.h> // Include the GLUT header file

using namespace std;

// this function is to draw pacman.
void ECE_Pacman::sketchPacman(float px, float pz,float R,float G,float B)
{
	glColor3f(R, G, B);
	glPushMatrix();
	glTranslatef(px, 0.5, pz);
	glutSolidSphere(0.5, 20, 20);
	glPopMatrix();
}
