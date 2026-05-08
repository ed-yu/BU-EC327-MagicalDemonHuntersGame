#include <iostream>
#include "RoamingDemon.h"
#include "Model.h"

using namespace std;

RoamingDemon::RoamingDemon(string name, double attack, double health, bool variant, int id, Point2D in_loc):GameObject(in_loc, id, 'W')
{
    this->name = name;
    this->attack = attack;
    this->health = health;
    this->variant = variant;
    this->bleedIntensity = 0;
    this->in_combat = false;
    this->current_mage = nullptr;
    this->state = IN_ENVIORMENT;
}

void RoamingDemon::follow(Mage* m)
{
    this->current_mage = m;
    this->state = IN_HUNT;
    m->SetFollowed(true , this);
}

bool RoamingDemon::get_variant()
{
    return this->variant;
}

double RoamingDemon::get_attack()
{
    return this->attack;
}

double RoamingDemon::get_health()
{
    return this->health;
}

bool RoamingDemon::get_in_combat()
{
    return this->in_combat;
}

bool RoamingDemon::Update()
{
    this->health -= getBleedIntensity();
    if(this->health <= 0)
    {
        this->state = DEAD;
    }

    switch(this->state){

        case(IN_ENVIORMENT):
            return false;
        case(DEAD):
            return false;
        case(IN_HUNT):
            if(this->current_mage != nullptr && this->current_mage->IsKnockedOut())
            {
                this->current_mage = nullptr;
                this->state = IN_ENVIORMENT;
                return false;
            }
            if(this->current_mage != nullptr)
            {
                Point2D target_loc = this->current_mage->GetLocation();

                if(this->location.x != target_loc.x || this->location.y !=target_loc.y)
                {
                    this->location = target_loc;
                    return true;
                }
            }
            return false;
        default:
            return false;
    }
}

void RoamingDemon::ShowStatus()
{
    cout << "Roaming Demon status: ";
    GameObject::ShowStatus();

    if(this->IsAlive())
    {
        cout << "Health: " << this->health << " Attack: " << this->attack << endl;
        if(this->state == IN_HUNT)
        {
            cout << "Currently hunting a Mage!" << endl;
        }
    }
    else
    {
        cout << this->GetId() << " | Dead." << endl; 
    }
}

bool RoamingDemon::IsAlive()
{
    if(this->health > 0)
    {
        return true;
    }
    return false;
}

bool RoamingDemon::ShouldBeVisible()
{
    return IsAlive();
}

void RoamingDemon::setBleedIntensity(double input)
{
    this->bleedIntensity = input;
}

double RoamingDemon::getBleedIntensity()
{
    return this->bleedIntensity;
}

void RoamingDemon::save(ofstream& file)
{
    GameObject::save(file);

    file << this->name << endl;
    file << this->attack << endl;
    file << this->health << endl;
    file << this->variant << endl;
    file << this->in_combat << endl;
    file << this->bleedIntensity << endl;
    if(this->current_mage != nullptr)
    {
        file << this->current_mage->GetId() << endl; //gets id of mage
    }
    else
    {
        file << -1 << endl; //null case
    }
}

void RoamingDemon::restore(ifstream& file, Model& model)
{
    GameObject::restore(file, model);

    file >> this->name;
    file >> this->attack;
    file >> this->health;
    file >> this->variant;
    file >> this->in_combat;
    file >> this->bleedIntensity;
    
    int currMageId; //temp val check
    file >> currMageId;

    if(currMageId != -1)
    {
        this->current_mage = model.GetMagePtr(currMageId);
    }
    else
    {
        this->current_mage = nullptr;
    }
}