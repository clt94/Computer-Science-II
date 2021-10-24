#include "Labs.h"

// public constructor
Labs::Labs()
{
    user.userID = -1;
    user.name = " ";
    user.useTime = 0;
    user.lab = 0;
    user.computerStation = 0;
}

// copy constructor
Labs::Labs(Labs &lab)
{
    user.userID = lab.getUserID();
    user.name = lab.getName();
    user.useTime = lab.getTime();
    user.lab = lab.getLab();
    user.computerStation = lab.getCompStation();
}

// Precondition: None
// Sets userID to a random int
// Postcondition: None
void Labs::setUserID() // takes a random number from 1 to 99999
{   user.userID = 1 + rand() % 99999;    }

// Precondition: int
// overloaded setter to manually set userID
// Postcondition: None
void Labs::setUserID(int userID)
{   this->user.userID = userID;  }

// Precondition: string by reference
// Sets the user's name
// Postcondition: None
void Labs::setName(string& name)
{   this->user.name = name;  }

// Precondition: int
// Sets the time used by each user on a computer
// Postcondition: None
void Labs::setTime(short useTime)
{   this->user.useTime = useTime;    }

// Precondition: short
// Sets the lab number used by each user on a computer
// Postcondition: None
void Labs::setLab(short labNum)
{   this->user.lab = labNum;    }

// Precondition: short
// Sets the computer station used by each user on a computer
// Postcondition: None
void Labs::setComputerStation(short computerStation)
{   this->user.computerStation = computerStation;   }


// Precondition: None
// Getter function to get userID
// Postcondition: int
int Labs::getUserID() const
{   return user.userID;  }

// Precondition: None
// Getter function to get name
// Postcondition: string
string Labs::getName() const
{   return user.name;    }

// Precondition: None
// Getter function to get useTime
// Postcondition: int
short Labs::getTime() const
{   return user.useTime;    }

// Precondition: None
// Getter function to get lab number
// Postcondition: int
short Labs::getLab() const
{   return user.lab;    }

// Precondition: None
// Getter function to get computer station
// Postcondition: int
short Labs::getCompStation() const
{   return user.computerStation;    }

// Precondition: None
// Prints userID in the correct format
// Postcondition: None
void Labs::printUserID() const
{   std::cout << std::setfill('0') << std::setw(5) << user.userID;  }
