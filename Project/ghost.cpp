/*
Author: Xueren Ge
Class: ECE6122
Last Date Modified: 2020/11/30
Description:
Its function is to draw ghosts and their colors. 
*/

#include "ghost.h"
#include <GL/glut.h> // Include the GLUT header file
#include <thread>
using namespace std;

// constructor: x,z coordinates, RGB color starting sequence
ECE_Ghost::ECE_Ghost(float x, float z, float R, float G, float B)
{
	this->x = x;
	this->z = z;
	this->R = R;
	this->G = G;
	this->B = B;
	this->seq = 0;
	this->xBegin = x;
	this->zEnd = z;
	if (this->x == 0.0 && this->z == 1.5)   this->seq = 1;
	if (this->x == 1.0 && this->z == 0.5)   this->seq = 2;
	if (this->x == -1.0 && this->z == 0.5)    this->seq = 3;
	if (this->x == 0.0 && this->z == 0.5)   this->seq = 4;
}

//draw ghosts and their colors
void ECE_Ghost::sketchGhost()
{
	glColor3f(this->R, this->G, this->B);
	glPushMatrix();
	    glTranslatef(this->x, 0.5, this->z);
	    glutSolidSphere(0.4, 20, 20);
    // draw right eye
        glPushMatrix();
            glColor3f(1.0, 1.0, 1.0);
            glTranslatef(-0.12, 0.25, -0.2);
            glutSolidSphere(0.1, 20, 20);
        // draw eye ball
            glPushMatrix();
                glColor3f(0.0, 0.0, 0.0);
                glTranslatef(-0.03, 0.05, -0.06);
                glutSolidSphere(0.05, 20, 20);
            glPopMatrix();
        glPopMatrix();
        // draw left eye
        glPushMatrix();
            glColor3f(1.0, 1.0, 1.0);
            glTranslatef(0.12, 0.25, -0.2);
            glutSolidSphere(0.1, 20, 20);
        // draw eye ball
            glPushMatrix();
                glColor3f(0.0, 0.0, 0.0);
                glTranslatef(0.03, 0.05, -0.06);
                glutSolidSphere(0.05, 20, 20);
            glPopMatrix();
        glPopMatrix();
	glPopMatrix();
    // draw body
    glColor3f(this->R, this->G, this->B);
	glPushMatrix();
	    glTranslatef(this->x, 0, this->z);
	    glRotatef(-90, 1, 0, 0);
	    GLUquadricObj* objCylinder = gluNewQuadric();
	    gluCylinder(objCylinder,0.4,0.4,0.4,32,32);
	glPopMatrix();
}

// sketch powerUp and coin
void ECE_Ghost::sketchCoinPowerUp()
{
    for (int i = 0; i < 22; i++)
    {
        for (int j = 0; j < 19; j++)
        {

            if (this->gameBoard[i][j] == 'd')
            {
                glColor3f(192.0 / 255.0, 192.0 / 255.0, 192.0 / 255.0); //The color for the coins.
                glPushMatrix();
                glTranslatef(j - 9, 0.1, -i + 11);
                glutSolidSphere(0.15, 20, 20);
                glPopMatrix();
            }
            if (this->gameBoard[i][j] == 'g')
            {
                glColor3f(175.0 / 255.0, 149.0 / 255.0, 114.0 / 255.0); //Define the color for powers.
                glPushMatrix();
                glTranslatef(j - 9, 0, -i + 11);
                glRotatef(-90, 1, 0, 0);
                GLUquadricObj* objDisk = gluNewQuadric();
                gluDisk(objDisk, 0.001, 0.25, 40, 40);
                glPopMatrix();
            }
        }
    }
}

// set path
void ECE_Ghost::setPath(int x, int z, int path[420][3], int point)
{
	for (int i = 0; i < 420; i++)
	{
		if (path[i][0] == x && path[i][1] == z)
		{
			path[i][2] = point;
		}
	}
}

// get path
int ECE_Ghost::getPath(int x, int z, int path[420][3])
{
	int point;
	int i = 0;
	while (i < 420)
    {
	    if (path[i][0] == x && path[i][1] == z)
        {
            point = path[i][2];
            return point;
        }
	    ++i;
    }
}

// shortest path algorithm
int ECE_Ghost::BFS(int x, int z, int pacX, int pacZ)
{
	struct node q[500];
	int dx[4] = { 0, 0, 1, -1 };
	int dz[4] = { 1, -1, 0, 0 };
	int head = 0, tail = 1;
	int path[420][3];

	for (int i = 0; i < 420; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			path[i][j] = this->path[i][j];
		}
	}
	for (int i = 0; i < 4; i++)
	{
		int tx = x + dx[i];
		int tz = z + dz[i];
		if (getPath(tx, tz, path) == 0 && tx == pacX && tz == pacZ)
		{
			return i;
		}
	}

	q[head].xcoord = x;
	q[head].zcoord = z;
	q[head].forard = -1;
	q[head].distance = 0;
	q[head].position = -1;
	setPath(x, z, path, 1);

	while (head < tail)
	{
		for (int i = 0; i < 4; i++)
		{
			int fx = q[head].xcoord + dx[i];
			int fz = q[head].zcoord + dz[i];

			if (getPath(fx, fz, path) == 0)
			{
				setPath(fx, fz, path, 1);
				q[tail].xcoord = fx;
				q[tail].zcoord = fz;
				q[tail].forard = head;
				q[tail].distance = q[head].distance + 1;
				q[tail].position = i;
				tail++;
			}
			if (fx == pacX && fz == pacZ)
			{
				int t = q[tail - 1].forard;
				while (q[t].forard != 0)
				{
					int tmp = q[t].forard;
					t = tmp;
				}
				return q[t].position;
			}
		}
		head++;
	}
}

// move ghost according to DFS
void ECE_Ghost::gmove(int x, int z, int pacX, int pacZ)
{
	if (catchPac(x, z, pacX, pacZ))
	{
		return;
	}
    switch (BFS(x, z, pacX, pacZ))
    {
        case 0:
            this->z += 1.0;
            break;
        case 1:
            this->z -= 1.0;
            break;
        case 2:
            this->x += 1.0;
            break;
        case 3:
            this->x -= 1.0;
            break;
        default:
            break;
    }
}

// decide whether catch pacman
bool ECE_Ghost::catchPac(int x, int z, int pacX, int pacZ)
{
	if (x == pacX && z == pacZ)
	{
		return true;
	}
	return false;
}

// initialize the ghost
void ECE_Ghost::init()
{
	this->x = this->xBegin;
	this->z = this->zEnd;
	this->ghostMove = 0;
	ghostThread = thread(&ECE_Ghost::ghostTime, this, seq);
}

// determine the time between ghost get out the middle box
void ECE_Ghost::ghostTime(int t)
{
    this_thread::sleep_for(chrono::seconds((t-1)));
    this->x = 0.0;
    this->z = 3.0;
    this->ghostMove = 1;
}

// w:x, c:d, p:g, 0:empty
char ECE_Ghost::gameBoard[22][19] =
{
    {'x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x'},
    {'x','d','d','d','d','d','d','d','d','x','d','d','d','d','d','d','d','d','x'},
    {'x','g','x','x','d','x','x','x','d','x','d','x','x','x','d','x','x','g','x'},
    {'x','d','x','x','d','x','x','x','d','x','d','x','x','x','d','x','x','d','x'},
    {'x','d','d','d','d','d','d','d','d','d','d','d','d','d','d','d','d','d','x'},
    {'x','d','x','x','d','x','d','x','x','x','x','x','d','x','d','x','x','d','x'},
    {'x','d','d','d','d','x','d','d','d','x','d','d','d','x','d','d','d','d','x'},
    {'x','x','x','x','d','x','x','x','0','x','0','x','x','x','d','x','x','x','x'},
    {'x','x','x','x','d','x','0','0','0','0','0','0','0','x','d','x','x','x','x'},
    {'x','x','x','x','d','x','0','x','x','0','x','x','0','x','d','x','x','x','x'},
    {'0','0','0','0','d','0','0','x','0','0','0','x','0','0','d','0','0','0','0'},
    {'x','x','x','x','d','x','0','x','x','x','x','x','0','x','d','x','x','x','x'},
    {'x','x','x','x','d','x','0','0','0','0','0','0','0','x','d','x','x','x','x'},
    {'x','x','x','x','d','x','0','x','x','x','x','x','0','x','d','x','x','x','x'},
    {'x','d','d','d','d','d','d','d','d','x','d','d','d','d','d','d','d','d','x'},
    {'x','d','x','x','d','x','x','x','d','x','d','x','x','x','d','x','x','d','x'},
    {'x','g','d','x','d','d','d','d','d','0','d','d','d','d','d','x','d','g','x'},
    {'x','x','d','x','d','x','d','x','x','x','x','x','d','x','d','x','d','x','x'},
    {'x','d','d','d','d','x','d','d','d','x','d','d','d','x','d','d','d','d','x'},
    {'x','d','x','x','x','x','x','x','d','x','d','x','x','x','x','x','x','d','x'},
    {'x','d','d','d','d','d','d','d','d','d','d','d','d','d','d','d','d','d','x'},
    {'x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x'}
};