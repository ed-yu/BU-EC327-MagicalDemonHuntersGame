#ifndef DEMONHIDEOUT_H
#define DEMONHIDEOUT_H
#include <iostream>
#include <fstream>
#include "Building.h"

using namespace std;

class GameObject;
class Point2D;
class Model;

enum DemonHideoutStates{
    NOT_DEFEATED = 0,
    DEFEATED = 1
};

class DemonHideout : public Building //object that has a location and an amount of battles. Contains a display_code letter and id number that are used to help identify the object in the output.
{
    private:
    unsigned int num_battle_remaining; //amount of battles remaining in the DemonHideout
    unsigned int max_number_of_battles; //Number of battles for this DemonHideout
    unsigned int mana_cost_per_battle; //Mana lost for a single hideout battle (depletes your mana when you battle)
    double gold_cost_per_battle; //Entry cost (in gold) for a single battle
    unsigned int experience_per_battle; //Amount of experience gained from each class.

    public:
    DemonHideout(); //default constructor
    DemonHideout(unsigned int, unsigned int, double, unsigned int, int, Point2D); //parameter constructor.
    ~DemonHideout(); //destructor

    double GetGoldCost(unsigned int); //returns the cost of battling battle_qty times (in gold).
    unsigned int GetManaCost(unsigned int); //returns the amount of mana points required for battle_qty battles.
    unsigned int GetNumBattlesRemaining(); //returns the number of battles reamining in this DemonHideout.
    bool IsAbleToBattle(unsigned int, double, unsigned int); //returns true if a Mage in DemonHideout with a given budget and mana can requrest to take battle_qty battle, returns false otherwise.
    unsigned int DemonBattle(unsigned int); //subtracts battles from num_battles_reamining if this DemonHideout has enough units. If the amount of battes requested is greater than the amount available at this DemonHideout, then num_battles_remaining will be used instead of battle_units when calculating experience gain. Returns the amount of experience gained by winning the battles. Experience points can be calculated using (number of bottles)*experience_per_battle.
    unsigned int GetExperiencePerBattle(); //Returns the experience gained from each battle.
    bool Update(); //if the DemonHideout has zero battles remaining, set the state to DEFEATED and display_code to 'd'. Then print the message "(display_code)(id) has been beaten". Returns false if battles still remain within the DemonHideout. This function shouldn't keep returning true if the DemonHideout is passed. It should return true ONLY at the time when the Demon Hideout is defeated, return false for later "Update()" function calls.
    bool passed(); //returns true if battles remaining is 0.
    void ShowStatus(); //prints out the status of the object by calling GameObject's show status and the values of its member variables.
    virtual void save(ofstream& file); //calls the save function for its super class, then writes to the file the member variables declared in this class. If a member variable is a pointer to another GameObject, it writes that objects id number instead. If the pointer is 0, it writes a -1 for the id number (assuming that object id numbers are >=0)
    virtual void restore(ifstream& file, Model& model); //calls the restore function for its superclass, then reads tfrom the file into the member variables declared in this class. If a member variable was originally a pointer to another GameObject, it reads in that object's id number, and gets the pointer to the new object that has that id number from the model. If the id number is -1, then the valuue of 0 is stored in the pointer.
};

#endif