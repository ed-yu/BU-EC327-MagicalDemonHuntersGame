#include <iostream>
#include "Building.h"
#include "Model.h"

using namespace std;


Building::Building() : GameObject('B') //default constructor, display code is set to 'B', default build
    {
        cout << "Building default constructed" << endl;
    }
Building::Building(char in_code, int in_Id, Point2D in_loc) : GameObject(in_loc, in_Id, in_code) //constructor initializes the idnumber, location, and remainder member variables to their default initial values.
    {
        //(Point2D in_loc, int in_id, char in_code)
        cout << "Building constructed" << endl;
    }

void Building::AddOneMage() //Increments mage_count by one.
    {
       this->mage_count++;
    }

void Building::RemoveOneMage() //Decrements mage_count by one.
    {
        this->mage_count--;
    }
void Building::ShowStatus() //prints "(display_code)(id) located at (location)" Prints "(mage_count) mage(s) is/ar in this building"
    {
        GameObject::ShowStatus();

        if(this->mage_count == 1) //plural vs singular check and statement
        {
            cout <<  this->mage_count << " mage is in this building" << endl;
        }
        else
        {
            cout << this->mage_count << " mages are in this building" << endl;
        }
    }

bool Building::ShouldBeVisible() //returns true as buildings are always visible;
    {
        return true;
    }

void Building::save(ofstream& file)
{
    GameObject::save(file);
    file << this->mage_count << endl;
}

void Building::restore(ifstream& file, Model& model)
{
    GameObject::restore(file, model);

    file >> this->mage_count;
}