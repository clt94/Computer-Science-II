/*
COPYRIGHT (C) 2019 Connor Taylor (clt94) All rights reserved
ASSGNA Delete Corresponding
Author: Connor Taylor
        clt94@zips.uakron.edu
Purpose: This program takes a c-string and edits it to remove repeating letters
         when comparing the first and last, second and second to last, etc... and
         puts it in order of first and last, second to last and second, third and
         third to last, etc... using smart pointers. Outputs the reversed order of
         the new array and the amount of repeats in the original.
*/

#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::unique_ptr;

// Precondition: c-string
// Postcondition: pointer to c-string
unique_ptr<char[]> delCorr(char []);

int main()
{
    // initializes original array
    const int SIZE = 10;
    char originalArray[SIZE];
    originalArray [0] = 'a';
    originalArray [1] = 'b';
    originalArray [2] = 'b';
    originalArray [3] = 'c';
    originalArray [4] = 'a';
    originalArray [5] = 'c';
    originalArray [6] = 'a';
    originalArray [7] = 'c';
    originalArray [8] = 'b';
    originalArray [9] = 'a';

    // initializes smart pointer c-string (I was unable to figure out how to get the actual size)
    unique_ptr<char[]> noRepeats(new char[SIZE]);
    // rearranges c-string
    noRepeats = delCorr(originalArray);

    int newSize = 0;
    // outputs the values of the new array in reverse order
    cout << "The New Array is: ";
    for (int i = SIZE - 1; i > -1; -- i)
    {
        if(noRepeats[i] != '\0')
        {
            ++ newSize;
            if (i != 0)
            {
                cout << noRepeats[i] << " ";
            }
            else
            {
                cout << noRepeats[i] << ".";
            }
        }
    }
    // outputs the amount of repeats in the original array
    cout << "\nAnd the original array has " << SIZE - newSize << " repeats.";

    return 0;
}

// Precondition: c-string
// Rearranges the c-string to remove repeats
// Postcondition: returns pointer to new c-string
unique_ptr<char[]> delCorr(char originalArray[])
{
    // finds the length of the array
    int arraySize = (*(&originalArray + 1) - originalArray) / 2 + 1;

    // initializes new array with updates size
    unique_ptr<char[]> newArray(new char[arraySize]);

    // fills in the new array with proper order and without repeats
    int index = 0;
    for(int i = 0; i < arraySize / 2; ++ i)
    {
        // this compares the beginning first to last character, second to second to last, etc...
        if(originalArray[i] != originalArray[arraySize - i - 1])
        {
            // this flips the second and second to last character to every iteration to achieve the out specified.
            if(index % 4 == 0)
            {
                newArray[index] = originalArray[i];
                ++ index;
                newArray[index] = originalArray[arraySize - i - 1];
                ++ index;
            }
            else
            {
                newArray[index] = originalArray[arraySize - i - 1];
                ++ index;
                newArray[index] = originalArray[i];
                ++ index;
            }
        }
        // sets repeats to null
        else
        {
            newArray[index] = '\0';
            ++ index;
            newArray[index] = '\0';
            ++ index;
        }
    }

    return newArray;
}
