/*
   COPYRIGHT (C) 2019 Connor Taylor (clt94) All rights reserved.
   CSII ASSGNF
   Author.  Connor Taylor
            clt94@zips.uakron.edu
   Version. 1.01 11.01.2019

*/
#include <iostream>
// Implementation file for the NumberList class

// Your coding required here
// Defines class CharList
class CharList
{
private:
    // Defines private struct ListNode that holds the values of each node
    struct ListNode
    {
        char value;
        ListNode *next;
    };
    ListNode *head;
public:
    // default constructor for CharList
    CharList()
    {   head = nullptr; }
    // prototypes for each function
    void displayList() const;
    void appendNode(char);
    void insertNode(char);
    void deleteNode(char);
    ~CharList();
};

//**************************************************
// displayList shows the value                     *
// stored in each node of the linked list          *
// pointed to by head.                             *
// pre: an empty parameter list                    *
// post: standard output of the linked list        *
//**************************************************

// I inlined this function because it was throwing the error of multiple class definition
// and this is the solution I found
inline void CharList::displayList() const
{
   ListNode *nodePtr;  // To move through the list

   // Position nodePtr at the head of the list.
   nodePtr = head;
   short count = 0;

   // While nodePtr points to a node, traverse
   // the list.
   while (nodePtr)
   {
      // Display the value in this node.
      std::cout << "[" << nodePtr->value << "] -> ";
      ++count;
      // Move to the next node.
      nodePtr = nodePtr->next;
      if (count % 10 == 0) {
        std::cout << std::endl;
        count = 0;
      }
   }
   std::cout << std::endl;
}

// More of your coding required here
// appendNode is a void function that is passed a character
// and adds the character to the end of ListNode
inline void CharList::appendNode(char character)
{
    // defines pointer to a newNode that will hold the new character
    ListNode* newNode = new ListNode;
    newNode->value = character;
    newNode->next = nullptr;
    // defines pointer to go through the list of nodes
    ListNode* nodePtr;

    // if head is empty then assign newNode to head
    if(!head)
    {
        head = newNode;
    }
    else
    {
        // assigns value to go through list at the start
        nodePtr = head;
        while(nodePtr->next) // if the next node exists enter the loop
        {
            nodePtr = nodePtr->next; // sets nodePtr to next to go through list
        }
        // sets nodePtr next to new node so the value of the newNode is at the end of the list
        nodePtr->next = newNode;
    }
}

// void function insertNode takes a char and inserts it after the first node with a value than itself
inline void CharList::insertNode(char character)
{
    // initializes a newNode to hold the character
    ListNode* newNode = new ListNode;
    newNode->value = character;
    // initializes a nodePtr to travel through the list
    ListNode* nodePtr;
    // initializes a node that will be the value previous to the head of the list
    ListNode* previousNode = nullptr;

    // if the list is empty then the node will be put it at the start
    if(!head)
    {
        head = newNode;
        newNode->next = nullptr;
    }
    else
    {
        // sets nodePtr to head so it can begin at the start of the list
        nodePtr = head;
        // loop while nodePtr has a value and if that value of nodePtr is higher than the character to insert, if not continue through the list
        while(nodePtr != nullptr && nodePtr->value > character)
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
    }
}

// void function deleteNode with a char than finds the first value in the list and then deletes it
inline void CharList::deleteNode(char character)
{
    // creates pointers to traverse the list
    ListNode* nodePtr;
    ListNode* previousNode;

    // exits function if list is empty
    if(!head)
    {
        return;
    }
    // if the head of the list is the character then delete head and set it to the next pointer in the list
    if(head->value == character)
    {
        nodePtr = head->next;
        delete head;
        head = nodePtr;
    }
    else
    {
        // sets nodePtr to head to traverse the list
        nodePtr = head;
        // while there is a value in the list and no value is equal to the character traverse the list
        while(nodePtr != nullptr && nodePtr->value != character)
        {
            previousNode = nodePtr;
            nodePtr = nodePtr->next;
        }
        // if the nodePtr does exist delete it
        if(nodePtr)
        {
            previousNode->next = nodePtr->next; // adjusts previous node to be after where the deleted node was
            delete nodePtr;
        }
    }
}

//**************************************************
// Destructor                                      *
// This function deletes every node in the list.   *
// pre: n/a                                        *
// post: destroyed object                          *
//**************************************************

inline CharList::~CharList()
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
}
