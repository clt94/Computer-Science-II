// Connor Taylor
// Assignment G: myStack
// This program demonstrates the myStack class.
#include <iostream>

// Declares class myStack that is templated
// Used to store values on the stack and traverse through the stack
template <typename T>
class myStack
{
private:
    T* stackArray; // declares a pointer that will serve as an array of values held on the stack
    int stackSize; // tracks the size of the stack
    int top; // stores the index of the top value of the array
public:
    myStack(int); // constructor
    ~myStack(); // destructor
    bool push(T); // puahes value onto stack
    bool pop(T&); // pop value from stack and store it
    bool isFull() const; // checks if stack is full
    bool isEmpty() const; // checks if stack is empty
    void mult(); // multiplies the last two values of the stack
    void div(); // divides the last two values of the stack
    void add(); // adds the last two values of the stack
    void sub(); // subtracts the last two values of the stack
    void addAll(); // adds all the values on the stack
    void multAll(); // multiplies all the values on the stack
};

// Precondition: int size
// initializes an array of the size passed
// Postcondition: none
template <typename T>
myStack<T>::myStack(int size)
{
    stackArray = new T[size]; // initializes array that holds the values of the stack with the size passed
    stackSize = size; // sets stackSize to size
    top = -1; // sets top to -1, as there are no values in stackArray yet
}

// Precondition: None
// Deletes stack
// Postcondition: None
template <typename T>
myStack<T>::~myStack()
{
    delete[] stackArray; // deletes stackArray
}

// Precondition: Templated type T named value
// Pushes a value onto the stack
// Postcondition: Returns true if the value is pushed onto the stack, false otherwise
template <typename T>
bool myStack<T>::push(T value)
{
    if(isFull()) // if the stack is full, do not push and return false
    {
        return false;
    }
    else // if stack is not full, push value to the stack and return true
    {
        ++top; // increments top by 1 to go to next value in stackArray
        stackArray[top] = value; // sets the stackArray at index of top to value
        return true;
    }
}

// Precondition: Templated type T by reference named value
// Copies value from top of stack to value and then removes the value from the top of the stack
// Postcondition: Returns true if value is popped, false otherwise
template <typename T>
bool myStack<T>::pop(T& value)
{
    if(isEmpty()) // if the array is empty, do not pop any values and return false
    {
        return false;
    }
    else // if the array is not empty, pops the value
    {
        value = stackArray[top]; // sets value to the data in the top of stackArray
        --top; // decrements top by one since the data in stackArray is gone
        return true;
    }
}

// Precondition: None
// Checks if stack is full
// Postcondition: Returns true if the stack is full, false otherwise
template <typename T>
bool myStack<T>::isFull() const
{
    if(top == stackSize - 1) // if the stackSize - 1 is equal to top then the array is full and returns true
    {
        return true;
    }
    else // otherwise return false
    {
        return false;
    }
}

// Precondition: None
// Checks if the stack is empty
// Postcondition: Returns true if the stack is empty, false otherwise
template <typename T>
bool myStack<T>::isEmpty() const
{
    if(top == -1) // if top is -1 the stack is empty and returns true
    {
        return true;
    }
    else // returns false otherwise
    {
        return false;
    }
}

// Precondition: None
// Pops top two values off the stack, multiplies them and pushes the product to the stack
// Postcondition: None
template <typename T>
void myStack<T>::mult()
{
    // pops value off the stack and stores it in value1
    T value1;
    pop(value1);
    // pops value off the stack and stores it in value2
    T value2;
    pop(value2);
    // multiplies value1 and value2 and pushes it to the stack
    push(value1 * value2);
}

// Precondition: None
// Pops top two values off the stack, divides them and pushes the quotient to the stack
// Postcondition: None
template <typename T>
void myStack<T>::div()
{
    // pops value off the stack and stores it in value1
    T value1;
    pop(value1);
    // pops value off the stack and stores it in value2
    T value2;
    pop(value2);
    // divides value1 and value2 and pushes it to the stack
    push(value1 / value2);
}

// Precondition: None
// Pops top two values off the stack, adds them and pushes the sum to the stack
// Postcondition: None
template <typename T>
void myStack<T>::add()
{
    // pops value off the stack and stores it in value1
    T value1;
    pop(value1);
    // pops value off the stack and stores it in value2
    T value2;
    pop(value2);
    // adds value1 and value2 and pushes it to the stack
    push(value1 + value2);
}

// Precondition: None
// Pops top two values off the stack, subtracts them and pushes the product to the stack
// Postcondition: None
template <typename T>
void myStack<T>::sub()
{
    // pops value off the stack and stores it in value1
    T value1;
    pop(value1);
    // pops value off the stack and stores it in value2
    T value2;
    pop(value2);
    // subtracts value1 and value2 and pushes it to the stack
    push(value1 - value2);
}

// Precondition: None
// Pops all the values off of the stack and totals them, and then pushes this value onto the stack
// Postcondition: None
template <typename T>
void myStack<T>::addAll()
{
    T value;
    T sum = 0;
    while(pop(value)) // while the stack can be popped, store the top of the stack in value
    {
        sum += value; // adds each value from the stack
    }
    push(sum); // pushed sum to the stack
}

// Precondition: None
// Pops all the values off of the stack, multiplies them all and pushes the product to the stack
// Postcondition: None
template <typename T>
void myStack<T>::multAll()
{
    T value;
    T product = 1;
    while(pop(value)) // while the stack can popped, store the top value of the stack in value
    {
        product *= value; // multiplies each value from the stack
    }
    push(product); // pushes product to the stack
}

int main()
{
  int catchVar;  // To hold values popped off the stack

  // Create a intstack object.
  myStack<int> intStack(5);
  std::cout << "Starting the demonstration of the greatest stack of all time"
            << std::endl << std::endl;

  // Push 3 and 6 onto the stack.
  std::cout << "Pushing 3\n";
  intStack.push(3);
  std::cout << "Pushing 6\n";
  intStack.push(6);

  // Add the two values.
  intStack.add();

  // Pop the sum off the intStack and display it.
  std::cout << "The sum is ";
  intStack.pop(catchVar);
  std::cout << catchVar << std::endl << std::endl;

  // Push 7 and 10 onto the intStack
  std::cout << "Pushing 7\n";
  intStack.push(7);
  std::cout << "Pushing 10\n";
  intStack.push(10);

  // Subtract
  intStack.sub();

  // Pop the difference off the intStack and display it.
  std::cout << "The difference is ";
  intStack.pop(catchVar);
  std::cout << catchVar << std::endl << std::endl;

  // Push 7 and 10 onto the intStack
  std::cout << "Pushing 7\n";
  intStack.push(7);
  std::cout << "Pushing 10\n";
  intStack.push(10);

  // multiply
  intStack.mult();

  // Pop the difference off the intStack and display it.
  std::cout << "The product is ";
  intStack.pop(catchVar);
  std::cout << catchVar << std::endl << std::endl;

  // Push 7 and 10 onto the intStack
  std::cout << "Pushing 7\n";
  intStack.push(7);
  std::cout << "Pushing 10\n";
  intStack.push(10);

  // divide
  intStack.div();

  // Pop the difference off the intStack and display it.
  std::cout << "The quotient is ";
  intStack.pop(catchVar);
  std::cout << catchVar << std::endl << std::endl;

  //***********************************
  // create a double version of myStack
  //***********************************
  myStack<double> doubleStack(5); // size 5
  double doubleValue = 87.1;
  std::cout << "Pushing elements onto doubleStack\n" << std::endl << std::endl;

  // push 5 doubles onto doubleStack

  while (doubleStack.push(doubleValue))
  {
    std::cout << doubleValue << ' ';
    doubleValue += 6.1;
  } // end while

  std::cout << "\nStack is full. Cannot push " << doubleValue
       << "\n\nPopping elements from doubleStack\n" << std::endl << std::endl;

  // pop elements from doubleStack
  while (doubleStack.pop(doubleValue))
  {
    std::cout << doubleValue << ' ';
  }
  std::cout << "\nStack is empty. Cannot pop\n" << std::endl << std::endl;

  //***********************************
  // create a float version of myStack
  //***********************************
  myStack<float> floatStack(5); // size 5
  float floatValue = 87.1;
  std::cout << "Pushing elements onto floatStack\n" << std::endl << std::endl;

  // push 5 floats onto floatStack
  while (floatStack.push(floatValue))
  {
    std::cout << floatValue << ' ';
    floatValue += 6.1;
  } // end while

  floatStack.addAll();

  // Pop the sum off the floatStack and display it.
  std::cout << "The sum of all is ";
  floatStack.pop(floatValue);
  std::cout << floatValue << std::endl << std::endl;

  floatValue = 87.1;
  // push 5 floats onto floatStack
  while (floatStack.push(floatValue))
  {
    std::cout << floatValue << ' ';
    floatValue += 6.1;
  } // end while

  floatStack.multAll();

  // Pop the sum off the floatStack and display it.
  std::cout << "The product of all is ";
  floatStack.pop(floatValue);
  std::cout << floatValue << std::endl << std::endl;
  std::cout << "Ending the demonstration of the greatest stack of all time"
            << std::endl << std::endl;
  return 0;
}
