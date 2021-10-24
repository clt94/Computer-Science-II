#include "LinkedList.h"
#include <iostream>

// Default constructor
LinkedList::LinkedList()
{
    head = nullptr;
    count = 0;
}

// Constructor to set size
LinkedList::LinkedList(short size)
{
    this->size = size;
    head = nullptr;
    count = 0;
}

// Precondition: short
// outputs lab
// Postcondition: None
void LinkedList::displayLab(short labSize) const
{
    ListNode* nodePtr;  // To move through the list
    short tempCount;

    // Position nodePtr at the head of the list.
    nodePtr = head;
    tempCount = 0;
    for(short i = 0; i < labSize; ++i)
    {
        ++tempCount;
        // if lab does not exist outputs empty
        if(nodePtr == nullptr || i + 1 != nodePtr->lab.getCompStation())
        {
            std::cout << std::setfill(' ') << std::setw(2) << i + 1 << " : " << "empty  ";
        }
        else // outputs lab
        {
            std::cout << std::setfill(' ') << std::setw(2) << i + 1 << " : ";
            nodePtr->lab.printUserID();
            std::cout << "  ";
            // Move to the next node.
            nodePtr = nodePtr->next;
        }
        // starts new line every 5 lines
        if(tempCount % 5 == 0)
        {
            std::cout << std::endl;
        }

    }
    std::cout << std::endl;
}

// Precondition: Labs by reference
// Inserts node in order by computer station
// Postcondition: None
void LinkedList::insertNode(Labs &newLab)
{
    // initializes a newNode to hold the character
    ListNode* newNode;
    ListNode* nodePtr;
    ListNode* previousNode;

    // initializes a nodePtr to travel through the list
    newNode = new ListNode;
    newNode->lab = newLab;
    // initializes a node that will be the value previous to the head of the list
    previousNode = nullptr;

    // if the list is empty then the node will be put it at the start
    if(head == nullptr)
    {
        head = newNode;
        newNode->next = nullptr;
        ++count;
    }
    else if(isFull()) // checks if lab is full
    {
        std::cout << "Sorry, this lab is full. Please try again later." << std::endl;
    }
    else if(isOccupied(nodePtr->lab.getCompStation())) // checks if computer is occupied
    {
        std::cout << "Sorry, this computer is occupied. Please try again later." << std::endl;
    }
    else // otherwise inserts node
    {
        // sets nodePtr to head so it can begin at the start of the list
        nodePtr = head;
        // loop while nodePtr has a value and if that value of nodePtr is higher than the computer station to insert, if not continue through the list
        while(nodePtr != nullptr && nodePtr->lab.getCompStation() < newLab.getCompStation())
        {
            // sets previousNode to the node just being used
            previousNode = nodePtr;
            // sets nodePtr to next node to open a hole for the newNode to be inserted
            nodePtr = nodePtr->next;
        }
        // inserts newNode at head of the list if the first value is less than the newNode
        if(previousNode == nullptr)
        {
            head = newNode;
            newNode->next = nodePtr;
        }
        // inserts newNode below first value greater than itself
        else
        {
            previousNode->next = newNode; // inserts the value of newNode into the value for next in the previous node
            newNode->next = nodePtr; // sets the next value of the newNode to the nodePtr
        }
        ++count;
    }
}

// Precondition: short, Labs by reference
// Deletes a node by userID
// Postcondition: bool
bool LinkedList::deleteNode(short user, Labs &lab)
{
    // creates pointers to traverse the list
    ListNode* nodePtr;
    ListNode* previousNode;

    // exits function if list is empty
    if(!head)
    {
        //std::cout << "User " << user << " is not logged in!" << std::endl;
        return false;
    }

    // if the head of the list is the character then delete head and set it to the next pointer in the list
    if(head->lab.getUserID() == user)
    {
        // outputs lab being logged out and deletes
        lab = head->lab;
        std::cout << "User " << user << " was logged out from lab " << head->lab.getLab() << " and computer "
                  << head->lab.getCompStation() << " for " << head->lab.getTime() << " minutes." << std::endl;
        nodePtr = head->next;
        delete head;
        head = nodePtr;
        count = 0;
        return true;
    }
    else
    {
        // sets nodePtr to head to traverse the list
        nodePtr = head;
        // while there is a value in the list and no value is equal to the character traverse the list
        while(nodePtr != nullptr && nodePtr->lab.getUserID() != user)
        {
            previousNode = nodePtr;
            nodePtr = nodePtr->next;
        }
        // if the nodePtr does exist delete it
        if(nodePtr)
        {
            // outputs node being logged out and deleted
            lab = nodePtr->lab;
            std::cout << "User " << user << " was logged out from lab " << nodePtr->lab.getLab() << " and computer "
                      << nodePtr->lab.getCompStation() << " for " << nodePtr->lab.getTime() << " minutes." << std::endl;
            previousNode->next = nodePtr->next; // adjusts previous node to be after where the deleted node was
            delete nodePtr;
            --count;
            return true;
        }
    }
    return false;
}

// Precondition: Int userID
// Searches for a userID in linked list
// Postcondition: None
bool LinkedList::findNode(int user)
{
    ListNode* nodePtr;  // To move through the list
    // Position nodePtr at the head of the list.
    nodePtr = head;
    while(nodePtr)
    {
        // if nodePtr has userID enter if and output the lab the user was found in
        if(nodePtr->lab.getUserID() == user)
        {
            std::cout << "User " << std::setfill(' ') << std::setw(2) << nodePtr->lab.getUserID() << " was found in lab " << nodePtr->lab.getLab()
                      << " and computer " << nodePtr->lab.getCompStation() << " for " << nodePtr->lab.getTime() << " minutes." << std::endl;
            return true;
        }
        // Move to the next node.
        nodePtr = nodePtr->next;
    }
    std::cout << std::endl;
    return false;
}

// Destructor
// Destroys LinkedList
LinkedList::~LinkedList()
{
   ListNode *nodePtr;   // To traverse the list
   ListNode *nextNode;  // To point to the next node

   // Position nodePtr at the head of the list.
   nodePtr = head;

   // While nodePtr is not at the end of the list...
   while (nodePtr != nullptr)
   {
      // Save a pointer to the next node.
      nextNode = nodePtr->next;
      // Delete the current node.
      delete nodePtr;
      // Position nodePtr at the next node.
      nodePtr = nextNode;
   }
   count = 0;
   size = 0;
}

// Precondition: None
// Checks if LinkedList is full
// Postcondition: Bool
bool LinkedList::isFull() const
{
    if(count == size)
    {
        return true;
    }
    return false;
}

// Precondition: short
// Checks if a computer station is occupied
// Postcondition: Bool
bool LinkedList::isOccupied(short compStation) const
{
    // Declares listNode to head to iterate through LinkedList
    ListNode* nodePtr;
    nodePtr = head;
    while(nodePtr != nullptr)
    {
        // if computer station exists return true
        if(nodePtr->lab.getCompStation() == compStation)
        {
           return true;
        }
        nodePtr = nodePtr->next;
    }
    return false;
}

// Precondition: None
// Finds first open computer station
// Postcondition: Short
short LinkedList::findFirstOpen()
{
    // Declares ListNode at head to iterate through list
    ListNode* nodePtr;
    nodePtr = head;
    short freeComputer = 1;
    // checks if head is free
    if(nodePtr == nullptr)
    {
        return freeComputer;
    }
    while(nodePtr != nullptr)
    {
        // if nodePtr computer station does not equal free computer that means the computer station is free
        if(nodePtr->lab.getCompStation() != freeComputer)
        {
            return freeComputer;
        }
    }
    return -1;
}
