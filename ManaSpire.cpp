#include <iostream>
#include "ManaSpire.h"
#include "Building.h"
#include "GameObject.h"
#include "Point2D.h"
#include "Model.h"

using namespace std;

ManaSpire::ManaSpire() : Building() //default constructor
    {
        
        this->crystal_capacity = 100;
        this->num_crystals_remaining = this->crystal_capacity;
        this->cost_per_crystal = 5;
        this->display_code = 'S';
        this->state = CRYSTALS_AVAILABLE;

        cout << "ManaSpire default constructed" << endl;

    }
ManaSpire::ManaSpire(int in_id, double crystal_const, unsigned int crystal_cap, Point2D in_loc) : Building('S', in_id, in_loc)
    {
        this->cost_per_crystal = crystal_const;
        this->crystal_capacity = crystal_cap;
        this->num_crystals_remaining = crystal_cap;

        cout << "ManaSpire constructed" << endl;

        this->state = CRYSTALS_AVAILABLE;

    }
ManaSpire::~ManaSpire()
    {
        cout << "ManaSpire destructed." << endl;
    }
bool ManaSpire::HasCrystals() //returns true if this ManaSpire contains at least one crystal, returns false otherwise.
    {
        if(num_crystals_remaining > 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
unsigned int ManaSpire::GetNumCrystalsRemaining() //returns the number of crystals remaining in this ManaSpire.
    {
        return this->num_crystals_remaining;
    }
bool ManaSpire::CanAffordCrystal(unsigned int crystal, double budget) //Returns true if this Mage can afford to purchase crystal with the given budget.
    {
        if(cost_per_crystal*crystal <= budget)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
double ManaSpire::GetCrystalCost(unsigned int crystal) //returns the cost (in gold pieces) for the specified number of crystals.
    {
        return crystal*this->cost_per_crystal;
    }
unsigned int ManaSpire::DistributeCrystals(unsigned int crystals_needed) //If the amount num_crystals_remaining in the ManaSpire is greater than or equal to crystals_needed, it subtract crystals_needed from ManaSpire amount and returns crystal_needed. If the amount of crystals in the ManaSpire is less, it returns the ManaSpire current amount, and the ManaSpire crystal amount is set to 0.
    {
        if(this->num_crystals_remaining >= crystals_needed)
        {
            this->num_crystals_remaining-= crystals_needed; //or this->num_crystals_remaining = this->num_crystals_remaining - crystals_needed;
            return crystals_needed;
        }
        else
        {
            unsigned int currentAmt = num_crystals_remaining;
            this->num_crystals_remaining = 0;
            return currentAmt;
        }
    }
bool ManaSpire::Update()
    {
        if(this->num_crystals_remaining == 0 && this->state != NO_CRYSTALS_AVAILABLE)
        {
            this->state = NO_CRYSTALS_AVAILABLE;
            this->display_code = 's';
            cout << "ManaSpire " << this->GetId() << " has ran out of crystals." << endl;
            return true;
        }
        else
        {
            return false;
        }
    }

void ManaSpire::ShowStatus()
    {
        cout << "ManaSpire Status: " << endl;
        Building::ShowStatus();
        cout << "Gold pieces per crystals: " << this->cost_per_crystal << endl;
        if(this->num_crystals_remaining == 1)
        {
            cout << "has " << num_crystals_remaining << " crystal remaining." << endl;
        }
        else
        {
            cout << "has " << num_crystals_remaining << " crystals remaining." << endl;
        }
    }

void ManaSpire::save(ofstream& file)
{
    Building::save(file);
    
    file << this->crystal_capacity << endl;
    file << this->num_crystals_remaining << endl;
    file << this->cost_per_crystal << endl;
    //rest of the variables are already being handled by Building.
}

void ManaSpire::restore(ifstream& file, Model& model)
{
    Building::restore(file, model);

    file >> this->crystal_capacity;
    file >> this->num_crystals_remaining;
    file >> this->cost_per_crystal;
}