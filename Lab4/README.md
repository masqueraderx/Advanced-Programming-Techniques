# Lab4 3D Pac-Man Maze

This Lab mainly requires you to draw the background of Pacman game. See details in **Lab4.pdf**.

This part requires you to install OpenGL. In **MAC OS**, itself has package GLUT. Just use **#include<GLUT/glut.h>**. 
When running on **Linux System**, use **#include <GL/glut.h>**. 

You can also use glew, to install it, use **brew install glew** and **brew install glfw3**, they are 
also packages of OpenGL.

To compile it, use **g++ main.cpp ECE_Pacman.cpp ECE_Ghost.cpp -lGL -lglut -lGLU**.
