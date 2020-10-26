/*
Author: Xueren Ge
Class: ECE6122
Last Date Modified: 25-Oct-2020
Description:
This file draws 3D Pac-Man Maze, press 'R' or 'r' can
rotate the maze 5 degree, press 'q' or 'Q' or 'ESC' can
exit.
*/
#include <GLUT/glut.h>
#include <math.h>
#include <stdlib.h> // standard definitions
#include "ECE_Ghost.h"
#include "ECE_Pacman.h"
#include <vector>

GLUquadricObj *objCylinder = gluNewQuadric();
float turn = 0;

// change size of window
void changeSize(int w, int h)
{
    float ratio = ((float)w) / ((float)h); // window aspect ratio
    glMatrixMode(GL_PROJECTION); // projection matrix is active
    glLoadIdentity(); // reset the projection
    gluPerspective(45.0, ratio, 0.1, 100.0); // perspective transformation
    glMatrixMode(GL_MODELVIEW); // return to modelview mode
    glViewport(0, 0, w, h); // set viewport (drawing area) to entire window
}

// draw circle to fill the empty area on top of solid cylinder
void drawCircle()
{
    int number = 100;
    float radius = 0.35f;
    float twoPi = 2.0f * 3.14159f;
    glBegin(GL_POLYGON);
    for ( int i = 0; i < number; ++i )
    {
        glVertex2f(radius * cosf(i * twoPi / number), radius * sinf(i * twoPi / number));
    }
    glEnd();
}

//draw golden disks (disks is made of solid cylinder and a circle on top of it)
void drawPowerUp()
{
    // golden
    GLfloat r = 255.0f / 255.0f;
    GLfloat g = 215.0f / 255.0f;
    GLfloat b = 0.0f / 255.0f;
    glColor3f(r, g, b);
    // draw left front one
    glPushMatrix();
        glTranslatef(-8, 0, 6);
        glRotatef(-90,1,0,0);
        gluCylinder(objCylinder, 0.35, 0.35, 0.1, 32, 5);
        glPushMatrix();
            glTranslatef(0, 0, 0.1);
            drawCircle();
        glPopMatrix();
    glPopMatrix();
    // draw left back one
    glPushMatrix();
        glTranslatef(-8, 0, -8);
        glRotatef(-90,1,0,0);
        gluCylinder(objCylinder, 0.35, 0.35, 0.1, 32, 5);
        glPushMatrix();
            glTranslatef(0, 0, 0.1);
            drawCircle();
        glPopMatrix();
    glPopMatrix();
    // draw right front one
    glPushMatrix();
        glTranslatef(8, 0, 6);
        glRotatef(-90,1,0,0);
        gluCylinder(objCylinder, 0.35, 0.35, 0.1, 32, 5);
        glPushMatrix();
            glTranslatef(0, 0, 0.1);
            drawCircle();
        glPopMatrix();
    glPopMatrix();
    // draw right back one
    glPushMatrix();
        glTranslatef(8, 0, -8);
        glRotatef(-90,1,0,0);
        gluCylinder(objCylinder, 0.35, 0.35, 0.1, 32, 5);
        glPushMatrix();
            glTranslatef(0, 0, 0.1);
            drawCircle();
        glPopMatrix();
    glPopMatrix();
}

// draw coins
void drawCoin()
{
    // back part (row -9 to -4)
    for ( int i = -8; i <= 8; ++i )
    {
        for ( int j = -9; j <= -4; ++j )
        {
            // special cases which are used to fill up incompleteness of 2 cylinder intersection.
            if ((j == -8 || j == -7) && (abs(i) == 7 || abs(i) == 6 || abs(i) == 4 || abs(i) == 3 || abs(i) == 2 || i == 0))
            {
                glColor3f(0.0, 0.65, 1.0);
                glPushMatrix();
                    glTranslatef(i, 0, j);
                    glutSolidSphere(0.15, 20, 20);
                glPopMatrix();
            }
            if ((j == -5) && (abs(i) == 7 || abs(i) == 6 || abs(i) == 4 || abs(i) == 2 || abs(i) == 1 || i == 0))
            {
                glColor3f(0.0, 0.65, 1.0);
                glPushMatrix();
                    glTranslatef(i, 0, j);
                    glutSolidSphere(0.15, 20, 20);
                glPopMatrix();
            }
            // no spheres
            if (j == -8 && abs(i) == 8)
                continue;
            // sliver coins
            glColor3f(0.75294, 0.75294, 0.75294);
            glPushMatrix();
                glTranslatef(i, 0, j);
                glutSolidSphere(0.15, 20, 20);
            glPopMatrix();
        }
    }
    // 2 column (-3 and 3) have all silver spheres
    for ( int j = -3; j <= 3; ++j )
    {
        glPushMatrix();
        glTranslatef(-5, 0, j);
            glutSolidSphere(0.15, 20, 20);
        glPopMatrix();
    }
    for ( int j = -3; j <= 3; ++j )
    {
        glPushMatrix();
        glTranslatef(5, 0, j);
            glutSolidSphere(0.15, 20, 20);
        glPopMatrix();
    }
    // front part(row 4 to 10)
    for ( int i = -8; i <= 8; ++i )
    {
        for ( int j = 4; j <= 10; ++j )
        {
            // special cases which are used to fill up incompleteness of 2 cylinder intersection.
            if ((j == 5) && (abs(i) == 7 || abs(i) == 6 || abs(i) == 4 || abs(i) == 3 || abs(i) == 2 || i == 0))
            {
                glColor3f(0.0, 0.65, 1.0);
                glPushMatrix();
                glTranslatef(i, 0, j);
                glutSolidSphere(0.15, 20, 20);
                glPopMatrix();
            }
            if ((j == 7) && (abs(i) == 8 || abs(i) == 6 || abs(i) == 4 || abs(i) == 2 || abs(i) == 1 || i == 0))
            {
                glColor3f(0.0, 0.65, 1.0);
                glPushMatrix();
                glTranslatef(i, 0, j);
                glutSolidSphere(0.15, 20, 20);
                glPopMatrix();
            }
            if ((j == 9) && (abs(i) == 7 || abs(i) == 6 || abs(i) == 5 || abs(i) == 4 || abs(i) == 3 || abs(i) == 2 || i == 0))
            {
                glColor3f(0.0, 0.65, 1.0);
                glPushMatrix();
                glTranslatef(i, 0, j);
                glutSolidSphere(0.15, 20, 20);
                glPopMatrix();
            }
            // no spheres
            if (j == 6 && (abs(i) == 8 || i == 0))
                continue;
            // sliver coins
            glColor3f(0.75294, 0.75294, 0.75294);
            glPushMatrix();
                glTranslatef(i, 0, j);
                glutSolidSphere(0.15, 20, 20);
            glPopMatrix();
        }
    }
    //draw blue spheres at where two cylinders join
    glColor3f(0.0, 0.65, 1.0);
    for (int i = -9; i <= 9; ++i )
    {
        for (int j = -3; j <= 3; ++j)
        {
            if ((j == -3) && (abs(i) == 9 || abs(i) == 6 || abs(i) == 2 || i == 0))
            {
                glPushMatrix();
                glTranslatef(i, 0, j);
                glutSolidSphere(0.15, 20, 20);
                glPopMatrix();
            }
            if ((j == 3 || (abs(j) == 1)) && (abs(i) == 9 || abs(i) == 6 || abs(i) == 4 || abs(i) == 2))
            {
                glPushMatrix();
                glTranslatef(i, 0, j);
                glutSolidSphere(0.15, 20, 20);
                glPopMatrix();
            }
        }
    }
    // draw four blue spheres for 4 maze corners
    glPushMatrix();
        glTranslatef(-9, 0, -10);
        glutSolidSphere(0.15, 20, 20);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(9, 0, -10);
        glutSolidSphere(0.15, 20, 20);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-9, 0, 11);
        glutSolidSphere(0.15, 20, 20);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(9, 0, 11);
        glutSolidSphere(0.15, 20, 20);
    glPopMatrix();
}

// draw walls of maze
void drawMaze()
{
    // blue
    glColor3f(0.0, 0.65, 1.0);

    // draw front wall
    glPushMatrix();
        glTranslatef(-9.0, 0.0, 11.0);
        glRotatef(90,0,1,0);
        gluCylinder(objCylinder, 0.15, 0.15, 18.0, 32, 5);
    glPopMatrix();

    // draw back wall
    glPushMatrix();
        glTranslatef(-9.0, 0.0, -10.0);
        glRotatef(90,0,1,0);
        gluCylinder(objCylinder, 0.15, 0.15, 18.0, 32, 5);
    glPopMatrix();

    // draw the right margin of maze(camera perspective)
    glPushMatrix();
        glTranslatef(9.0, 0.0, 3.0);
        gluCylinder(objCylinder, 0.15, 0.15, 8.0, 32, 5);
        glPushMatrix();
            glRotatef(-90,0,1,0);
            gluCylinder(objCylinder, 0.15, 0.15, 3.0, 32, 5);
            glPushMatrix();
                glTranslatef(0.0, 0.0, 3.0);
                glRotatef(-90,0,1,0);
                gluCylinder(objCylinder, 0.15, 0.15, 2.0, 32, 5);
            glPopMatrix();
            glPushMatrix();
                glTranslatef(-2.0, 0.0, 0.0);
                gluCylinder(objCylinder, 0.15, 0.15, 3.0, 32, 5);
                glPushMatrix();
                    glTranslatef(-2.0, 0.0, 0.0);
                    gluCylinder(objCylinder, 0.15, 0.15, 3.0, 32, 5);
                    glPushMatrix();
                        glTranslatef(0.0, 0.0, 3.0);
                        glRotatef(-90,0,1,0);
                        gluCylinder(objCylinder, 0.15, 0.15, 2.0, 32, 5);
                    glPopMatrix();
                    glPushMatrix();
                        glTranslatef(-2.0, 0.0, 0.0);
                        gluCylinder(objCylinder, 0.15, 0.15, 3.0, 32, 5);
                    glPopMatrix();
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0.0, 0.0, -13.0);
            gluCylinder(objCylinder, 0.15, 0.15, 7.0, 32, 5);
        glPopMatrix();

    // draw the left margin of the maze(camera perspective)
    glPopMatrix();
        glPushMatrix();
        glTranslatef(-9.0, 0.0, 3.0);
        gluCylinder(objCylinder, 0.15, 0.15, 8.0, 32, 5);
        glPushMatrix();
            glRotatef(90,0,1,0);
            gluCylinder(objCylinder, 0.15, 0.15, 3.0, 32, 5);
            glPushMatrix();
                glTranslatef(0.0, 0.0, 3.0);
                glRotatef(90,0,1,0);
                gluCylinder(objCylinder, 0.15, 0.15, 2.0, 32, 5);
            glPopMatrix();
            glPushMatrix();
                glTranslatef(2.0, 0.0, 0.0);
                gluCylinder(objCylinder, 0.15, 0.15, 3.0, 32, 5);
                glPushMatrix();
                    glTranslatef(2.0, 0.0, 0.0);
                    gluCylinder(objCylinder, 0.15, 0.15, 3.0, 32, 5);
                    glPushMatrix();
                        glTranslatef(0.0, 0.0, 3.0);
                        glRotatef(90,0,1,0);
                        gluCylinder(objCylinder, 0.15, 0.15, 2.0, 32, 5);
                    glPopMatrix();
                    glPushMatrix();
                        glTranslatef(2.0, 0.0, 0.0);
                        gluCylinder(objCylinder, 0.15, 0.15, 3.0, 32, 5);
                    glPopMatrix();
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0.0, 0.0, -13.0);
            gluCylinder(objCylinder, 0.15, 0.15, 7.0, 32, 5);
        glPopMatrix();
    glPopMatrix();

    // draw the rectangle in the middle
    glPushMatrix();
        glTranslatef(2.0, 0.0, 1.0);
        glRotatef(-90, 0.0, 1.0, 0.0);
        gluCylinder(objCylinder, 0.15, 0.15, 4.0, 32, 5);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(2.0, 0.0, -1.0);
        glRotatef(-90, 0.0, 1.0, 0.0);
        gluCylinder(objCylinder, 0.15, 0.15, 4.0, 32, 5);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(2.0, 0.0, -1.0);
        gluCylinder(objCylinder, 0.15, 0.15, 2.0, 32, 5);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-2.0, 0.0, -1.0);
        gluCylinder(objCylinder, 0.15, 0.15, 2.0, 32, 5);
    glPopMatrix();

    // other lines around the middle rectangle
    // draw all vertical line
    // front
    glPushMatrix();
        glTranslatef(0.0, 0.0, 3.0);
        gluCylinder(objCylinder, 0.15, 0.15, 2.0, 32, 5);
        glPushMatrix();
            glTranslatef(-4.0, 0.0, -2.0);
            gluCylinder(objCylinder, 0.15, 0.15, 2.0, 32, 5);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(4.0, 0.0, -2.0);
            gluCylinder(objCylinder, 0.15, 0.15, 2.0, 32, 5);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0.0, 0.0, 4.0);
            gluCylinder(objCylinder, 0.15, 0.15, 2.0, 32, 5);
            glPushMatrix();
                glTranslatef(-4.0, 0.0, 0.0);
                gluCylinder(objCylinder, 0.15, 0.15, 2.0, 32, 5);
                glPushMatrix();
                    glTranslatef(-2.0, 0.0, -2.0);
                    gluCylinder(objCylinder, 0.15, 0.15, 2.0, 32, 5);
                glPopMatrix();
            glPopMatrix();
            glPushMatrix();
                glTranslatef(4.0, 0.0, 0.0);
                gluCylinder(objCylinder, 0.15, 0.15, 2.0, 32, 5);
                glPushMatrix();
                    glTranslatef(2.0, 0.0, -2.0);
                    gluCylinder(objCylinder, 0.15, 0.15, 2.0, 32, 5);
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
    // back
    // right part of back
    glPushMatrix();
        glTranslatef(0.0, 0.0, -5.0);
        gluCylinder(objCylinder, 0.15, 0.15, 2.0, 32, 5);
        glPushMatrix();
            glTranslatef(2.0, 0.0, -3.0);
            gluCylinder(objCylinder, 0.15, 0.15, 1.0, 32, 5);
            glPushMatrix();
                glTranslatef(2.0, 0.0, 0.0);
                gluCylinder(objCylinder, 0.15, 0.15, 1.0, 32, 5);
                glPushMatrix();
                    glTranslatef(2.0, 0.0, 0.0);
                    gluCylinder(objCylinder, 0.15, 0.15, 1.0, 32, 5);
                    glPushMatrix();
                        glTranslatef(1.0, 0.0, 0.0);
                        gluCylinder(objCylinder, 0.15, 0.15, 1.0, 32, 5);
                    glPopMatrix();
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();
    //left part of back
        glPushMatrix();
            glTranslatef(-2.0, 0.0, -3.0);
            gluCylinder(objCylinder, 0.15, 0.15, 1.0, 32, 5);
            glPushMatrix();
                glTranslatef(-2.0, 0.0, 0.0);
                gluCylinder(objCylinder, 0.15, 0.15, 1.0, 32, 5);
                glPushMatrix();
                    glTranslatef(-2.0, 0.0, 0.0);
                    gluCylinder(objCylinder, 0.15, 0.15, 1.0, 32, 5);
                    glPushMatrix();
                        glTranslatef(-1.0, 0.0, 0.0);
                        gluCylinder(objCylinder, 0.15, 0.15, 1.0, 32, 5);
                    glPopMatrix();
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();
        glPushMatrix();
            glTranslatef(-4.0, 0.0, 0.0);
            gluCylinder(objCylinder, 0.15, 0.15, 4.0, 32, 5);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(4.0, 0.0, 0.0);
            gluCylinder(objCylinder, 0.15, 0.15, 4.0, 32, 5);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0.0, 0.0, -5.0);
            gluCylinder(objCylinder, 0.15, 0.15, 3.0, 32, 5);
        glPopMatrix();
    glPopMatrix();
    // horizontal lines
    // front
    glPushMatrix();
        glTranslatef(2.0, 0.0, 3.0);
        glRotatef(-90, 0.0, 1.0, 0.0);
        gluCylinder(objCylinder, 0.15, 0.15, 4.0, 32, 5);
        glPushMatrix();
            glTranslatef(4.0, 0.0, 0.0);
            gluCylinder(objCylinder, 0.15, 0.15, 4.0, 32, 5);
            glPushMatrix();
                glTranslatef(0.0, 0.0, -7.0);
                gluCylinder(objCylinder, 0.15, 0.15, 1.0, 32, 5);
            glPopMatrix();
            glPushMatrix();
                glTranslatef(0.0, 0.0, 10.0);
                gluCylinder(objCylinder, 0.15, 0.15, 1.0, 32, 5);
            glPopMatrix();
            glPushMatrix();
                glTranslatef(2.0, 0.0, -5.0);
                gluCylinder(objCylinder, 0.15, 0.15, 5.0, 32, 5);
            glPopMatrix();
            glPushMatrix();
                glTranslatef(2.0, 0.0, 4.0);
                gluCylinder(objCylinder, 0.15, 0.15, 5.0, 32, 5);
            glPopMatrix();
        glPopMatrix();
        glPushMatrix();
            glTranslatef(2.0, 0.0, -2.0);
            gluCylinder(objCylinder, 0.15, 0.15, 2.0, 32, 5);
            glPushMatrix();
                glTranslatef(0.0, 0.0, -3.0);
                gluCylinder(objCylinder, 0.15, 0.15, 1.0, 32, 5);
            glPopMatrix();
        glPopMatrix();
        glPushMatrix();
            glTranslatef(2.0, 0.0, 4.0);
            gluCylinder(objCylinder, 0.15, 0.15, 2.0, 32, 5);
            glPushMatrix();
                glTranslatef(0.0, 0.0, 4.0);
                gluCylinder(objCylinder, 0.15, 0.15, 1.0, 32, 5);
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
    // back
    glPushMatrix();
        glTranslatef(2.0, 0.0, -5.0);
        glRotatef(-90, 0.0, 1.0, 0.0);
        gluCylinder(objCylinder, 0.15, 0.15, 4.0, 32, 5);
        //right
        glPushMatrix();
            glTranslatef(2.0, 0.0, -2.0);
            gluCylinder(objCylinder, 0.15, 0.15, 2.0, 32, 5);
            glPushMatrix();
                glTranslatef(-4.0, 0.0, 0.0);
                gluCylinder(objCylinder, 0.15, 0.15, 2.0, 32, 5);
                glPushMatrix();
                    glTranslatef(0.0, 0.0, -3.0);
                    gluCylinder(objCylinder, 0.15, 0.15, 1.0, 32, 5);
                    glPushMatrix();
                        glTranslatef(2.0, 0.0, 0.0);
                        gluCylinder(objCylinder, 0.15, 0.15, 1.0, 32, 5);
                    glPopMatrix();
                glPopMatrix();
                glPushMatrix();
                    glTranslatef(-1.0, 0.0, 0.0);
                    gluCylinder(objCylinder, 0.15, 0.15, 2.0, 32, 5);
                    glPushMatrix();
                        glTranslatef(0.0, 0.0, -3.0);
                        gluCylinder(objCylinder, 0.15, 0.15, 1.0, 32, 5);
                    glPopMatrix();
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();
        //left
        glPushMatrix();
            glPushMatrix();
                glTranslatef(2.0, 0.0, 4.0);
                gluCylinder(objCylinder, 0.15, 0.15, 2.0, 32, 5);
            glPopMatrix();
            glTranslatef(-2.0, 0.0, 4.0);
            gluCylinder(objCylinder, 0.15, 0.15, 2.0, 32, 5);
            glPushMatrix();
                glTranslatef(0.0, 0.0, 4.0);
                gluCylinder(objCylinder, 0.15, 0.15, 1.0, 32, 5);
                glPushMatrix();
                    glTranslatef(2.0, 0.0, 0.0);
                    gluCylinder(objCylinder, 0.15, 0.15, 1.0, 32, 5);
                glPopMatrix();
            glPopMatrix();
            glPushMatrix();
                glTranslatef(-1.0, 0.0, 0.0);
                gluCylinder(objCylinder, 0.15, 0.15, 2.0, 32, 5);
                glPushMatrix();
                    glTranslatef(0.0, 0.0, 4.0);
                    gluCylinder(objCylinder, 0.15, 0.15, 1.0, 32, 5);
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
}

// draw four ghosts
void drawGhost()
{
    std::vector<ECE_Ghost> vecGhosts;
    vecGhosts.resize(4);
    for ( int i = 0; i < 4; ++i)
    {
        vecGhosts[i].read_Ghost(i);
        vecGhosts[i].draw_Ghost();
    }
}

// draw one pacman
void drawPacman()
{
    std::vector<ECE_Pacman> vecPacman;
    vecPacman.resize(1);
    for ( int i = 0; i < 1; ++i)
    {
        vecPacman[i].read_Pacman(i);
        vecPacman[i].draw_Pacman();
    }
}

void renderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Reset transformations
    glLoadIdentity();
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHT0);
    // set the light
    GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    // enable light
    glEnable(GL_DEPTH_TEST);
    // set camera
    gluLookAt(15.0, 20.0, 17.0, -3.0, -7.0, -4.0, 0.0, 1.0, 0.0);
    // draw the whole scene and the rotate function
    glPushMatrix();
        glRotatef(turn, 0.0, 1.0, 0.0);
        drawMaze();
        drawCoin();
        drawPowerUp();
        drawGhost();
        drawPacman();
    glPopMatrix();

    glutSwapBuffers();
}

// set keyboard function
void keyboard(unsigned char key, int xx, int yy)
{
    switch (key)
    {
        // if 'q' or 'Q'
        case 'q':
        case 'Q':
            exit(0);
        // if 'r' or 'R'
        case 'r':
        case 'R':
            // rotate 5 degree
            turn = ((int)turn - 5) % 360;
            // refresh the screen
            glutPostRedisplay();
            break;
        // if 'ESC'
        case 27:
            exit(0);
        default:
            break;
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    // set window
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(700, 400);
    glutCreateWindow("Pac-man");
    // set keyboard function
    glutKeyboardFunc(keyboard);
    // display
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize); // window reshape callback
    glutMainLoop();
    return 0;
}