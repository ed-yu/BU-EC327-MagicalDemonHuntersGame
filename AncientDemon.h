#ifndef ANCIENTDEMON_H
#define ANCIENTDEMON_H

#include "GameObject.h"
#include "Mage.h"
#include <fstream>

using namespace std;

class Model;

enum AncientDemonStates{
    AD_IN_ENVIORMENT = 12,
    AD_IN_HUNT = 13,
    AD_DEAD = 14
};

class AncientDemon : public GameObject
{
protected:
double attack; //init val 10
double health; //init val 4
double freeIntensity; //init val 0
bool drained; //one time drain for reward
bool variant; //init val false, extra cred opt: could actually make a derived class of RoamingDemon
bool in_combat; //retyrbs true if the RoamingDemon is attackin a Mage, default is false
string name; //name
Mage* current_mage; //holds the current Mage it is following

public:

AncientDemon(string name, double attack, double health, bool variant, int id, Point2D in_loc);
void follow(Mage* m); //follows Mage m, both change the Roaming Demon's current_mage value and update the mage's information as needed as well.

bool get_variant(); //returns variant
double get_attack();
double get_health(); //return health
bool get_in_combat(); // returns is_in_combat
bool Update(); //updates state > IN_ENVIORMENT: default state when we create a Roaming Demon and it returns false. State > DEAD: When the Roaming Demon's health is 0 or below. State > IN_HUNTL when the Roaming Demon is following a mage
void ShowStatus(); //outputs status
bool IsAlive(); //check the health of the ROaming Demon and return True if it is alive.
bool ShouldBeVisible();
void setFreeIntensity(double); //Mage can use mana to combat the RoamingDemon.
double getFreeIntensity(); //affects RoamingDemon.
virtual void save(ofstream& file); //calls the save function for its super class, then writes to the file the member variables declared in this class. If a member variable is a pointer to another GameObject, it writes that objects id number instead. If the pointer is 0, it writes a -1 for the id number (assuming that object id numbers are >=0)
virtual void restore(ifstream& file, Model& model); //calls the restore function for its superclass, then reads tfrom the file into the member variables declared in this class. If a member variable was originally a pointer to another GameObject, it reads in that object's id number, and gets the pointer to the new object that has that id number from the model. If the id number is -1, then the valuue of 0 is stored in the pointer.

};


#endif