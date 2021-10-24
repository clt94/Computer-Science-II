#ifndef LABS_H_INCLUDED
#define LABS_H_INCLUDED
#include <iostream>
#include <iomanip>

using std::string;

// declares class Labs
class Labs
{
private:
    // private data for any declaration of Labs
    struct UserInfo
    {
        int userID;
        string name;
        short useTime;
        short lab;
        short computerStation;
    };
    UserInfo user;
public:
    // default constructor
    Labs();
    // copy constructor
    Labs(Labs&);
    // Precondition: None
    // Postcondition: None
    void setUserID();
    // Precondition: int
    // Postcondition: None
    void setUserID(int);
    // Precondition: string by reference
    // Postcondition: None
    void setName(string&);
    // Precondition: short
    // Postcondition: None
    void setTime(short);
    // Precondition: short
    // Postcondition: None
    void setLab(short);
    // Precondition: short
    // Postcondition: None
    void setComputerStation(short);
    // Precondition: None
    // Postcondition: int
    int getUserID() const;
    // Precondition: None
    // Postcondition: string
    string getName() const;
    // Precondition: None
    // Postcondition: short
    short getTime() const;
    // Precondition: None
    // Postcondition: short
    short getLab() const;
    // Precondition: None
    // Postcondition: short
    short getCompStation() const;
    // Precondition: None
    // Postcondition: None
    void printUserID() const;
};

#endif // LABS_H_INCLUDED
