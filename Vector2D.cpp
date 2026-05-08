#include <iostream>
#include <ostream>
#include "Point2D.h"
#include "Vector2D.h"
using namespace std;

Vector2D::Vector2D() //default constructor
    {
        this->x = 0;
        this->y = 0;
    }
Vector2D::Vector2D(double in_x, double in_y) //constructor that takes in x and y input
    {
        this->x = in_x;
        this->y = in_y;
    }

Vector2D operator*(const Vector2D& v1, const double d) //returns Vector2D after vector multiplication
    {
        return Vector2D(v1.x*d, v1.y*d);
    }

Vector2D operator/(const Vector2D& v1, const double d) //returns Vector2D after vector division
    {
        if(d != 0)
        {
            return Vector2D(v1.x/d, v1.y/d);
        }
        else //safeguard
        {
            return Vector2D(v1.x, v1.y);
        }
    }

ostream& operator<<(ostream& output, const Vector2D& v1) //outputs vector in vector format
{
    output << "<" << v1.x << "," << v1.y << ">";
    return output;
}
