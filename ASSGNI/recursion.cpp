/*
   COPYRIGHT (C) 2019 Connor (clt94) All rights reserved.
   CS Assignment I
   Author.  Connor Taylor
            clt94@zips.uakron.edu
   Version. 1.01 11.17.2019
   Purpose: This program populates an array with the Fibonacci sequence using recursive function
            and then uses a quicksort function that uses recursion.
*/
#include <iostream>

// prototypes
template <class T>
void printarray(const T[], int);
void chew_system_stack();

/*
 * Recursive version of fibonacci
 */
int fibrecurse(int n)
{
    if(n <= 0) // first value is 0
    {
        return 0;
    }
    else if(n == 1) // second value is 1
    {
        return 1;
    }
    else // gets value to n - 1 and n - 2 and adds them
    {
        return fibrecurse(n - 1) + fibrecurse(n - 2);
    }
}

/*
 * Iterative (loop) version of fibonacci
 */
int fibiterate(int n)
{

    if(n == 0)
    {
        return 0;
    }
    else
    {
        int nMinus2 = 1;
        int nMinus1 = 1;
        int current = 1;
        for(int i = 3; i <= n; ++ i)
        {
            current = nMinus1 + nMinus2;
            nMinus2 = nMinus1;
            nMinus1 = current;
        }
        return current;
    }
}

// Precondition: two ints passed by reference
// Swaps the two values
// Postcondition: none
void swap(int& value1, int& value2)
{
    int temp = value1;
    value1 = value2;
    value2 = temp;
}

// Precondition: T array, int, and int
// Partitions array
// Postcondition: returns int
template <class T>
int partition(T ar[], int first, int last)
{
    int pivotValue, pivotIndex, mid;
    mid = (first + last) / 2; // gets mid point of array
    swap(ar[first], ar[mid]);
    pivotIndex = first; // value to index through array
    pivotValue = ar[first]; // value at the pivotIndex
    for (int scan = first + 1; scan <= last; scan++) // iterates through array
    {
        if (ar[scan] < pivotValue) // if the value is less than pivotValue
        {
            pivotIndex++; // iterates to the next value in the array
            swap(ar[scan], ar[pivotIndex]);
        }
    }
    swap(ar[first], ar[pivotIndex]);
    return pivotIndex;
}

/*
 * Recursive quicksort
 */
template <class T>
void quicksort(T ar[], int first, int last)
{
    int pivotPoint;
    if (first < last)
    {
        pivotPoint = partition(ar, first, last);
        quicksort(ar, first, pivotPoint - 1); // calls quicksort to sort array until one before pivotPoint
        quicksort(ar, pivotPoint + 1, last); // calls quicksort to sort array starting from pivotPoint plus one
    }
}


int main()
{
    const int FIBLOOPS = 10;
    const int ARSIZ = 16;
    int ar[ARSIZ];

    std::cout << "Recursive fib: ";
    for(int i = 0; i < FIBLOOPS; ++i)
    {
        std::cout << fibrecurse(i) << " ";
    }
    std::cout << std::endl;
    std::cout << "Iterative fib: ";
    for(int i = 0; i < FIBLOOPS; ++i)
    {
        std::cout << fibiterate(i) << " ";
    }
    std::cout << std::endl;

    std::cout << "Quicksort:" << std::endl;
    // populate random array
    for(int i = 0; i < ARSIZ; ++i)
    {
        ar[i] = (i * 3037) % 2099;  // prime numbers! again!
    }
    printarray(ar, ARSIZ);
    quicksort(ar, 0, ARSIZ-1);
    printarray(ar, ARSIZ);

//    std::cout << "Chewing system stack:" << std::endl;
//    chew_system_stack();

    return 0;
}

/*  utility functions, do not modify  */
template <class T>
void printarray(const T ar[], int s)
{
    for(int i = 0; i < s; ++i)
    {
        std::cout << ar[i] << " ";
    }
    std::cout << std::endl;
}

void printstackpointer()
{
    void * stack_pointer;
    // inline assembly language to get stack pointer
    __asm__ __volatile__("movl  %%esp,%%eax"
                             :"=a"(stack_pointer)
                             );
    std::cout << stack_pointer << std::endl;
}

void chew_system_stack()
{
    // Feel free to play with this, but please
    // do NOT enable this for your final commit!
    printstackpointer();
    chew_system_stack();
}
/* end utilities */
