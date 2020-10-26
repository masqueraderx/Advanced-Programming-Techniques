/*
Author: Xueren Ge
Class: ECE6122
Last Date Modified: 25-Oct-2020
Description: This file defines the class ECE_Pacman
which 6 private parameters: RGB(color) and xyz(offset).
It has 2 member functions, Read_Pacman is used to read
in data, Draw_Pacman is used to draw Pacman.
*/

#ifndef LAB4_ECE_PACMAN_H
#define LAB4_ECE_PACMAN_H
#include <GLUT/glut.h>

class ECE_Pacman {

public:
    // read the parameters in (RGB and xyz offset)
    ECE_Pacman read_Pacman(int const& i);
    // draw pacman
    void draw_Pacman();

private:
    GLfloat R, G, B;
    int xcoord, ycoord, zcoord;
};


#endif //LAB4_ECE_PACMAN_H
