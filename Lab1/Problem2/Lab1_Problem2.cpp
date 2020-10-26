/*
Author: your Xueren Ge Class: ECE 6122
Last Date Modified: 09-02-2020
Description:
This Program is used for Summation of resulting Collatz Sequence. To use it, you need to input a number,
 and then it will output the summation of Collatz Sequence.
*/
#include <iostream>
#include <fstream>
using namespace std;

int main(int argc,char* argv[])
{
    // Check the number of parameters
    if (argc < 2) {
        // Tell the user how to run the program
        std::cerr << "Usage: " << argv[0] << "Number" << std::endl;
        /* "Usage messages" are a conventional way of telling the user
         * how to run a program if they enter the command incorrectly.
         */
        return 1;
    }
    // define variable 'num' as the input number
    unsigned long num = atol(argv[1]);
    // initialize variable 'result' which records the summation of Collatz Sequence
    int res = num;
    // calculate the Collatz Sequence until the last one is 1
    while (num != 1 && num != 0)
    {
        // num is odd
        if (num % 2 == 1)
        {
            num = 3 * num + 1;
        }
        // num is even
        else
        {
            num = num / 2;
        }
        // calculate the sum of Collatz Sequence
        res += num;
    }
    // write the value into output2.txt
    ofstream ofs ("./output2.txt", ofstream::out);
    ofs << res << endl;
    ofs.close();
    return 0;
}
