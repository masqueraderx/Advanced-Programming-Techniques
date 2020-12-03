/*
Author: Xueren Ge
Class: ECE6122
Last Date Modified: 2020/11/30
Description:
This file implemented the game "3D" pacman.
press up, down, left, right key to control the pacman's direction
press 'g' to let ghost move
if pacman eats the power up, the ghost will escape from the pacman for 5 seconds
if pacman is caught by ghost, game will restart and restart for 3 times. Then game over.
*/

#include <thread>
#include <chrono>
#include <iostream>
#include <GL/glut.h>
#include "ghost.h"
#include "maze.h"
#include "pacman.h"
#include <stdlib.h>
using namespace std;

// pacman coordinates
double x = 0.0;
double z = -5.0;
// whether ghost escape
bool ghostEscape = 0;
// whether pacman eat the powerUp
bool powerUp = 0;
int flag;
// input color, coordinate
ECE_Ghost ghost1(0.0, 0.5, 255.0f / 255.0f, 192.0f / 255.0f, 203.0f / 255.0f); // pink
ECE_Ghost ghost2(-1.0, 0.5, 0.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f); // orange
ECE_Ghost ghost3(1.0, 0.5, 0.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f); //green
ECE_Ghost ghost4(0.0, 1.5, 255.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f); //red
ECE_Pacman pacman;
// total number of coins and powers
int coinPowerUpLeft = 156;
// live of pacman
int remaining = 3;
// whether it needs restart
bool reStart = 0;
// camera angle
int turn = -35;

thread pac, power;

// how ghost1 move
void ghost1move(void)
{
    switch (powerUp)
    {
        // if pacman doesn't eat PowerUp, run to pacman (x, z)
        case 0:
            ghost1.gmove(ghost1.x, ghost1.z, x, z);
            break;
        // if pacman eat PowerUp, run to the contrary direction (-x, -z)
        case 1:
            ghost1.gmove(ghost1.x, ghost1.z, -x, -z);
            break;
        default:
            break;
    }

    if (ghost1.catchPac(ghost1.x, ghost1.z, x, z))
    {
        switch (powerUp)
        {
            // if pacman was caught and didn't eat powerUp
            case 0:
                reStart = 1;
                ghost1.ghostMove = 0;
                ghost2.ghostMove = 0;
                ghost3.ghostMove = 0;
                ghost4.ghostMove = 1;
                remaining--;
                ghost1.ghostThread.join();
                ghost2.ghostThread.join();
                ghost3.ghostThread.join();
                ghost4.ghostThread.join();
                ghost1.init();
                ghost2.init();
                ghost3.init();
                ghost4.init();
                break;
            // if pacman was caught but eat powerUp
            case 1:
                ghost1.x = 0;
                ghost1.z = 0.5;
                ghost1.ghostMove = 0;
                ghost1.R = 1;
                ghost1.G = 128.0 / 255.5;
                ghost1.B = 192.0 / 255.0;
                ghost1.sketchGhost();
                break;
            default:
                break;
        }
    }
    // if lives was exhausted
    if (remaining == 0)
    {
        cout << "You lose!" << endl;
        cout << "Waiting to close the window..." << endl;
        ghost1.ghostThread.join();
        ghost2.ghostThread.join();
        ghost3.ghostThread.join();
        ghost4.ghostThread.join();
        cout << "Closed" << endl;
        exit(0);
   }
   glutPostRedisplay();
}

// how ghost2 move
void ghost2move(void)
{
    switch (powerUp)
    {
        // if pacman doesn't eat PowerUp, run to pacman (x, z)
        case 0:
            ghost2.gmove(ghost2.x, ghost2.z, x, z);
            break;
        // if pacman eat PowerUp, run to the contrary direction (-x, -z)
        case 1:
            ghost2.gmove(ghost2.x, ghost2.z, -x, -z);
            break;
        default:
            break;
    }
    // if pacman was caught
    if (ghost2.catchPac(ghost2.x, ghost2.z, x, z))
    {
        switch (powerUp)
        {
            // if pacman doesn't eat powerUp
            case 0:
                reStart = 1;
                ghost1.ghostMove = 1;
                ghost2.ghostMove = 0;
                ghost3.ghostMove = 0;
                ghost4.ghostMove = 0;
                remaining--;
                ghost1.ghostThread.join();
                ghost2.ghostThread.join();
                ghost3.ghostThread.join();
                ghost4.ghostThread.join();
                ghost1.init();
                ghost2.init();
                ghost3.init();
                ghost4.init();
                break;
            // if pacman eat powerUp
            case 1:
                ghost2.x = -1.0;
                ghost2.z = 0.5;
                ghost2.ghostMove = 0;
                ghost2.R = 1;
                ghost2.G = 159.0 / 255.5;
                ghost2.B = 113.0 / 255.0;
                ghost2.sketchGhost();
                break;
            default:
                break;
        }
    }

    if (remaining == 0)
    {
        cout << "You lose!" << endl;
        cout << "Waiting to close the window..." << endl;
        ghost4.ghostThread.join();
        ghost3.ghostThread.join();
        ghost2.ghostThread.join();
        ghost1.ghostThread.join();
        cout << "Closed" << endl;
        exit(0);
    }
    glutPostRedisplay();
}

void ghost3move(void)
{
    switch (powerUp)
    {
        // if pacman doesn't eat powerUp
        case 0:
            ghost3.gmove(ghost3.x, ghost3.z, x, z);
            break;
        // if pacman eat the powerUp
        case 1:
            ghost3.gmove(ghost3.x, ghost3.z, -x, -z);
            break;
        default:
            break;
    }
    // if pacman was caught
    if (ghost3.catchPac(ghost3.x, ghost3.z, x, z))
    {
        switch (powerUp)
        {
            // pacman doesn't eat powerUp
            case 0:
                reStart = 1;
                remaining--;
                ghost1.ghostMove = 1;
                ghost2.ghostMove = 0;
                ghost3.ghostMove = 0;
                ghost4.ghostMove = 0;
                ghost1.ghostThread.join();
                ghost2.ghostThread.join();
                ghost3.ghostThread.join();
                ghost4.ghostThread.join();
                ghost1.init();
                ghost2.init();
                ghost3.init();
                ghost4.init();
                break;
            // pacman eat powerUp
            case 1:
                ghost3.x = 1.0;
                ghost3.z = 0.5;
                ghost3.R = 0;
                ghost3.G = 1;
                ghost3.B = 1;
                ghost3.ghostMove = 0;
                ghost3.sketchGhost();
                break;
            default:
                break;
        }
    }
    // if pacman life is exhausted
    if (remaining == 0)
    {
        cout << "You lose!" << endl;
        cout << "Waiting to close the window..." << endl;
        ghost1.ghostThread.join();
        ghost2.ghostThread.join();
        ghost3.ghostThread.join();
        ghost4.ghostThread.join();
        cout << "Closed" << endl;
        exit(0);
    }
    glutPostRedisplay();
}

void ghost4move(void)
{
    switch (powerUp)
    {
        // pacman doesn't eat powerUp
        case 0:
            ghost4.gmove(ghost4.x, ghost4.z, x, z);
            break;
        // pacman eat powerUp
        case 1:
            ghost4.gmove(ghost4.x, ghost4.z, -x, -z);
            break;
        default:
            break;
    }
    // pacman was caught
    if (ghost4.catchPac(ghost4.x, ghost4.z, x, z))
    {
        switch (powerUp)
        {
            // pacman doesn't eat powerUp
            case 0:
                reStart = 1;
                remaining--;
                ghost1.ghostMove = 1;
                ghost2.ghostMove = 0;
                ghost3.ghostMove = 0;
                ghost4.ghostMove = 0;
                ghost1.ghostThread.join();
                ghost2.ghostThread.join();
                ghost3.ghostThread.join();
                ghost4.ghostThread.join();
                ghost1.init();
                ghost2.init();
                ghost3.init();
                ghost4.init();
                break;
            // pacman eat powerUp
            case 1:
                ghost4.x = 0.0;
                ghost4.z = 1.5;
                ghost4.R = 0;
                ghost4.G = 1;
                ghost4.B = 1;
                ghost4.ghostMove = 0;
                ghost4.sketchGhost();
                break;
            default:
                break;
        }
    }
    // pacman life was exhausted
    if (remaining == 0)
    {
        cout << "You lose!" << endl;
        cout << "Waiting to close the window..." << endl;
        ghost1.ghostThread.join();
        ghost2.ghostThread.join();
        ghost3.ghostThread.join();
        ghost4.ghostThread.join();
        cout << "Closed" << endl;
        exit(0);
    }
    glutPostRedisplay();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(20.0, (GLfloat)w / (GLfloat)h, 0.1, 80.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// used to indicate the whether pacman eat the powerUp
void eatPowerUp()
{
    powerUp = 1;
    this_thread::sleep_for(chrono::seconds(5));
    powerUp = 0;
}

// whether it's unable to kill ghost
void killGhost()
{
    power = thread(eatPowerUp);
    if (powerUp == 1)
    {
        power.join();
    }
}

void display(void)
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(20.0, 50.0,-40.0, 0.0, 0.0, 0.0, -1.0, 2.0, 2.0);

    glRotatef((GLfloat)turn, 0.0, 1.0, 0.0);
    /*Calling the ECE_Ghost class, indicating their colors and places.*/

    ghost1.sketchCoinPowerUp();
    maze m;
    m.sketchMaze();
   
    if (remaining == 0)
    {
        reStart = 0;
        x = 0;
        z = -5;
        flag = 0;

        ghost1.x = 0;
        ghost1.z = 0.5;

        ghost2.x = 1.0;
        ghost2.z = 0.5;

        ghost3.x = 1.0;
        ghost3.z = 0.5;

        ghost4.x = 0;
        ghost4.z = 1.5;
    }

    if (reStart == 0 && powerUp == 0)
    {
        ghost1.R = 1;
        ghost1.G = 128.0 / 255.5;
        ghost1.B = 192.0 / 255.0;
        ghost1.sketchGhost();
        ghost2.R = 1;
        ghost2.G = 159.0 / 255.5;
        ghost2.B = 113.0 / 255.0;
        ghost2.sketchGhost();
        ghost3.R = 0;
        ghost3.G = 1;
        ghost3.B = 1;
        ghost3.sketchGhost();
        ghost4.R = 1;
        ghost4.G = 0;
        ghost4.B = 0;
        ghost4.sketchGhost();
        pacman.sketchPacman(x, z, 238.0 / 255.0, 227.0 / 255.0, 0);
    }

    if (powerUp == 1 && ghost4.catchPac(ghost4.x, ghost4.z, x, z) == 0)
    {
        ghostEscape = 1;
        ghost1.R = 1;
        ghost1.B = 1;
        ghost1.G = 1;
        ghost2.R = 1;
        ghost2.B = 1;
        ghost2.G = 1;
        ghost3.R = 1;
        ghost3.B = 1;
        ghost3.G = 1;
        ghost4.R = 1;
        ghost4.B = 1;
        ghost4.G = 1;
        ghost1.sketchGhost();
        ghost2.sketchGhost();
        ghost3.sketchGhost();
        ghost4.sketchGhost();
        pacman.sketchPacman(x, z, 238.0 / 255.0, 227.0 / 255.0, 0);
    }

    // restart
   if (reStart == 1)
   {
       // pacman back to original coordinates
       x = 0;
       z = -5;
       flag = 0;
       // ghost back to origin ghost coordinates
       ghost1.x = 0;
       ghost1.z = 0.5;
       ghost2.x = -1.0;
       ghost2.z = 0.5;
       ghost3.x = 1.0;
       ghost3.z = 0.5;
       ghost4.x = 0;
       ghost4.z = 2.0;
       // if game not over
       if (remaining >= 1)
       {
           ghost4.ghostMove = 1;
           ghost3.ghostMove = 0;
           ghost2.ghostMove = 0;
           ghost1.ghostMove = 0;
       }
 
       pacman.sketchPacman(x, z, 238.0 / 255.0, 227.0 / 255.0, 0);
       
       ghost4.sketchGhost();
       ghost3.sketchGhost();
       ghost2.sketchGhost();
       ghost1.sketchGhost();
       if (remaining > 0)
       {
           reStart = 0;
       }
   }

   if (ghostEscape == 1 && powerUp == 0)
   {
       power.join();
       ghostEscape = 0;
   }

   if (remaining >= 1)
   {
       if (ghost4.ghostMove == 1)   ghost4move();
       if (ghost3.ghostMove == 1)   ghost3move();
       if (ghost2.ghostMove == 1)   ghost2move();
       if (ghost1.ghostMove == 1)   ghost1move();
   }
   glutSwapBuffers();
   glutPostRedisplay();
}

// decide how ghost move
bool ghostMove(int xPosition, int zPosition)
{
    int xcoord = (int)xPosition;
    int zcoord = (int)zPosition;
    // if it's wall
    if (ECE_Ghost::gameBoard[-zcoord + 11][xcoord + 9] == 'x')  return 0;
    // if it's coin, eat it
    if (ECE_Ghost::gameBoard[-zcoord + 11][xcoord + 9] == 'd')
    {
        ECE_Ghost::gameBoard[-zcoord + 11][xcoord + 9] = '0';
        coinPowerUpLeft = coinPowerUpLeft - 1;
        return 1;
    }
    // if it's PowerUp, eat it
    if (ECE_Ghost::gameBoard[-zcoord + 11][xcoord + 9] == 'g')
    {
        killGhost();
        ECE_Ghost::gameBoard[-zcoord + 11][xcoord + 9] = '0';
        coinPowerUpLeft = coinPowerUpLeft - 1;
        return 1;
    }
}

void pacmanMove()
{
    switch (flag)
    {
        // move upward
        case 1:
            z += 1;
            if (ghostMove(x, z) == 0)   z -= 1;
            else if (ghostMove(x, z) == 1)  ECE_Ghost::gameBoard[-(int)z + 11][(int)x + 9] = '0';
            break;
        // move downward
        case 2:
            z -= 1;
            if (ghostMove(x, z) == 0)   z += 1;
            else if (ghostMove(x, z) == 1)  ECE_Ghost::gameBoard[-(int)z + 11][(int)x + 9] = '0';
            break;
        // move left
        case 3:
            x += 1;
            if (ghostMove(x, z) == 0)   x -= 1;
            else if (ghostMove(x, z) == 1)  ECE_Ghost::gameBoard[-(int)z + 11][(int)x + 9] = '0';
            break;
        // move right
        case 4:
            x -= 1;
            if (ghostMove(x, z) == 0)   x += 1;
            else if (ghostMove(x, z) == 1)  ECE_Ghost::gameBoard[-(int)z + 11][(int)x + 9] = '0';
            break;
        default:
            break;
    }
    glutPostRedisplay();
}


void update(void)
{
    if (remaining > 0 && coinPowerUpLeft > 0)
    {
        if (flag != 0)
        {
            pac = thread(pacmanMove);
            pac.join();
        }
        if (coinPowerUpLeft == 0)
        {
            cout << "You win!" << endl;
            cout << "Waiting to close the window..." << endl;
            ghost4.ghostThread.join();
            ghost3.ghostThread.join();
            ghost2.ghostThread.join();
            ghost1.ghostThread.join();
            cout << "Closed" << endl;
            exit(0);
        }
        this_thread::sleep_for(chrono::milliseconds(100));
    }
    glutPostRedisplay();
}

void processNormalKeys(unsigned char key, int xx, int yy)
{
  switch (key)
    {
        case 'g':
        case 'G':
            ghost4.init();
            ghost3.init();
            ghost2.init();
            ghost1.init();
            glutPostRedisplay();
            break;
        case 'p':
        case 'P':
            ghost4.ghostMove = 0;
            break;
        case 'r':
        case 'R':
            // rotate 5 degree
            turn = ((int)turn - 5) % 360;
            // refresh the screen
            glutPostRedisplay();
            break;
        default:
            break;
    }
}


void pressSpecialKey(int key, int xx, int yy)
{
    switch (key)
    {
        // up
        case GLUT_KEY_UP:
        {
            flag = 1;
            break;
        }
        // down
        case GLUT_KEY_DOWN:
        {
            flag = 2;
            break;
        }
        // left
        case GLUT_KEY_LEFT:
        {
            flag = 3;
            break;
        }
        // right
        case GLUT_KEY_RIGHT:
        {
            flag = 4;
            break;
        }
    }
}

//----------------------------------------------------------------------------------------
// This is the main function. Its function is standard GLUT initializations and callbacks.
//----------------------------------------------------------------------------------------
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(100, 50);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("3D PacMan Game");
    glutDisplayFunc(display);
    glutIdleFunc(update);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(processNormalKeys); 
 
    glutSpecialFunc(pressSpecialKey); // process special key pressed
    

    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHT0);
    GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);

    glutMainLoop();

    return 0;
}
