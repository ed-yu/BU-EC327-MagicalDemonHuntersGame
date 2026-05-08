#ifndef POINT2D_H
#define POINT2D_H
#include <ostream>

using namespace std;

class Vector2D;

class Point2D //contains two double values, which will be used to represent a set of (x, y) Cartesian coordinates. THis class and Vector 2D will be used to simplify keeping track of the coordinates of each object in the game, and updating their locations as they move. All data members and functions for this class is public.
{
    public:
    double x; //The x value of the point
    double y; //The y value of the point
    Point2D(); //default constructor
    Point2D(double, double); //constructor that take in input x and y

};
double GetDistanceBetween(Point2D, Point2D); //computes the linear distance between two points

ostream& operator<<(ostream& output, const Point2D& obj); //outputs the point in point format
Point2D operator+(const Point2D& p1, const Vector2D& v1); //add operator, adds the point and the vector
Vector2D operator-(const Point2D& p1, const Point2D& p2); //subtract operator, subtracts the point and the vector

#endif