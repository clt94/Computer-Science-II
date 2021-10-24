/*
COPYRIGHT (C) 2019 Connor Taylor (clt94) All rights reserved
ASSGNB Array of Structs
Author: Connor Taylor
        clt94@zips.uakron.edu
Purpose: Using an array of structs get the income and tax rate
         for several citizens, verifying their inputs, and outputting
         their taxes.
*/
#include <iostream>
#include <limits>

using std::cin;
using std::cout;
using std::endl;
using std::numeric_limits;
using std::streamsize;
using std::ios;

// Declares a struct with an int for the tax payer's number, and floats
// for their tax rate, income, and their due taxes.
struct taxPayer
{
    int taxPayer;
    float taxRate;
    float income;
    float taxes;
};

// The size of the array of tax payers
const int SIZE = 2;

// Precondition: Pointer to tax payer
// Postcondition: None
void taxTaker(taxPayer *);
void taxPrint(taxPayer *);

int main()
{
    // declares array of taxPayer size
    taxPayer citizen[SIZE];
    // takes and validates inputs
    taxTaker(citizen);
    // outputs each tax payers taxes
    taxPrint(citizen);
    return 0;
}

// Precondition: Array of taxPayer
// Takes inputs and validates it
// Postcondition: None
void taxTaker(taxPayer citizen[])
{
    cout << "Please enter the annual income and tax rate for " << SIZE << " tax payers:" << endl;

    for (int i = 0; i < SIZE; ++ i)
    {
        // puts in the tax payer's number
        citizen[i].taxPayer = i + 1;

        // takes input and validates for tax payer's income
        cout << "\nEnter this year's income for tax payer " << citizen[i].taxPayer << ": ";
        cin >> citizen[i].income;
        while(cin.fail() || citizen[i].income < 0)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Enter a number greater than 0: ";
            cin >> citizen[i].income;
        }

        // takes input and validates for tax payer's tax rate
        cout << "Enter the tax rate for tax payer # " << i + 1 << ": ";
        cin >> citizen[i].taxRate;
        while(cin.fail() || citizen[i].taxRate < 0.01 || citizen[i].taxRate > 9.9)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Enter a number greater than 0 and less than 10: ";
            cin >> citizen[i].taxRate;
        }
    }
}

// Precondition: Array of taxPayer
// Takes inputs and validates it
// Postcondition: None
void taxPrint(taxPayer citizen[])
{
    cout << "\nTaxes due for this year:\n" << endl;

    // set decimal format to 2
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);
    for(int i = 0; i < SIZE; ++ i)
    {
        // calculates tax payer's taxes
        citizen[i].taxes = citizen[i].income * (citizen[i].taxRate / 100.0);

        // outputs each tax payer's taxes
        cout << "Tax payer # " << citizen[i].taxPayer << ": $ " << citizen[i].taxes << endl;
    }
}
