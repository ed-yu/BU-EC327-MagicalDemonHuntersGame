#ifndef VIEW_H
#define VIEW_H

#include <iostream>
#include "GameObject.h"
#include "Mage.h"

const int view_maxsize = 20; // the maximum size of the grid array

class View
{
    private:
    int size; //the current size of the grid to be displayed; not all of the grid array will be displayed in this project.
    double scale; //the distance represented by each cell of the grid
    Point2D origin; //the coordinates of the lower left-hand corner of the grid
    char grid[view_maxsize][view_maxsize][2]; //an array to hold the characters that make up the display grid.
    bool GetSubscripts(int &out_x, int &out_y, Point2D location); //calculates the column and row subscripts

    public:
    View(); //default constructor, sets size to 11, scale to 2, origin default to (0,0). No constructor output message is needed.
    void Clear(); //sets all the cells of the grid to the background pattern shown in the sample output.
    void Plot(GameObject *ptr); //Plots the pointed-to object in the proper cell of the grid.
    void Draw();

    



};
#endif