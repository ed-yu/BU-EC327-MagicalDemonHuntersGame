#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Point2D.h"
#include <fstream>


using namespace std;

class Model;

class GameObject //base class for all the objects in the game. It is reponsible for the member variables and functions that they all have in common.
{
    protected:
    Point2D location; //loation of the object
    int id_num; //object's ID
    char display_code;//How the object is presented in the View
    char state; //State of the object; more information provided in each derived class

    public:
    GameObject(char);
    GameObject(Point2D in_loc, int in_id, char in_code);
    virtual ~GameObject(); //destructor
    Point2D GetLocation(); //returns the location for this object
    int GetId(); //returns the id for this object
    char GetState(); //returns the state for this object
    virtual void ShowStatus(); //Outputs the information contained in class "(display_code)(id_num) at (location)"
    virtual bool Update() = 0;
    virtual bool ShouldBeVisible() = 0;
    void DrawSelf(char *ptr);
    virtual void save(ofstream& file); //calls the save function for its super class, then writes to the file the member variables declared in this class. If a member variable is a pointer to another GameObject, it writes that objects id number instead. If the pointer is 0, it writes a -1 for the id number (assuming that object id numbers are >=0)
    virtual void restore(ifstream& file, Model& model); //calls the restore function for its superclass, then reads tfrom the file into the member variables declared in this class. If a member variable was originally a pointer to another GameObject, it reads in that object's id number, and gets the pointer to the new object that has that id number from the model. If the id number is -1, then the valuue of 0 is stored in the pointer.
    char GetDisplayCode(); //gets display code
};
#endif