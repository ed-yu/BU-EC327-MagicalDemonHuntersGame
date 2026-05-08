#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <iostream>
#include <ostream>
using namespace std;

class Vector2D //contains the two double values, is used to represent a vector in the real plane (set of x and y displacements). The overloaded operators allow one to do simple linear-algebra operations to compute where an object's new location should be as it move around. All data memebers and functions for this class is public.
{
    public:
    double x; //The x value of the point
    double y; //The y value of the point
    Vector2D(); //default constructor
    Vector2D(double, double); //constructor that takes in x and y input

};

Vector2D operator*(const Vector2D&, const double); //returns Vector2D after vector multiplication
Vector2D operator/(const Vector2D& v1, const double d); //returns Vector2D after vector division
ostream& operator<<(ostream& output, const Vector2D& v1); //outputs vector in vector format

#endif