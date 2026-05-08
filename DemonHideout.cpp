#include <iostream>
#include "DemonHideout.h"
#include "GameObject.h"
#include "Point2D.h"
#include "Model.h"

using namespace std;

DemonHideout::DemonHideout() : Building() //default constructor
{
    this->display_code = 'D';
    this->state = NOT_DEFEATED;
    this->max_number_of_battles = 10;
    this->num_battle_remaining = this->max_number_of_battles;
    this->mana_cost_per_battle = 1;
    this->gold_cost_per_battle = 1.0;
    this->experience_per_battle = 2;
    cout << "DemonHideout default constructed." << endl;
}
DemonHideout::DemonHideout(unsigned int max_battle, unsigned int mana_loss, double cost, unsigned int exp_per_battle, int in_id, Point2D in_loc) : Building('D', in_id, in_loc) //parameter constructor
{
    this->id_num = in_id;
    this->max_number_of_battles = max_battle;
    this->mana_cost_per_battle = mana_loss;
    this->experience_per_battle = exp_per_battle;
    this->gold_cost_per_battle = cost;
    this->location = in_loc;
    this->num_battle_remaining = this->max_number_of_battles; //check_________
    this->state = NOT_DEFEATED; //check___________________
    cout << "DemonHideout constructed." << endl;

}
DemonHideout::~DemonHideout()
{
    cout << "DemonHideout destructed." << endl;
}

double DemonHideout::GetGoldCost(unsigned int battle_qty) //returns the cost of battling battle_qty times (in gold).
{
    return this->gold_cost_per_battle*battle_qty;
}

unsigned int DemonHideout::GetManaCost(unsigned int battle_qty) //returns the amount of mana points required for battle_qty battles.
{
    return this->mana_cost_per_battle*battle_qty;
}

unsigned int DemonHideout::GetNumBattlesRemaining() //returns the number of battles reamining in this DemonHideout.
{
    return this->num_battle_remaining;
}

bool DemonHideout::IsAbleToBattle(unsigned int battle_qty, double budget, unsigned int mana) //returns true if a Mage in DemonHideout with a given budget and mana can requrest to take battle_qty battle, returns false otherwise.
{
    if(GetGoldCost(battle_qty) <= budget && GetManaCost(battle_qty) <= mana)
    {
        return true;
    }
    else
    {
        return false;
    }
    return false; //occurs if fatal
}

unsigned int DemonHideout::DemonBattle(unsigned int battle_units) //subtracts battles from num_battles_reamining if this DemonHideout has enough units. If the amount of battes requested is greater than the amount available at this DemonHideout, then num_battles_remaining will be used instead of battle_units when calculating experience gain. Returns the amount of experience gained by winning the battles. Experience points can be calculated using (number of bottles)*experience_per_battle.
{
    if(battle_units<=num_battle_remaining)
    {
        this->num_battle_remaining -= battle_units;
        return this->experience_per_battle*battle_units;
    }
    else
    {
        unsigned int experience = this->num_battle_remaining;
        this->num_battle_remaining = 0;
        return experience*this->experience_per_battle;
    }
    return 0; //occurs if fatal
    
}

unsigned int DemonHideout::GetExperiencePerBattle() //Returns the experience gained from each battle.
{
    return this->experience_per_battle;
}

bool DemonHideout::Update() //if the DemonHideout has zero battles remaining, set the state to DEFEATED and display_code to 'd'. Then print the message "(display_code)(id) has been beaten". Returns false if battles still remain within the DemonHideout. This function shouldn't keep returning true if the DemonHideout is passed. It should return true ONLY at the time when the Demon Hideout is defeated, return false for later "Update()" function calls.
{
    if(this->num_battle_remaining == 0 && this->state != DEFEATED)
    {
        this->state = DEFEATED;
        this->display_code = 'd';
        cout << this->display_code << this->id_num << " has been beaten." << endl;
        return true;
    }
    else
    {
        return false;
    }
    return false; //occurs if fatal
}

bool DemonHideout::passed() //returns true if battles remaining is 0.
{
    if(this->num_battle_remaining == 0)
    {
        return true;
    }
    return false;
}

void DemonHideout::ShowStatus() //prints out the status of the object by calling GameObject's show status and the values of its member variables.
{
    cout << "DemonHideoutStatus: ";
    Building::ShowStatus();
    cout << "Max number of battles: " << this->max_number_of_battles << endl;
    cout << "Mana cost per battle: " << this->mana_cost_per_battle << endl;
    cout << "Gold per battle: " << this->gold_cost_per_battle << endl;
    cout << "Experience per battle: " << this->experience_per_battle << endl;
    if(num_battle_remaining == 1)
    {
        cout << this->num_battle_remaining << " battle is remaining for this DemonHideout." << endl;
    }
    else
    {
        cout << this->num_battle_remaining << " battles are remaining for this DemonHideout." << endl;
    }
}

void DemonHideout::save(ofstream& file)
{
    Building::save(file);

    file << this->max_number_of_battles << endl;
    file << this->num_battle_remaining << endl;
    file << this->mana_cost_per_battle << endl;
    file << this->gold_cost_per_battle << endl;
    file << this->experience_per_battle << endl;

}

void DemonHideout::restore(ifstream& file, Model& model)
{
    Building::restore(file, model);

    file >> this->max_number_of_battles;
    file >> this->num_battle_remaining;
    file >> this->mana_cost_per_battle;
    file >> this->gold_cost_per_battle;
    file >> this->experience_per_battle;
}