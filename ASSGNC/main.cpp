/*
COPYRIGHT (C) 2019 Connor Taylor (clt94) All rights reserved
ASSGNC Sophisticated Rectangle
Author: Connor Taylor
        clt94@zips.uakron.edu
Purpose: Making a class rectangle, take points and validate they are a rectangle
         and within bounds. Then compute the length, width, perimeter, area, and
         if it is a square.
*/
// A Sophisticated Rectangle Class
#include <iostream>
#include <stdexcept>

/*
Create a sophisticated Rectangle class. This class stores only the Cartesian coordinates of the four corners of the
rectangle. The constructor calls a set function that accepts four sets of coordinates and verifies that
each of these is in the first quadrant with no single x- or y-coordinate larger than 20.0. The set function
also verifies that the supplied coordinates do, in fact, specify a rectangle.

Provide member functions that calculate the length, width, perimeter and area. The length is the larger of the two
dimensions.

Include a predicate function square that determines whether the rectangle is a square.
*/

// PLACE CLASSES AND METHODS HERE
// Creates class Point. This is the two Cartesian coordinates.
// Initializes points in constructor. Has a two getters.
class Point
{
private:
    float xCoord, yCoord;
public:
    Point() // constructor
    {
        xCoord = 0.0;
        yCoord = 0.0;
    }
    Point(float x, float y) // constructor
    {
        xCoord = x;
        yCoord = y;
    }
    float getX() const // gets x-coordinate
    {
        return xCoord;
    }
    float getY() const // gets y-coordinate
    {
        return yCoord;
    }
};

// Makes a class Rectangle. Child of class Point. Contains side1 and side2.
// Sides initialized in constructor. Has function to arrange points into rectangle and validate.
// Has function to find the length, width, perimeter, area, and determines if it's a square.
class Rectangle : public Point
{
private:
    float side1, side2;
public:
    Rectangle(Point &, Point &, Point &, Point &);
    void setCoord(Point &, Point &, Point &, Point &);
    float length();
    float width();
    void perimeter();
    void area();
    bool square();
};

// Constructor for rectangle. Calls function setCoord.
Rectangle::Rectangle(Point &p1, Point &p2, Point &p3, Point &p4)
{
    setCoord(p1, p2, p3, p4);
}

// Precondition: four Point references
// Validates each point is greater than 0 and less than 20. Arranges points
// to get side1 and side2. Sets sides to 0 if they are not a rectangle.
// Postcondition: None
void Rectangle::setCoord(Point &p1, Point &p2, Point &p3, Point &p4)
{
    // verifies p1
    if(p1.getX() < 0 || p1.getX() > 20 || p1.getY() < 0 || p1.getY() > 20)
    {
        std::cout << "Point out of bounds!" << std::endl;
    }
    // verifies p2
    if(p2.getX() < 0 || p2.getX() > 20 || p2.getY() < 0 || p2.getY() > 20)
    {
        std::cout << "Point out of bounds!" << std::endl;
    }
    // verifies p3
    if(p3.getX() < 0 || p3.getX() > 20 || p3.getY() < 0 || p3.getY() > 20)
    {
        std::cout << "Point out of bounds!" << std::endl;
    }
    // verifies p4
    if(p4.getX() < 0 || p4.getX() > 20 || p4.getY() < 0 || p4.getY() > 20)
    {
        std::cout << "Point out of bounds!" << std::endl;
    }
    // sets side1 and side2 in proper order of points
    if(p1.getX() < p2.getX() && p1.getY() < p4.getY() && p1.getX() == p4.getX() && p1.getY() == p2.getY())
    {
        side1 = p2.getX() - p1.getX();
        side2 = p4.getY() - p1.getY();
    }
    // sets side1 and side2 if the points are in the reverse order
    else if(p4.getX() < p3.getX() && p4.getY() < p1.getY() && p4.getX() == p1.getX() && p4.getY() == p3.getY())
    {
        side1 = p3.getX() - p4.getX();
        side2 = p1.getY() - p4.getY();
    }
    // sets side1 and side2 to 0 if the coordinates do not make a rectangle
    else
    {
        std::cout << "Coordinates do not make a rectangle!" << std::endl;
        side1 = 0.0;
        side2 = 0.0;
    }
}

// Precondition: None
// Determines which side is smaller and returns the larger one as the length.
// Postcondition: float
float Rectangle::length()
{
    if(side1 < side2)
    {
        return side2;
    }
    else
    {
        return side1;
    }
}

// Precondition: None
// Gets the width by returning the smaller side.
// Postcondition: float
float Rectangle::width()
{
    if(side1 < side2)
    {
        return side1;
    }
    else
    {
        return side2;
    }
}

// Precondition: None
// Outputs the perimeter.
// Postcondition: None
void Rectangle::perimeter()
{
    std::cout << "\nperimeter: " << side1 * 2 + side2 * 2;
}

// Precondition: None
// Outputs the area.
// Postcondition: None
void Rectangle::area()
{
    std::cout << "\narea: " << side1 * side2;
}

// Precondition: None
// Determines if the rectangle is a square also.
// Postcondition: bool
bool Rectangle::square()
{
    if(side1 == side2)
    {
        return true;
    }
    return false;
}

int main() {
   Point w{1.0, 1.0};
   Point x{5.0, 1.0};
   Point y{5.0, 3.0};
   Point z{1.0, 3.0};
   Point j{0.0, 0.0};
   Point k{1.0, 0.0};
   Point m{1.0, 1.0};
   Point n{0.0, 1.0};

   Rectangle r1{z, y, x, w};
   std::cout << "Rectangle 1:\n";
   std::cout << "length = " << r1.length();
   std::cout << "\nwidth = " << r1.width();
   r1.perimeter();
   r1.area();
   std::cout << "\nThe rectangle "
      << (r1.square() ? "is" : "is not")
      << " a square.\n";

   Rectangle r2{j, k, m, n};
   std::cout << "\nRectangle 2:\n";
   std::cout << "length = " << r2.length();
   std::cout << "\nwidth = " << r2.width();
   r2.perimeter();
   r2.area();
   std::cout << "\nThe rectangle "
      << (r2.square() ? "is" : "is not")
      << " a square.\n";
}
