#ifndef MANASPIRE_H
#define MANASPIRE_H

#include <iostream>
#include <fstream>
#include "Building.h"

using namespace std;

class GameObject;
class Point2D;
class Model;

enum ManaSpireStates {
    CRYSTALS_AVAILABLE = 0,
    NO_CRYSTALS_AVAILABLE = 1
};

class ManaSpire : public Building //contains a location and a set amount of magic crystals. Contains a display_code letter and an id number that are used to help identify the object in the output. ManaSpire inherits from Building.
{
    private:
    unsigned int crystal_capacity; //maximum number of crystals this ManaSpire can hold.
    unsigned int num_crystals_remaining; //the amount of crystals currently in this ManaSpire, initial value is set to crystal_capacity.
    double cost_per_crystal; //the per crystal cost in the ManaSpire.

    public:
    ManaSpire(); //default constructor
    ManaSpire(int, double, unsigned int, Point2D); //parameter constructor.
    ~ManaSpire(); //destructor
    bool HasCrystals(); //returns true if this ManaSpire contains at least one crystal, returns false otherwise.
   
    unsigned int GetNumCrystalsRemaining(); //returns the number of crystals remaining in this ManaSpire.
    bool CanAffordCrystal(unsigned int, double); //Returns true if this Mage can afford to purchase crystal with the given budget.
    double GetCrystalCost(unsigned int); //returns the cost (in gold pieces) for the specified number of crystals.
    unsigned int DistributeCrystals(unsigned int); //If the amount num_crystals_remaining in the ManaSpire is greater than or equal to crystals_needed, it subtract crystals_needed from ManaSpire amount and returns crystal_needed. If the amount of crystals in the ManaSpire is less, it returns the ManaSpire current amount, and the ManaSpire crystal amount is set to 0.
    bool Update();
    void ShowStatus();
    virtual void save(ofstream& file); //calls the save function for its super class, then writes to the file the member variables declared in this class. If a member variable is a pointer to another GameObject, it writes that objects id number instead. If the pointer is 0, it writes a -1 for the id number (assuming that object id numbers are >=0)
    virtual void restore(ifstream& file, Model& model); //calls the restore function for its superclass, then reads tfrom the file into the member variables declared in this class. If a member variable was originally a pointer to another GameObject, it reads in that object's id number, and gets the pointer to the new object that has that id number from the model. If the id number is -1, then the valuue of 0 is stored in the pointer.
};
#endif