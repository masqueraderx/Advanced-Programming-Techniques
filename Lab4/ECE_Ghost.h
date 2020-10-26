/*
Author: Xueren Ge
Class: ECE6122
Last Date Modified: 25-Oct-2020
Description: This file defines the class ECE_Ghost
which 6 private parameters: RGB(color) and xyz(offset).
It has 2 member functions, Read_Ghost is used to read
in data, Draw_Ghost is used to draw different Ghosts.
*/

#ifndef LAB4_ECE_GHOST_H
#define LAB4_ECE_GHOST_H
#include <GLUT/glut.h>

class ECE_Ghost{

public:
    // read parameters(RGB and xyz offset) of ghost in
    ECE_Ghost read_Ghost(int const& i);
    // draw ghosts
    void draw_Ghost();

private:
    GLfloat R, G, B;
    int xcoord, ycoord, zcoord;
};


#endif //LAB4_ECE_GHOST_H
