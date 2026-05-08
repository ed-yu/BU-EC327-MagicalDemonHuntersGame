#ifndef BUILDING_H
#define BUILDING_H

#include <iostream>
#include <fstream>
#include "Point2D.h"
#include "Vector2D.h"
#include "GameObject.h"

class Model;

using namespace std;


class Building : public GameObject //base class for all building type objects in the game. It inherits from GameObject and is responsible for tracting the total number of Mages that enter or leave a building.
{
    private:
    unsigned int mage_count = 0;
    public:
    Building(); //default constructor, display code is set to 'B', default build
    Building(char, int, Point2D); //constructor initializes the idnumber, location, and remainder member variables to their default initial values.

    void AddOneMage(); //Increments mage_count by one.
    void RemoveOneMage(); //Decrements mage_count by one.
    void ShowStatus(); //prints "(display_code)(id) located at (location)" Prints "(mage_count) mage(s) is/ar in this building"
    bool ShouldBeVisible(); //returns true as buildings are always visible;
    virtual void save(ofstream& file); //calls the save function for its super class, then writes to the file the member variables declared in this class. If a member variable is a pointer to another GameObject, it writes that objects id number instead. If the pointer is 0, it writes a -1 for the id number (assuming that object id numbers are >=0)
    virtual void restore(ifstream& file, Model& model); //calls the restore function for its superclass, then reads tfrom the file into the member variables declared in this class. If a member variable was originally a pointer to another GameObject, it reads in that object's id number, and gets the pointer to the new object that has that id number from the model. If the id number is -1, then the valuue of 0 is stored in the pointer.
};

#endif