/*
Author: Xueren Ge
Class: ECE6122
Last Date Modified: 13-Oct-2020
Description:
This file is used to implement the member functions of class SudokuGrid.
*/
#include "Sudoku.h"
const int N = 9;
using namespace std;

bool SudokuGrid::isPresentInCol(int const& col, int const& num) const
{
    for (int row = 0; row < N; row++)
        if ((this->gridElement[row][col] - 48) == num)
            return true;
    return false;
}

bool SudokuGrid::isPresentInRow(int const& row, int const& num) const
{
    for (int col = 0; col < N; col++)
        if ((this->gridElement[row][col] - 48) == num)
            return true;
    return false;
}

bool SudokuGrid::isPresentInBox(int const& boxStartRow, int const& boxStartCol, int const& num) const
{
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            if ((this->gridElement[row+boxStartRow][col+boxStartCol] - 48) == num)
                return true;
    return false;
}

bool SudokuGrid::findEmptyPlace(int &row, int &col) const
{
    for (row = 0; row < N; ++row)
        for (col = 0; col < N; ++col)
            if ((this->gridElement[row][col] - 48) == 0) //marked with 0 is empty
                return true;
    return false;
}

bool SudokuGrid::isValidPlace(int const& row, int const& col, int const& num) const
{
    //when item not found in col, row and current 3x3 box
    return !isPresentInRow(row, num) && !isPresentInCol(col, num) && !isPresentInBox(row - row%3 ,col - col%3, num);
}

bool SudokuGrid::solve()
{
    int row, col;
    if (!findEmptyPlace(row, col))
        return true; //when all places are filled
    for (int num = 1; num <= 9; num++){ //valid numbers are 1 - 9
        if (isValidPlace(row, col, num)){ //check validation, if yes, put the number in the grid
            this->gridElement[row][col] = num + 48;
            if (solve()) //recursively go for other rooms in the grid
                return true;
            this->gridElement[row][col] = 0 + 48; //turn to unassigned space when conditions are not satisfied
        }
    }
    return false;
}
