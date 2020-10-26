# Multi-thread

This part requires you to install OpenMP. Follow the steps to install gcc(https://www.youtube.com/watch?v=0z-fCNNqfEg) and change the compiler.
In CmakeList, follow what I do in it. About the Problem, see more details in **Lab3.pdf**.

## Problem 1: Su Doku
  Su Doku(Janpanese meaning number place) is the name given to a popular puzzle concept. 
Its origin is unclear, but credit must be attributed to Leonhard Euler who invented
a similar, and much more difficult, puzzle idea called Latin Squares. The objective of Su Doku
puzzles, however, is to replace the blanks (or zeros) in a 9 by 9 grid in such that each row, column,
and 3 by 3 box contains each of the digits 1 to 9. Below is an example of a typical starting puzzle
grid and its solution grid. For more details, see https://www.projecteuler.net.
  In order to run it, input **input_sudoku.txt** when running. It will output **Lab3Prob1.txt**, It includes
the answer 50 Su Doku games. 

## Problem 2: Another ant on the move problem
  See details (https://brilliant.org/practice/monte-carlo/), using command line arguments like shown below
  **./a.out -N 100000 -g 6**, it will output Lab3Prob2.txt. If you are interested in Monte Carlo, see Monte Carlo Simulation.pdf.
  
## Problem 3: Using Monte Carlo to solve optimization problem
  This will output **Lab3Prob3.txt**
