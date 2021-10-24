/*
COPYRIGHT (C) 2019 Connor Taylor (clt94) All rights reserved
ProjectPartA
Author: Connor Taylor
        clt94@zips.uakron.edu
Purpose: Using dynamic memory and class Labs, allow a lab administrator
         to login a user, logout a user, search for a user's lab and computer
         number, and displays a lab and all its computers.
*/
#include <iostream>
#include <iomanip>
#include <time.h>
#include <stdlib.h>
#include <limits>

using std::cout;
using std::cin;
using std::endl;
using std::setfill;
using std::setw;
using std::string;
using std::numeric_limits;
using std::streamsize;

// Global Constants
// Number of computer labs
const int NUMLABS = 8;
// Number of computers in each lab
// I changed it to as unsigned int so it wouldn't throw a warning from comparing it to a signed int
const unsigned int LABSIZES[NUMLABS] = {19, 15, 24, 33, 61, 17, 55, 37};
// Names of university of each lab
const string UNIVERSITYNAMES[NUMLABS] = {"The University of Michigan", "The University of Pittsburgh",
                                            "Stanford University", "Arizona State University",
                                            "North Texas State University", "The University of Alabama, Huntsville",
                                            "Princeton University", "Duquesne University"};

// declares class Labs
class Labs
{
private:
    // private data for any declaration of Labs
    int userID;
    string name;
    int useTime;
public:
    // public constructor
    Labs()
    {
        userID = -1;
        name = " ";
        useTime = 0;
    }
    // setter functions for all of the private variables
    void setUserID() // takes a random number from 1 to 99999
    {   userID = 1 + rand() % 99999;    }
    void setUserID(int userID) // overloaded setter to manually set userID
    {   this->userID = userID;  }
    void setName(string& name)
    {   this->name = name;  }
    void setTime(int useTime)
    {   this->useTime = useTime;    }
    // getter functions to get all private variables
    int getUserID()
    {   return userID;  }
    string getName()
    {   return name;    }
    int getTime()
    {   return useTime;    }
    // prints userID in the correct format
    void printUserID()
    {   cout << setfill('0') << setw(5) << userID;  }
};

// Precondition: None
// Postcondition: None
void availableLabs();

// Precondition: None
// Postcondition: None
void menu();

// Precondition: Int by reference, int, int
// Postcondition: None
void validate(int&, int, int);

// Precondition: Int by reference
// Postcondition: None
void validate(int&);

// Precondition: String by reference
// Postcondition: None
void validate(string&);

// Precondition: Pointers to array of Labs
// Postcondition: None
void simulateLogin(Labs*[]);

// Precondition: Pointers to array of Labs
// Postcondition: None
void simulateLogoff(Labs*[]);

// Precondition: Pointers to array of Labs
// Postcondition: None
void searchUser(Labs*[]);

// Precondition: Pointers to array of Labs
// Postcondition: None
void displayLab(Labs*[]);

// Precondition: Int, pointers to array of Labs
// Postcondition: bool
bool isFull(int, Labs*[]);

// Precondition: Int, int, pointers to array of Labs
// Postcondition: bool
bool occupied(int, int, Labs*[]);

int main()
{
    // seeds srand for rand only once in setUserID()
    srand(time(NULL));
    Labs *pointers[NUMLABS];
    // initializes all default values of the jagged array
    for(size_t i{0}; i < NUMLABS; ++i)
    {
        pointers[i] = new Labs[LABSIZES[i]];
    }
    // displays the names of the labs
    availableLabs();
    int choice;
    // do while loop based on users choice
    do
    {
        // displays menu and then takes input
        menu();
        cout << "\t\tYour choice: ";
        cin >> choice;
        validate(choice, 1, 5);
        // switch statement based on user input
        switch(choice)
        {
        case 1:
            // Option 1: Simulate Login
            simulateLogin(pointers);
            break;
        case 2:
            // Option 2: Simulate Logoff
            simulateLogoff(pointers);
            break;
        case 3:
            // Option 3: Search for a user
            searchUser(pointers);
            break;
        case 4:
            // Option 4: Displays a lab
            displayLab(pointers);
            break;
        case 5:
            // Option 5: Ends program
            cout << "Ending program!" << endl;
            return 0;
        default:
            // Default statement in case input gets past validation
            cout << "Invalid choice!" << endl;
            break;
        }
        // Pauses program till users presses enter
        cout << "\nPress enter to continue.";
        cin.ignore();
        cin.get();
        // exits while loop if option is five and switch statement fails
    }while(choice != 5);
    return 0;
}

// Precondition: None
// Outputs all lab numbers and university names
// Postcondition: None
void availableLabs()
{
    cout << "\tWelcome - here is our list of available labs" << endl;
    // iterates through array of university names in case of future changes
    for(size_t i{1}; i <= NUMLABS; ++i)
    {
        cout << "lab # " << i << " for " << UNIVERSITYNAMES[i - 1] << endl;
    }
}

// Precondition: None
// Outputs all options
// Postcondition: None
void menu()
{
    cout << " " << setfill('_') << setw(48) << " " << endl;
    cout << "|" << setfill(' ') << setw(48) << "|" << endl;
    cout << "|\t   Connor Taylor Incorporated\t\t|" << endl;
    cout << "|\t\tComputer Lab System\t\t|" << endl;
    cout << "|" << setfill('_') << setw(48) << "|" << endl;
    cout << "|" << setfill(' ') << setw(48) << "|" << endl;
    cout << "|\t\t     Main Menu\t\t\t|" << endl;
    cout << "|\t\t1) Simulate Login\t\t|" << endl;
    cout << "|\t\t2) Simulate Logoff\t\t|" << endl;
    cout << "|\t\t3) Search\t\t\t|" << endl;
    cout << "|\t\t4) Display a Lab\t\t|" << endl;
    cout << "|\t\t5) Quit\t\t\t\t|" << endl;
    cout << "|" << setfill('_') << setw(48) << "|" << endl;
}

// Precondition: Int input by reference, int low, and int high
// Validates int input based on if it is an int and the low and high of the bounds
// Postcondition: None
void validate(int &input, int low, int high)
{
    // checks for valid values then checks bounds
    while(cin.fail() || input < low || input > high)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        // reprompts user for input based on bounds
        cout << "Please enter a number from " << low << " to " << high << ": ";
        cin >> input;
    }
}

// Precondition: Int input by reference
// Validates input based on if it is 15, 30, 45, and 60
// THIS IS SPECIFICALLY FOR TIME SPENT ON COMPUTER STATION
// Postcondition: None
void validate(int& input)
{
    while(cin.fail() || (input != 15 && input != 30 && input != 45 && input != 60)) // checks for valid values then checks bounds
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Please enter either 15, 30, 45, or 60: "; // reprompts user
        cin >> input;
    }
}

// Precondition: String input by reference
// Validates string input to ensure string is not empty and does not exceed 35 characters
// Postcondition: None
void validate(string& input)
{
    // checks if string is empty or if it exceeds 35 characters
    while(input.empty() || input.length() > 35)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Please enter a valid name: "; // reprompts user
        getline(cin, input);
    }
}

// Precondition: Labs pointer to array
// Simulates logging in a new user
// Postcondition: None
void simulateLogin(Labs* pointers[])
{
    // takes user input for which lab to sign into
    int labNum;
    cout << "Enter the lab the user is signing in from (1-8): ";
    cin >> labNum;
    // validates user input
    validate(labNum, 1, NUMLABS);
    // checks if lab is full, exits function if full
    if(isFull(labNum - 1, pointers))
    {
        cout << "This lab is full!" << endl;
        return;
    }
    // takes user input for lab computer to sign into
    int labComp;
    cout << "Enter the computer system you are logging in from (1-" << LABSIZES[labNum - 1] <<"): ";
    cin >> labComp;
    // validates user input
    validate(labComp, 1, LABSIZES[labNum - 1]);
    // checks if computer is occupied, exits function if occupied
    if(occupied(labNum - 1, labComp - 1, pointers))
    {
        cout << "This computer is already in use!" << endl;
        return;
    }
    // creates userID and outputs it
    pointers[labNum - 1][labComp - 1].setUserID();
    cout << "User id: ";
    pointers[labNum - 1][labComp - 1].printUserID();
    cout << endl;
    // takes user's name
    string name;
    cout << "Please enter the name of this user: ";
    cin.ignore();
    getline(cin, name);
    // validates users name
    validate(name);
    pointers[labNum - 1][labComp - 1].setName(name);
    int useTime;
    // takes user input for time spent at each computer
    cout << "Please enter the minutes of use for the workstation (15/30/45/60): ";
    cin >> useTime;
    // validates input to ensure it is either 15, 30, 45, or 60
    validate(useTime);
    pointers[labNum - 1][labComp - 1].setTime(useTime);
}

// Precondition: Int labNum, Lab pointer to array
// Checks if a lab is full
// Postcondition: returns a bool
bool isFull(int labNum, Labs* pointers[])
{
    // iterates through array to see if there are open computers
    for(size_t i{0}; i < LABSIZES[labNum]; ++i)
    {
        if(pointers[labNum][i].getUserID() == -1)
        {
            // returns false if a computer is open
            return false;
        }
    }
    // returns true if all computers are occupied
    return true;
}

// Precondition: Int labNum, int labComp, Labs pointer to array
// Checks if computer is occupied
// Postcondition: None
bool occupied(int labNum, int labComp, Labs* pointers[])
{
    // returns false if computer is not occupied
    if(pointers[labNum][labComp].getUserID() == -1)
    {
        return false;
    }
    // returns true if computer is occupied
    return true;
}

// Precondition: Labs pointers to array
// Simulates logging off a user
// Postcondition: None
void simulateLogoff(Labs* pointers[])
{
    // takes user input for userID to logoff
    int user;
    cout << "Enter the 5 digit number of the user to logoff: ";
    cin >> user;
    // validates input for 1 to 99,999
    validate(user, 1, 99999);
    // iterates through pointers
    for(size_t i{0}; i < NUMLABS; ++i)
    {
        for(size_t j{0}; j < LABSIZES[i]; ++j)
        {
            // resets user to default values if user is found and exits function
            if(pointers[i][j].getUserID() == user)
            {
                string temp = " ";
                pointers[i][j].setUserID(-1);
                pointers[i][j].setName(temp); // would not accept string constant
                pointers[i][j].setTime(0);
                cout << "User " << user << " was logged out from lab " << i + 1 << " and computer " << j + 1 << endl;
                return;
            }
        }
    }
    // tells user that that userID is not logged into any computers
    cout << "User " << user << " is not logged in!" << endl;
}

// Precondition: Labs pointers to array
// Searches for a user
// Postcondition: None
void searchUser(Labs* pointers[])
{
    // takes input of userID to search for
    int user;
    cout << "Enter the 5 digit number of the user to find: ";
    cin >> user;
    // validates userID from 1 to 99999
    validate(user, 1, 99999);
    // iterates through pointers
    for(size_t i{0}; i < NUMLABS; ++i)
    {
        for(size_t j{0}; j < LABSIZES[i]; ++j)
        {
            // when user is found outputs the lab and computer and exits the function
            if(pointers[i][j].getUserID() == user)
            {
                cout << "User " << user << " is in lab " << i + 1 << " at computer " << j + 1 << " for " << pointers[i][j].getTime() << " minutes" << endl;
                return;
            }
        }
    }
    // tells user that that userID is not logged in
    cout << "User " << user << " is not logged in" << endl;
}

// Precondition: Labs pointers to array
// Displays all computers in a lab
// Postcondition: None
void displayLab(Labs* pointers[])
{
    // takes user input for a lab
    int labNum;
    cout << "Please enter the lab to display: ";
    cin >> labNum;
    // validates labNum from 1 to size of NUMLABS
    validate(labNum, 1, NUMLABS);
    // outputs heading of display
    cout << "\nLAB STATUS" << endl;
    cout << "Lab #\t" << labNum << " for " << UNIVERSITYNAMES[labNum - 1] << endl;
    cout << "Computer Stations" << endl;
    // iterates through lab
    for(size_t i{0}; i < LABSIZES[labNum - 1]; ++i)
    {
        // if computer is not occupied outputs computer number and empty
        if(pointers[labNum - 1][i].getUserID() == -1)
        {
            cout << setfill(' ') << setw(2) << i + 1 << " : " << "empty  ";
        }
        // if computer is occupied outputs computer number and userID
        else
        {
            cout << setfill(' ') << setw(2) << i + 1 << " : ";
            pointers[labNum - 1][i].printUserID();
            cout << "  ";
        }
        // starts new line every 5 lines
        if((i + 1) % 5 == 0)
        {
            cout << endl;
        }
    }
}
