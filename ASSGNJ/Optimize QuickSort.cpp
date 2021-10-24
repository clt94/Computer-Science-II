/*
This program and the utility programs are useful for measurements of run times.

In this example it measures the runtimes of 3 standard template library sort algorithms

The value for our Data Structures class is to have an example of measuring runtime complexity

Note that this program uses three different algorithms (for sorting) as an example.
To use it for other algorithms, the parameters in the template function (Container) will need to be changed
 */

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <iterator>
#include <algorithm>    // std::random_shuffle
#include "Complexity_Timer.hpp"
#include "Complexity_Recorder.hpp"


// i left this here b/c i don't want to expend energy
using namespace std;

// timer
timer timer1;

// U can be any type we want to test. here it's the type of data in the sequence to be sorted; can be changed to any other type for which assignment (=) and less-than comparisons (<) are defined.
typedef int U;

// experiment will involve timing of 3 algorithms and that the number of "trials" will be 7. By a trial is meant timing of the algorithm for inputs of a single length;
// rather than taking a single such measurement we take seven measurements with different randomly generated inputs and compute their median. (The median computation is done
// in class recorder.) The median is used here rather than the mean because it is less susceptible to fluctuation due to possibly large fluctuations in the individual times.
const int number_of_algorithms = 3;
const int number_of_trials = 7;

// factor is &&&&&
const int factor = 1000;

// Prototypes for quicksort
void swap(int &, int &);
template <class container>
int partition(container &, int, int);
template <class container>
void quicksort(container &, int, int);

// This template function is to specify which algorithms are used in the timing experiment
template <class container>
inline void algorithm(int k, container &x, int BigK)
{
    switch (k)
    {
        case 0: stable_sort(x.begin(), x.end());
            break;
        case 1: sort(x.begin(), x.end());
            break;
        //case 2: partial_sort(x.begin(), x.end(), x.end());
        case 2: quicksort(x, 0, x.size());
    }
}

// SORT: (the Quicksort algorithm, using the median-of-3 method of choosing pivot elements for partitioning) from STL
// PARTIAL SORT: (Heapsort) - Partially sort elements in range from STL
// STABLE SORT: sorts the elements in the range [first,last), like sort, but preserves the relative order of the elements with equivalent values

const char* headings[number_of_algorithms] =
{"|  stable sort   ",
 "|      sort      ",
// "|  partial sort  ",
 "|   quick sort   "};


int main()
{
    int N0, N1, N2, N, K;
    N1 = 1;    // smallest sequence
    N2 = 1000; // largest sequence

// for our outputting of the results
    ofstream ofs("results.txt");

// this is going to hold the measurements
    vector<recorder<timer> > stats(number_of_algorithms);

// The "U" is the type for the vectors x and y (poorly named, i know). Using the largest sequence multiplied by factor to allocate memory
    vector<U> x, y;
    x.reserve(N2*factor);
    y.reserve(N2*factor);


// The times are taken for short computations by repeating those computations a number of times
// (controlled by the variable repetitions), so that they take long enough to register nonzero times.
// In our example where N1 = 1(meaning a sequence of length 1,000 (or, more generally, 1 * factor),
// then the time will be computed for executing the algorithm 32 times
   int repetitions = max(32/N1, 1);

    cout << "____";
    for (int i = 0; i < number_of_algorithms; ++i)
      cout << headings[i];
    cout << endl;

    cout << "Size";
    for (int i = 0; i < number_of_algorithms; ++i)
      cout << "|      Time      ";
    cout << endl;



    for (N0 = N1; N0 <= N2; N0 *= 2)
    {

        N = N0 * factor;

        K = N/2;

        for (int i = 0; i < N; ++i)
            x.push_back(i);

        cout << setw(4) << N0 << flush;
        ofs << setw(4) << N0;

        //int p;


        for (int i = 0; i < number_of_algorithms; ++i)
            stats[i].reset();

        for (int j = 0; j < number_of_trials; ++j)
        {

            random_shuffle(x.begin(), x.end());
            y = x;

// Notice here we repeat the computation repetitions # of times, not for each one, and we record the total time.
// (The repetitions factor is divided out when the time is later reported on the output stream.)
            for (int i = 0; i < number_of_algorithms; ++i)
            {
               timer1.restart();
               for (int k = 0; k < repetitions; ++k)
               {
                 x = y;
                 algorithm(i, x, K);
               }
               timer1.stop();
               stats[i].record(timer1);
            }
        } // end of trials loop

        for (int i = 0; i < number_of_algorithms; ++i)
        {
            stats[i].report(cout, repetitions);
            stats[i].report(ofs, repetitions);
        }

        cout << endl;
        ofs << endl;

        x.erase(x.begin(), x.end());

        if (repetitions > 1)
            repetitions /= 2;

// Notice we restore the input sequence before each call of the algorithm; b/c these algorithms typically
//  would perform differently on already-sorted sequences than on random ones.

    }

    return 0;

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
template <class container>
int partition(container &array, int first, int last)
{
    int pivotValue, pivotIndex, mid;
    mid = (first + last) / 2; // gets mid point of array
    swap(array[first], array[mid]);
    pivotIndex = first; // value to index through array
    pivotValue = array[first]; // value at the pivotIndex
    for (int scan = first + 1; scan <= last; ++scan) // iterates through array
    {
        if (array[scan] < pivotValue) // if the value is less than pivotValue
        {
            ++pivotIndex; // iterates to the next value in the array
            swap(array[scan], array[pivotIndex]);
        }
    }
    swap(array[first], array[pivotIndex]);
    return pivotIndex;
}

/*
 * Recursive quicksort
 */
template <class container>
void quicksort(container &array, int first, int last)
{
    int pivotPoint;
    if (first < last)
    {
        pivotPoint = partition(array, first, last);
        quicksort(array, first, pivotPoint - 1); // calls quicksort to sort array until one before pivotPoint
        quicksort(array, pivotPoint + 1, last); // calls quicksort to sort array starting from pivotPoint plus one
    }
}
