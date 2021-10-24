#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED
#include "Labs.h"

class LinkedList
{
private:
    // Defines private struct ListNode that holds the values of each node
    struct ListNode
    {
        Labs lab;
        ListNode *next;
    };
    ListNode *head = nullptr;
    short count;
    short size;
public:
    // default constructor for CharList
    LinkedList();
    // constructor for declaring size
    LinkedList(short);
    // Precondition: short
    // Postcondition: none
    void displayLab(short) const;
    // Precondition: Labs by reference
    // Postcondition: none
    void appendNode(Labs&);
    // Precondition: Labs by reference
    // Postcondition: none
    void insertNode(Labs&);
    // Precondition: short, Labs by reference
    // Postcondition: bool
    bool deleteNode(short, Labs&);
    // Precondition: int
    // Postcondition: bool
    bool findNode(int);
    // Precondition: none
    // Postcondition: bool
    bool isFull() const;
    // Precondition: short, short
    // Postcondition: bool
    bool isOccupied(short) const;
    // Precondition: none
    // Postcondition: short
    short findFirstOpen();
    // destructor
    ~LinkedList();
};

#endif // LINKEDLIST_H_INCLUDED
