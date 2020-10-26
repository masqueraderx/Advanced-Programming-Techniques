/*
Author: Xueren Ge
Class: ECE6122
Last Date Modified: 13-Oct-2020
Description:
The purpose of this file is to define SudokuGrid's
all member functions and member variables.
*/

#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

class SudokuGrid
{
public:

    bool isPresentInCol(int const& col, int const& num) const;

    bool isPresentInRow(int const& row, int const& num) const;

    bool isPresentInBox(int const& boxStartRow, int const& boxStartCol, int const& num) const;

    bool findEmptyPlace(int &row, int &col) const;

    bool isValidPlace(int const& row, int const &col, int const& num) const;
// solve the Sudoku
    bool solve();

    // read class in
    friend fstream& operator>>(fstream& os, SudokuGrid& gridIn)
    {
        string dataline;
        getline(os, gridIn.m_strGridName);
        char dummy[2] = {0, 0};
        for (int ii = 0; ii < 9; ++ii)
        {
            getline(os, dataline);
            for (int jj = 0; jj < 9 ; ++jj)
            {
                dummy[0] = dataline[jj];
                gridIn.gridElement[ii][jj] = atoi(dummy) + 48; // convert integer to unsigned char
            }
        }
        return os;
    }

    // this operator outputs the class using the same format as is used in reading in a MyGrid object.
    friend fstream& operator<<(fstream& os, const SudokuGrid& gridIn)
    {
        os << gridIn.m_strGridName << endl;
        for (int i = 0; i < 9; ++i)
        {
            for (int j = 0; j < 9; ++j)
            {
                os << gridIn.gridElement[i][j] << " ";
            }
            os << endl;
        }
        return os;
    }

private:
    string m_strGridName;
    unsigned char gridElement[9][9];
};