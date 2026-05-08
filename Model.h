#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <list>
#include <fstream>
#include "GameObject.h"
#include "View.h"
#include "Mage.h"
#include "RoamingDemon.h"
#include "ManaSpire.h"
#include "DemonHideout.h"
#include "AncientDemon.h"

class Point2D;

class Model
{
    private:
    int time; //the simulation time
    //GameObject *object_ptrs[10]; //object ptr array
    list<GameObject*> object_ptrs;
    list<GameObject*> active_ptrs;
    //int num_objects; //number of object
    //Mage *mage_ptrs[10]; //mage ptr array
    list<Mage*> mage_ptrs;
   //int num_mages; //number of mages
    //ManaSpire *spire_ptrs[10]; //spire ptr array
    list<ManaSpire*> spire_ptrs;
    //int num_spires; //number of spires
    //DemonHideout *hideout_ptrs[10]; //hideout ptr array
    list<DemonHideout*> hideout_ptrs;
    //int num_hideouts; //number of hideouts
    //RoamingDemon *roamingdemon_ptrs[10]; //roamingdemon array
    list<RoamingDemon*> roamingdemon_ptrs;
    //int num_roamingdemons;
    list<AncientDemon*> ancientdemon_ptrs;

    public:
    Model(); //default constructor
    ~Model(); //destructor deletes each object, and outputs a message: "Model destructed"
    
    Mage* GetMagePtr(int id); //gets mageptr with id
    ManaSpire* GetManaSpirePtr(int id); //gets spire ptr with id
    DemonHideout* GetDemonHideoutPtr(int id); //gets demon hideout ptr with id
    RoamingDemon* GetRoamingDemonPtr(int id);
    AncientDemon* GetAncientDemonPtr(int id);
    bool Update(); //update function
    void Display(View& view); //display function, game grid
    void ShowStatus(); //virtual function that shows status of the game
    void NewCommand(char type, int id, double x, double y); //creates new objects during program execution
    void save(ofstream& file);
    void restore(ifstream& file);
};



#endif