/*
Author: Xueren Ge
Class: ECE6122
Last Date Modified: 25-Oct-2020
Description: This file implements Class
ECE_Ghost's 2 member functions.
*/

#include "ECE_Ghost.h"
#include <GLUT/glut.h>
GLUquadricObj *ghost = gluNewQuadric();

GLfloat Ghost_Color[4][3] = {{255.0f / 255.0f, 192.0f / 255.0f, 203.0f / 255.0f}, // pink
                       {0.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f}, // green
                       {255.0f / 255.0f, 97.0f / 255.0f, 0.0f / 255.0f}, // orange
                       {255.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f}}; // red

int Ghost_Offset[4][3] = {{0, 0, 0}, // pink ghost offset
                    {-1, 0, 0}, // green ghost offset
                    {1, 0, 0}, // orange ghost offset
                    {0, 0, 1}}; // red ghost offset
// read in
ECE_Ghost ECE_Ghost::read_Ghost(int const& i)
{
    (*this).R = Ghost_Color[i][0];
    (*this).G = Ghost_Color[i][1];
    (*this).B = Ghost_Color[i][2];
    (*this).xcoord = Ghost_Offset[i][0];
    (*this).ycoord = Ghost_Offset[i][1];
    (*this).zcoord = Ghost_Offset[i][2];
    return *this;
}
// draw ghost
void ECE_Ghost::draw_Ghost()
{
    glColor3f(this->R, this->G, this->B);
    glPushMatrix();
        // draw body
        glTranslatef(this->xcoord + 0, 0 + this->ycoord, 0.5 - this->zcoord);
        glRotatef(-90,1,0,0);
        gluCylinder(ghost, 0.4, 0.4, 0.4, 32, 5);
        glPushMatrix();
            glTranslatef(0, 0, 0.4);
            glutSolidSphere(0.4, 20, 20);
            // draw right eye
            glPushMatrix();
                glColor3f(1.0, 1.0, 1.0);
                glTranslatef(-0.1, -0.25, 0.2);
                glutSolidSphere(0.13, 20, 20);
                // draw eye ball
                glPushMatrix();
                    glColor3f(0.0, 0.0, 0.0);
                    glTranslatef(0.03, -0.08, 0.12);
                    glutSolidSphere(0.05, 20, 20);
                glPopMatrix();
            glPopMatrix();
            // draw left eye
            glPushMatrix();
                glColor3f(1.0, 1.0, 1.0);
                glTranslatef(0.1, -0.25, 0.2);
                glutSolidSphere(0.13, 20, 20);
                // draw eye ball
                glPushMatrix();
                    glColor3f(0.0, 0.0, 0.0);
                    glTranslatef(0.03, -0.08, 0.12);
                    glutSolidSphere(0.05, 20, 20);
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
}