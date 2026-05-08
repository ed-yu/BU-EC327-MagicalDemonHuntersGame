#include <iostream>
#include <ostream>
#include <cmath>
#include "Point2D.h"
#include "Vector2D.h"
using namespace std;

Point2D::Point2D() //default constructor
    {
        this->x = 0;
        this->y = 0;
    }
Point2D::Point2D(double in_x, double in_y) //constructor that take in input x and y
    {
        this->x = in_x;
        this->y = in_y;

    }
double GetDistanceBetween(Point2D p1, Point2D p2) //computes the linear distance between two points
    {
        double distance;

        distance = sqrt(((p2.x - p1.x)*(p2.x - p1.x)) + ((p2.y-p1.y)*(p2.y-p1.y)));

        return distance;
    }

ostream& operator<<(ostream& output, const Point2D& p1) //outputs the point in point format
    {
        output << "(" << p1.x << ", " << p1.y << ")";
        return output;
    }

Point2D operator+(const Point2D& p1, const Vector2D& v1) //add operator, adds the point and the vector
{
    return Point2D(p1.x+ v1.x, p1.y+ v1.y);

}
Vector2D operator-(const Point2D& p1, const Point2D& p2) //subtract operator, subtracts the point and the vector
{
    return Vector2D(p1.x-p2.x, p1.y-p2.y);
}
