/*
Author: your Xueren Ge Class: ECE 6122
Last Date Modified: 09-02-2020
Description:
This Program is used for Summation of Primes. To use it, you need to input a number,
 and then it will output the summation of primes which are less than your input number.
*/

#include <iostream>
#include <fstream>
using namespace std;

/*
This function is IsPrime, it is used to judge whether the number is a prime.
 If the number is a prime, it will output true, otherwise false.
*/
bool IsPrime(unsigned long INum)// INum is the input number
{
    // In the for loop, it checks whether all numbers less than INum can be divided
    for (int i = INum-1; i > 1; i--)
    {
        // the Inum can be divided by number i
        if (INum % i == 0)
        {
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[])
{
    // check the number of parameters
    if (argc < 2)
    {
        // Tell the user how to run the program
        cerr << "Usage: " << argv[0] << "Number" << endl;
        /* "Usage messages" are a conventional way of telling the user
         * how to run a program if they enter the command incorrectly.
         */
        return 1;
    }
    // define variable 'num' as the input number
    unsigned long num = atol(argv[1]);
    // initialize variable 'result' which records the summation of all primes
    int res = 0;
    // for loop is used to find all primes
    for (int i = 2; i <= num; i++)
    {
        if (IsPrime(i))
        {
            res += i;
        }
    }
    // write the value into output1.txt
    ofstream ofs ("./output1.txt", ofstream::out);
    ofs << res << endl;
    ofs.close();
    return 0;
}

