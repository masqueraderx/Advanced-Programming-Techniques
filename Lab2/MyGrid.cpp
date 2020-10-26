/*
Author: Xueren Ge
Class: ECE6122
Last Date Modified: 27-Sep-2020
Description:
The purpose of this file is to implement all member functions defined in "MyGrid.h".
*/
#include "MyGrid.h"
#include <fstream>
# include <vector>
using namespace std;

// this function is used to read elements into MyGrid
bool MyGrid::loadGridFromFile(const string& filename)
{
    int row, col;
    fstream f(filename, fstream::in);
    // Fail to load file
    if (!f.is_open())
    {
        return false;
    }
    //read myX, myY, row and col
    f >> this->myX >> this->myY;
    f >> row >> col;
    // initialize gridElements vector
    this->gridElements.resize(row);
    for (int i = 0; i < row; ++i)
    {
        this->gridElements[i].resize(col);
    }
    //read gridElements
    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < col; ++j)
        {
            f >> this->gridElements[i][j];
        }
    }
    return true;
}

// sets all elements to 0
void MyGrid::zeroOutGrid()
{
    for (int i = 0; i < this->gridElements.size(); ++i)
    {
        for (int j = 0; j < this->gridElements[0].size(); ++j)
        {
            this->gridElements[i][j] = 0;
        }
    }
}

// get number of gridElements' Rows
long MyGrid::getNumRows() const
{
    return this->gridElements.size();
}

// get number of gridElements' columns
long MyGrid::getNumCols() const
{
    return this->gridElements[0].size();
}

//Add two MyGrid object
MyGrid MyGrid::operator+(MyGrid const& rhs) const
{
    // In case that one of them is empty
    if (this->gridElements.size() == 0)
    {
        return rhs;
    }
    if (rhs.gridElements.size() == 0)
    {
        return *this;
    }

    int NewCol, NewRow;
    // calculate the new column and row
    if (this->myX > rhs.myX)
    {
        NewCol = this->myX + this->getNumCols() - rhs.myX;
    }
    else
    {
        NewCol = rhs.myX + rhs.getNumCols() - this->myX;
    }
    if (this->myY > rhs.myY)
    {
        NewRow = this->myY + this->getNumRows() - rhs.myY;
    }
    else
    {
        NewRow = rhs.myY + rhs.getNumRows() - this->myY;
    }
    // define the output MyGrid
    MyGrid Out;
    // get Out's myX and myY
    Out.myX = min(this->myX, rhs.myX);
    Out.myY = max(this->myY, rhs.myY);
    Out.gridElements.resize(NewRow);
    for (int i = 0; i < NewRow; ++i)
    {
        Out.gridElements[i].resize(NewCol);
    }
    // Initialize all elements to 0
    Out.zeroOutGrid();
    // Assign this->gridElements to Out.gridElements
    for (int i = Out.myY - this->myY; i < Out.myY - this->myY + this->getNumRows(); ++i)
    {
        for (int j = this->myX - Out.myX ; j < this->myX - Out.myX+this->getNumCols(); ++j)
        {
            Out.gridElements[i][j] += this->gridElements[i-Out.myY + this->myY][j-this->myX + Out.myX];
        }
    }
    // Assign rhs.gridElements to Out.gridElements
    for (int i = Out.myY-rhs.myY; i < Out.myY-rhs.myY + rhs.getNumRows(); ++i)
    {
        for (int j = rhs.myX-Out.myX; j < rhs.myX-Out.myX + rhs.getNumCols(); ++j)
        {
            Out.gridElements[i][j] += rhs.gridElements[i-Out.myY + rhs.myY][j-rhs.myX + Out.myX];
        }
    }
    return Out;
}

// subtract two MyGrid
MyGrid MyGrid::operator-(MyGrid const& rhs) const
{
    // In case that one of them is empty
    if (this->gridElements.size() == 0)
    {
        return rhs;
    }
    if (rhs.gridElements.size() == 0)
    {
        return *this;
    }

    int NewCol, NewRow;
    // get New row and column
    if (this->myX > rhs.myX)
    {
        NewCol = this->myX + this->getNumCols() - rhs.myX;
    }
    else
    {
        NewCol = rhs.myX + rhs.getNumCols() - this->myX;
    }
    if (this->myY > rhs.myY)
    {
        NewRow = this->myY + this->getNumRows() - rhs.myY;
    }
    else
    {
        NewRow = rhs.myY + rhs.getNumRows() - this->myY;
    }
    // define the output MyGrid
    MyGrid Out;
    // get Out's myX and myY
    Out.myX = min(this->myX, rhs.myX);
    Out.myY = max(this->myY, rhs.myY);
    Out.gridElements.resize(NewRow);
    for (int i = 0; i < NewRow; ++i)
    {
        Out.gridElements[i].resize(NewCol);
    }
    // Initialize all elements to 0
    Out.zeroOutGrid();
    // Assign this->gridElements to Out.gridElements.
    for (int i = Out.myY - this->myY; i < Out.myY - this->myY + this->getNumRows(); ++i)
    {
        for (int j = this->myX - Out.myX ; j < this->myX - Out.myX+this->getNumCols(); ++j)
        {
            Out.gridElements[i][j] += this->gridElements[i - Out.myY + this->myY][j - this->myX + Out.myX];
        }
    }
    // Out.gridElements subtract rhs.gridElements
    for (int i = Out.myY - rhs.myY; i < Out.myY - rhs.myY + rhs.getNumRows(); ++i)
    {
        for (int j = rhs.myX - Out.myX; j < rhs.myX - Out.myX + rhs.getNumCols(); ++j)
        {
            Out.gridElements[i][j] -= rhs.gridElements[i - Out.myY + rhs.myY][j - rhs.myX + Out.myX];
        }
    }
    return Out;
}

// Adds a long to all the elements in the MyGrid object
MyGrid MyGrid::operator+(long const &rhs) const
{
    MyGrid NewGrid(*this);
    for (int i = 0; i < NewGrid.getNumRows(); ++i)
    {
        for (int j = 0; j < NewGrid.getNumCols(); ++j)
        {
            NewGrid.gridElements[i][j] += rhs;
        }
    }
    return NewGrid;
}

// Adds a MyGrid object to a long.
// The long value is added to all the elements in the MyGrid object.
MyGrid operator + (long const &lhs, MyGrid const &rhs)
{
    MyGrid NewGrid(rhs);
    // Adds a long "lhs" to MyGrid object "rhs"
    return (rhs + lhs);
}

// assign a MyGrid object to another MyGrid object
MyGrid& MyGrid::operator+=(MyGrid const &rhs)
{
    // Add two MyGrid Object
    *this = *this + rhs;
    return *this;
}

// prefix: all the element values are increased by one
MyGrid& MyGrid::operator++()
{
    for (int i = 0; i < this->getNumRows(); ++i)
    {
        for (int j = 0; j < this->getNumCols(); ++j)
        {
            ++((*this).gridElements[i][j]);
        }
    }
    return *this;
}

// postfix: all the element values are increased by one
MyGrid MyGrid::operator++(int)
{
    MyGrid temp = *this;
    for (int i = 0; i < this->getNumRows(); ++i)
    {
        for (int j = 0; j < this->getNumCols(); ++j)
        {
            this->gridElements[i][j]++;
        }
    }
    // return temp MyGrid but add this MyGrid
    return temp;
}

// prefix: all the element values are decreased by one
MyGrid& MyGrid::operator--()
{
    for (int i = 0; i < this->getNumRows(); ++i)
    {
        for (int j = 0; j < this->getNumCols(); ++j)
        {
            --((*this).gridElements[i][j]);
        }
    }
    return *this;
}

// postfix: all the element values are decreased by one
MyGrid MyGrid::operator--(int)
{
    MyGrid temp = *this;
    for (int i = 0; i < this->getNumRows(); ++i)
    {
        for (int j = 0; j < this->getNumCols(); ++j)
        {
            this->gridElements[i][j]--;
        }
    }
    // // return temp MyGrid but subtract this MyGrid
    return temp;
}

// has the same effect as multiplying all the elements by -1
MyGrid MyGrid::operator-() const
{
    MyGrid temp(*this);
    for (int i = 0; i < this->getNumRows(); ++i)
    {
        for (int j = 0; j < this->getNumCols(); ++j)
        {
            temp.gridElements[i][j] *= -1;
        }
    }
    return temp;
}

// the size and all the elements must be the same
// and the upper left-hand offset must be the same.
// otherwise, return false
bool MyGrid::operator==(MyGrid const &rhs) const
{
    if (this->myX != rhs.myX) return false;
    if (this->myY != rhs.myY) return false;
    if (this->getNumRows() != rhs.getNumRows()) return false;
    if (this->getNumCols() != rhs.getNumCols()) return false;
    for (int i = 0; i < this->getNumRows(); ++i)
    {
        for (int j = 0; j < this->getNumCols(); ++j)
        {
            if (this->gridElements[i][j] != rhs.gridElements[i][j])
                return false;
        }
    }
    return true;
}


