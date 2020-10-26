/*
Author: Xueren Ge
Class: ECE6122
Last Date Modified: 27-Sep-2020
Description:
The purpose of this file is to define MyGrid's
all member functions and member variables.
*/
#pragma once
#include <vector>
#include <string>
#include <fstream>

using namespace std;
/*
 The purpose of this MyGrid is to create a member variable gridElements that is a dynamic two-dimensional
 array of elements (type long) of m rows by n columns. The class also contains two long variables
 called myX and myY which indicates the upper left-hand location of element (0,0) of the grid. And define some
 functions to be implemented.
 */
class MyGrid
{

public:
    // read in the input files and correctly create the individual MyGrid objects
    bool loadGridFromFile(const string& filename);
    // sets all elements to 0
    void zeroOutGrid();
    // get MyGrid objects gridElement rows
    long getNumRows() const;
    // get MyGrid objects gridElement columns
    long getNumCols() const;
    // Add two MyGrid object
    MyGrid operator+(MyGrid const&) const;
    // Subtract two MyGrid object
    MyGrid operator-(MyGrid const&) const;
    // Adds a long to all the elements in the MyGrid object.
    MyGrid operator+(long const&) const;
    // Adds a MyGrid object to a long.
    friend MyGrid operator+(long const& lhs, MyGrid const& rhs);
    // Addition assignment
    MyGrid& operator+=(MyGrid const&);
    // Increment
    MyGrid& operator++(); // Prefix
    MyGrid operator++(int); // Postfix
    // decrement
    MyGrid& operator--(); // Prefix
    MyGrid operator--(int); // Postfix
    // multiplying all the elements by -1
    MyGrid operator-() const;
    // judge two MyGrid object are the same
    bool operator==(MyGrid const&) const;

    // this operator outputs the class using the same format as is used in reading in a MyGrid object.
    friend fstream& operator<<(fstream& os, const MyGrid& gridIn)
    {
        os << gridIn.myX << " " << gridIn.myY << endl;
        os << gridIn.getNumRows() << " " << gridIn.getNumCols() << endl;
        for (int i = 0; i < gridIn.getNumRows(); ++i)
        {
            for (int j = 0; j < gridIn.getNumCols(); ++j)
            {
                os << gridIn.gridElements[i][j] << " ";
            }
            os << endl;
        }
        return os;
    }

private:
    long myX, myY;
    vector<vector<long>> gridElements;
};

