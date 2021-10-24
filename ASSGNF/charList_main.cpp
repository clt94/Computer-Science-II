// This program demonstrates simple operations
// on a linked list.
#include <iostream>
#include "charList.cpp"

int main()
{
   // Define a NumberList object.
   CharList list;

   // Append some values to the list.
   list.appendNode('t');
   list.appendNode('s');
   list.appendNode('n');
   list.appendNode('m');
   list.appendNode('j');
   list.appendNode('f');
   list.appendNode('c');
   list.appendNode('a');
   // t s n m j c a
   list.insertNode('y'); // y t s n m j c a
   list.insertNode('0'); // y t s n m j c a 0
   list.insertNode('9'); // y t s n m j c a 9 0
   list.insertNode('o'); // y t s o n m j c a 9 0
   list.insertNode('p'); // y t s p o n m j c a 9 0
   list.insertNode('@'); // y t s p o n m j c a @ 9 0
   list.insertNode('Q'); // y t s p o n m j c a Q @ 9 0
   list.deleteNode('t'); // y s p o n m j c a Q @ 9 0
   list.displayList();
   return 0;
}
