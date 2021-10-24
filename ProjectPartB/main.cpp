/*
COPYRIGHT (C) 2019 Connor Taylor (clt94) All rights reserved
ProjectPartB
Author: Connor Taylor
        clt94@zips.uakron.edu
Purpose: Using linked lists and class Labs, allow a lab administrator
         to login a user, logout a user, search for a user's lab and computer
         number using a map, and displays a lab and all its computers. All users will be stored
         in a .txt file that can be used to recover users.
*/
#include <iostream>
#include <iomanip>
#include <time.h>
#include <stdlib.h>
#include <limits>
#include <fstream>
#include <string>
#include <map>
#include "Labs.h"
#include "LinkedList.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::numeric_limits;
using std::streamsize;
using std::fstream;
using std::map;
using std::pair;
using std::iterator;

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

// Precondition: None
// Postcondition: None
void availableLabs();

// Precondition: None
// Postcondition: None
void menu();

// Precondition: short input by reference, short low, and short high
// Postcondition: None
void validate(short&, short, short);

// Precondition: Int input by reference, int low, and int high
// Postcondition: None
void validate(int&, int, int);

// Precondition: short input by reference
// Postcondition: None
void validate(short&);

// Precondition: String input by reference
// Postcondition: None
void validate(string&);

// Precondition: LinkedList double pointer, fstream by reference
// Postcondition: None
void simulateLogin(LinkedList**, map<int, short>&, fstream&);


// Precondition: LinkedList double pointer, fstream by reference
// Postcondition: None
void simulateLogoff(LinkedList**, map<int, short>&, fstream&);

// Precondition: LinkedList double pointer
// Postcondition: None
void searchUser(map<int, short>&);

// Precondition: LinkedList double pointer
// Postcondition: None
void displayLab(LinkedList**);

// Precondition: fstream by reference, Labs by reference, constant char by reference
// Postcondition: None
void writeToLog(fstream&, Labs&, const char&);

// Precondition: fstream by reference, LinkedList double pointer
// Postcondition: None
void recoverUser(fstream&, LinkedList**);

int main()
{
    // seeds srand for rand only once in setUserID()
    srand(time(NULL));
    // declares fstream and opens tranlog.txt
    fstream transactionLog;
    transactionLog.open("tranlog.txt", std::ios::in |std::ios::out |std::ios::app);
    if(!transactionLog.is_open()) // checks if it is open and ends the program if it fails
    {
        cout << "tranlog.txt failed to open.";
        return 0;
    }
    map<int, short> users;
    // declares LinkedList
    LinkedList** list;
    list = new LinkedList*[NUMLABS];
    for(short i = 0; i < NUMLABS; ++i)
    {
        list[i] = new LinkedList(LABSIZES[i]);
    }
    // displays the names of the labs
    availableLabs();
    short choice;
    // do while loop based on users choice
    do
    {
        // displays menu and then takes input
        menu();
        cout << "\t\tYour choice: ";
        cin >> choice;
        validate(choice, 1, 6);
        // switch statement based on user input
        switch(choice)
        {
        case 1:
            // Option 1: Simulate Login
            simulateLogin(list, users, transactionLog);
            break;

        case 2:
            // Option 2: Simulate Logoff
            simulateLogoff(list, users, transactionLog);
            break;
        case 3:
            // Option 3: Search for a user
            searchUser(users);
            break;
        case 4:
            // Option 4: Displays a lab
            displayLab(list);
            break;
        case 5:
            // Option 5: Recovers a user from transaction log
            recoverUser(transactionLog, list);
            break;
        case 6:
            // Option 5: Ends program
            cout << "Ending program!" << endl;
            return 0;
        default:
            // Default statement in case input gets past validation
            cout << "Invalid choice!" << endl;
            break;
        }
        // Pauses program until the user presses enter
        cout << "\nPress enter to continue.";
        cin.ignore();
        cin.get();
        // exits while loop if option is five and switch statement fails
    }while(choice != 6);

    // closes file
    transactionLog.close();
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
    cout << " " << std::setfill('_') << std::setw(48) << " " << endl;
    cout << "|" << std::setfill(' ') << std::setw(48) << "|" << endl;
    cout << "|\t   Connor Taylor Incorporated\t\t|" << endl;
    cout << "|\t\tComputer Lab System\t\t|" << endl;
    cout << "|" << std::setfill('_') << std::setw(48) << "|" << endl;
    cout << "|" << std::setfill(' ') << std::setw(48) << "|" << endl;
    cout << "|\t\t     Main Menu\t\t\t|" << endl;
    cout << "|\t\t1) Simulate Login\t\t|" << endl;
    cout << "|\t\t2) Simulate Logoff\t\t|" << endl;
    cout << "|\t\t3) Search\t\t\t|" << endl;
    cout << "|\t\t4) Display a Lab\t\t|" << endl;
    cout << "|\t\t5) Recover a User\t\t|" << endl;
    cout << "|\t\t6) Quit\t\t\t\t|" << endl;
    cout << "|" << std::setfill('_') << std::setw(48) << "|" << endl;
}

// Precondition: short input by reference, short low, and short high
// Validates int input based on if it is an int and the low and high of the bounds
// Postcondition: None
void validate(short &input, short low, short high)
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
// Precondition: short input by reference
// Validates input based on if it is 15, 30, 45, and 60
// THIS IS SPECIFICALLY FOR TIME SPENT ON COMPUTER STATION
// Postcondition: None
void validate(short& input)
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

// Precondition: LinkedList double pointer, fstream by reference
// Simulates logging in a new user
// Postcondition: None
void simulateLogin(LinkedList** list, map<int, short>& users, fstream& transactionLog)
{
    Labs lab;
    short labNum, labComp, useTime;
    string name;

    // takes user input for which lab to sign into
    cout << "Enter the lab the user is signing in from (1-8): ";
    cin >> labNum;
    // validates user input
    validate(labNum, 1, NUMLABS);
    // checks if lab is full, exits function if full
    if(list[labNum - 1]->isFull())
    {
        cout << "Sorry, this lab is full. Please try again later." << endl;
        return;
    }
    lab.setLab(labNum); // sets users lab number

    // takes user input for lab computer to sign into
    cout << "Enter the computer system you are logging in from (1-" << LABSIZES[labNum - 1] <<"): ";
    cin >> labComp;
    // validates user input
    validate(labComp, 1, LABSIZES[labNum - 1]);
    // checks if computer is occupied, exits function if occupied
    if(list[labNum - 1]->isOccupied(labComp))
    {
        cout << "Sorry, this computer is already in use. Please try again later." << endl;
        return;
    }
    lab.setComputerStation(labComp); // sets user's computer station

    // creates userID and outputs it
    lab.setUserID();
    cout << "User id: ";
    lab.printUserID();
    cout << endl;

    // takes user's name
    cout << "Please enter the name of this user: ";
    cin.ignore();
    getline(cin, name);
    // validates users name
    validate(name);
    lab.setName(name);

    // takes user input for time spent at each computer
    cout << "Please enter the minutes of use for the workstation (15/30/45/60): ";
    cin >> useTime;
    // validates input to ensure it is either 15, 30, 45, or 60
    validate(useTime);
    lab.setTime(useTime);
    // inserts lab into LinkedList
    list[labNum - 1]->insertNode(lab);
    users.insert(pair<int, short>(lab.getUserID(), labComp));
    // writes user's info to tranlog.txt
    writeToLog(transactionLog, lab, 'I');
}

// Precondition: LinkedList double pointer, fstream by reference
// Simulates logging off a user
// Postcondition: None
void simulateLogoff(LinkedList** list, map<int, short>& users,fstream &transactionLog)
{
    // takes user input for userID to logoff
    Labs lab;
    int user;
    cout << "Enter the 5 digit number of the user to logoff: ";
    cin >> user;
    // validates input for 1 to 99,999
    validate(user, 1, 99999);
    // iterates through labs
    for(short i = 0; i < NUMLABS; ++i)
    {
        // enter if statement if user is found
        if(list[i]->deleteNode(user, lab))
        {
            // writes to log that the user was signed out, then exits function
            writeToLog(transactionLog, lab, 'O');
            return;
        }
    }
    // tells user that that userID is not logged into any computers
    cout << "User " << user << " is not logged in!" << endl;
}

// Precondition: LinkedList double pointer
// Searches for a user
// Postcondition: None
void searchUser(map<int, short>& users)
{
    /*
    // takes input of userID to search for
    int user;
    cout << "Enter the 5 digit number of the user to find: ";
    cin >> user;
    // validates userID from 1 to 99999
    validate(user, 1, 99999);
    // iterates through each lab
    for(short i = 0; i < NUMLABS; ++i)
    {
        // if the user is found exit function
        if(list[i]->findNode(user))
        {
            return;
        }
    }
    // tells user that that userID is not logged in
    cout << "User " << user << " is not logged in." << endl;
    */
}

// Precondition: LinkedList double pointer
// Displays all computers in a lab
// Postcondition: None
void displayLab(LinkedList** list)
{
    // takes user input for a lab
    short labNum;
    cout << "Please enter the lab to display: ";
    cin >> labNum;
    // validates labNum from 1 to size of NUMLABS
    validate(labNum, 1, NUMLABS);
    // outputs heading of display
    cout << "\nLAB STATUS" << endl;
    cout << "Lab #\t" << labNum << " for " << UNIVERSITYNAMES[labNum - 1] << endl;
    cout << "Computer Stations" << endl;
    // calls LinkedList function to display lab
    list[labNum - 1]->displayLab(LABSIZES[labNum - 1]);
}

// Precondition: fstream by reference, Labs by reference, constant char by reference
// Writes each users info to tranlog.txt
// Postcondition: None
void writeToLog(fstream &transactionLog, Labs &lab, const char &action)
{
    // gets current time
    time_t now = time(0);
    char* timeIn = ctime(&now);
    timeIn[20] = '\0';
    // inputs info to tranlog.txt
    transactionLog << timeIn << ',' << action << ' ' << lab.getUserID() << ' ' << lab.getTime() << ' ' << lab.getName() << ',' << '\n';
}

// Precondition: fstream by reference, LinkedList double pointer
// Recovers a user from the tranlog.txt and returns them to the lab
// Postcondition: None
void recoverUser(fstream &transactionLog, LinkedList** list)
{
    Labs lab;
    int userID, tempUserID;
    short labNum, useTime;
    string time, name;
    char action;

    // reset everything and go to the beginning of the file
    transactionLog.clear();
    transactionLog.seekg(0, std::ios::beg);

    // takes user input for userID to recover and validates
    cout << "Please enter a user to recover: ";
    cin >> userID;
    validate(userID, 1, 99999);

    // takes user input for the lab number and validates
    cout << "Please enter the lab user " << userID << " was in: ";
    cin >> labNum;
    validate(labNum, 1, NUMLABS);

    // checks if lab is full
    if(list[labNum]->isFull())
    {
        cout << "Sorry, this lab is full. Please try again later." << endl;
        return; // exits function if lab is full
    }

    // reads beginning time of each line until there is no more
    while(getline(transactionLog, time, ','))
    {
        // takes input from file
        transactionLog >> action >> tempUserID >> useTime;
        getline(transactionLog, name, ',');
        // if userID exits in text file enter if statement
        if(userID == tempUserID)
        {
            // creates all values of lab
            lab.setUserID(userID);
            lab.setName(name);
            lab.setTime(useTime);
            lab.setLab(labNum);
            lab.setComputerStation(list[labNum - 1]->findFirstOpen()); // finds first open computer in lab
            list[labNum - 1]->insertNode(lab); // inserts lab
            // Informs users where the userID was inserted
            cout << "User " << userID << " was restored to computer " << lab.getCompStation() << " in lab " << labNum << "!" << endl;
            // goes back to end of file
            transactionLog.clear();
            transactionLog.seekg(0, std::ios::end);
            return;
        }
    }
    // informs user the userId was not found
    cout << "Sorry, this user was not found." << endl;
    // returns to end of file
    transactionLog.clear();
    transactionLog.seekg(0, std::ios::end);
}
