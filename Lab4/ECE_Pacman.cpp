/*
Author: Xueren Ge
Class: ECE6122
Last Date Modified: 25-Oct-2020
Description: This file implements Class
ECE_Pacman's 2 member functions.
*/

#include "ECE_Pacman.h"
#include <GLUT/glut.h>
//yellow
GLfloat Pacman_Color[1][3] = {255.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f};
// offset
int Pacman_Offset[1][3] = {0, 0, 6};

// read data in
ECE_Pacman ECE_Pacman::read_Pacman(const int &i)
{
    (*this).R = Pacman_Color[i][0];
    (*this).G = Pacman_Color[i][1];
    (*this).B = Pacman_Color[i][2];
    (*this).xcoord = Pacman_Offset[i][0];
    (*this).ycoord = Pacman_Offset[i][1];
    (*this).zcoord = Pacman_Offset[i][2];
    return *this;
}

// draw pacman
void ECE_Pacman::draw_Pacman()
{
    // draw body
    glColor3f(this->R, this->G, this->B);
    glPushMatrix();
        glTranslatef(this->xcoord + 0, 0 + this->ycoord, 0 + this->zcoord);
        glutSolidSphere(0.55, 20, 20);
    glPopMatrix();
}