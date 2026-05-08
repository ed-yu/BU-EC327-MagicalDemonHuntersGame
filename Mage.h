#ifndef MAGE_H
#define MAGE_H

#include <iostream>
#include <fstream>

#include "GameObject.h"
#include "Point2D.h"
#include "Vector2D.h"

using namespace std;

class Model;
class ManaSpire;
class DemonHideout;
class RoamingDemon;
class AncientDemon;

enum MageStates{
    STOPPED = 0,
    MOVING = 1,
    KNOCKED_OUT = 2,
    AT_SPIRE = 3,
    IN_HIDEOUT = 4,
    MOVING_TO_SPIRE = 5,
    MOVING_TO_HIDEOUT = 6,
    BATTLING_IN_HIDEOUT = 7,
    RECOVERING_MANA = 8
};

class Mage : public GameObject
{
    friend class AncientDemon;
    protected:
    bool UpdateLocation(); //updates the object's location while it is moving. prints "(display_code)(id): I'm there!" if Mage has arrived at its destination. Prints "(display_code)(id): step..." otherwise.
    void SetupDestination(Point2D dest); //sets up the object to start moving to dest.
    
    private:
    double speed; //speed this object travels, expressed aas distance per update time unit.
    bool is_at_spire; //set to true of the Mage is in a ManaSpire. Initial value should be false.
    bool is_in_hideout; //set to true if this Mage is in a DemonHideout. Initial value should be false.
    unsigned int mana; //amoung of mana a Mage has. Initial value should be 20.
    unsigned int experience; //the amount of experience points this Mage has. Intiial value should be 0.
    double gold_pieces; //the total amount of gold pieces this Mage holds. Initial value should be 0.
    unsigned int battles_to_buy; //stores the number of battles to buy when in a DemonHideout. Initial value should be 0.
    unsigned int crystals_to_buy; //stores the number of crystals to buy when in a ManaSpire, initial value should be 0.
    string name; //the name of this mage.
    ManaSpire* current_spire; //a pointer to the current ManaSpire. Initial value should be 0 (NULL).
    DemonHideout* current_hideout; //a pointer to the current DemonHideout. Initial value should be 0 (NULL).
    Point2D destination; //this object's current destination coordinates in the real plane. Point2D's default constructor will initialize this to (0.0, 0.0).
    Vector2D delta; //Contains the x and y amounts that the object will move on each time unit.
    bool isFollowed; //bool, if followed by roamingdemon
    bool isCursed; //bool, if followed by ancientdemon
    RoamingDemon* currentFollower; //current roamingdemon following mage
    AncientDemon* currentAncientCurse; //current ancientdemon following mage
    void AncientRelief(bool); //if Mage defeats AncientDemon, add mana.

    public:
    Mage(); //default constructor
    Mage(char); //takes in_code, sets speeed to 5 and outputs "Mage constructed" set state:STOPPED, display_code:in_code.
    Mage(string, int, char, unsigned int, Point2D); //inits the speed to in_speed and sets the name to in_name.
    virtual ~Mage(); // destructor
    void StartMoving(Point2D); //tells Mage to start moving, calls setup_destination(), sets state:MOVING.
    void StartMovingToHideout(DemonHideout*);//tells Mage to start moving to a DemonHideout. Calls SetupDestination(). state:MOVING_TO_HIDEOUT
    void StartMovingToSpire(ManaSpire*); //tells Mage to start moving to a ManaSpire. calls:SetupDestination(), state:MOVING_TO_SPIRE
    void StartBattling(unsigned int); //tells Mage to start battling (num_battles) in a DemonHideout. state:BATTLING_IN_HIDEOUT
    void StartRecoveringMana(unsigned int); //Mage to start recovering at a ManaSpire. state:RECOVERING_MANA
    void Stop(); //end process for Mage, state:STOPPED.
    bool IsKnockedOut(); //returns true if mana is 0.
    bool ShouldBeVisible(); //returns true if mage is not knocked out.
    void ShowStatus(); //prints name_status, calls GameObject::ShowStatus(). Print state specific status information.
    bool Update(); //Mage object behavior
    string GetName(); //returns the Name string of the Mage.
    bool IsBeingFollowed(); //returns true if is being followed by a RoamingDemon
    bool IsCursed(); //returns true if it is being followed by an AncientDemon
    void setFreeCase(double); //takes in a number
    void SetFollowed(bool, RoamingDemon*); //called in RoamingDemon class, if is following, then sets to true and passes RoamingDemon ptr.
    void setBleedCase(double); //takes in number 
    void SetCurse(bool, AncientDemon*); //called in AncientDemon class, if it is following, sets to true and passes AncientDemon ptr.
    virtual void save(ofstream& file); //calls the save function for its super class, then writes to the file the member variables declared in this class. If a member variable is a pointer to another GameObject, it writes that objects id number instead. If the pointer is 0, it writes a -1 for the id number (assuming that object id numbers are >=0)
    virtual void restore(ifstream& file, Model& model); //calls the restore function for its superclass, then reads tfrom the file into the member variables declared in this class. If a member variable was originally a pointer to another GameObject, it reads in that object's id number, and gets the pointer to the new object that has that id number from the model. If the id number is -1, then the valuue of 0 is stored in the pointer.
};

double GetRandomAmountOfGP(); //returns a random number between 0.0 and 2.0 inclusive.

#endif