/*
Author: Xueren Ge
Class: ECE6122
Last Date Modified: 13-Oct-2020
Description:
The purpose of this file is to use multi-threads to solve the problem
of Sudoku Puzzles. To run this file,you need to input input_sudoku.txt,
and it will output a file Lab3Prob1.txt.
The main.cpp file is provided for you to test class(SudokuGrid) functionality.
*/
#include <iostream>
#include <fstream>
#include <mutex>
#include <thread>
#include "Sudoku.h"

using namespace std;

mutex outFileMutex;
mutex inFileMutex;
fstream outFile;
fstream inFile;

void solveSudokuPuzzles()
{
    SudokuGrid tempGrid;
    do{
        // read in
        inFileMutex.lock();
        inFile >> tempGrid;
        inFileMutex.unlock();
        // solve
        tempGrid.solve();
        // output
        outFileMutex.lock();
        outFile << tempGrid;
        outFileMutex.unlock();
    } while (inFile.peek() != EOF);
}

int main(int argc, char* argv[])
{
    outFile.open("Lab3Prob1.txt", fstream::out);
    inFile.open(argv[1], ios::in);
    // dynamically determine the maximum number of threads
    unsigned int thread_count = thread::hardware_concurrency();
    vector <thread> threads;
    // spawn threads to solve SudokuPuzzles
    for (int i = 0; i < thread_count; ++i)
        threads.push_back(thread(solveSudokuPuzzles));

    // join the threads
    for (auto& th : threads)
        th.join();
    return 0;
}
