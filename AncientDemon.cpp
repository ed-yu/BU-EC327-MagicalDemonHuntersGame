#include <iostream>
#include "AncientDemon.h"
#include "Model.h"

using namespace std;

AncientDemon::AncientDemon(string name, double attack, double health, bool variant, int id, Point2D in_loc):GameObject(in_loc, id, 'X')
{
    this->name = name;
    this->attack = attack;
    this->health = health;
    this->variant = variant;
    this->freeIntensity = 0;
    this->in_combat = false;
    this->current_mage = nullptr;
    this->state = AD_IN_ENVIORMENT;
    this->drained = false;
}

void AncientDemon::follow(Mage* m)
{
    this->current_mage = m;
    this->state = AD_IN_HUNT;
    m->SetCurse(true , this);
}

bool AncientDemon::get_variant()
{
    return this->variant;
}

double AncientDemon::get_attack()
{
    return this->attack;
}

double AncientDemon::get_health()
{
    return this->health;
}

bool AncientDemon::get_in_combat()
{
    return this->in_combat;
}

bool AncientDemon::Update()
{
    this->health -= getFreeIntensity();
    if(this->health <= 0)
    {
        this->state = AD_DEAD;
        if(this->drained == false && this->current_mage != nullptr)
        {
            this->drained = true;
            this->current_mage->AncientRelief(true);
        }
    }

    switch(this->state){

        case(AD_IN_ENVIORMENT):
            return false;
        case(AD_DEAD):
            return false;
        case(AD_IN_HUNT):
            if(this->current_mage != nullptr && this->current_mage->IsKnockedOut())
            {
                this->current_mage = nullptr;
                this->state = AD_IN_ENVIORMENT;
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

void AncientDemon::ShowStatus()
{
    cout << "Ancient Demon status: ";
    GameObject::ShowStatus();

    if(this->IsAlive())
    {
        cout << "Health: " << this->health << " Attack: " << this->attack << endl;
        if(this->state == AD_IN_HUNT)
        {
            cout << "Currently hunting a Mage!" << endl;
        }
    }
    else
    {
        cout << this->GetId() << " | Dead." << endl; 
    }
}

bool AncientDemon::IsAlive()
{
    if(this->health > 0)
    {
        return true;
    }
    return false;
}

bool AncientDemon::ShouldBeVisible()
{
    return IsAlive();
}

void AncientDemon::setFreeIntensity(double input)
{
    this->freeIntensity = input;
}

double AncientDemon::getFreeIntensity()
{
    return this->freeIntensity;
}

void AncientDemon::save(ofstream& file)
{
    GameObject::save(file);

    file << this->name << endl;
    file << this->attack << endl;
    file << this->health << endl;
    file << this->variant << endl;
    file << this->drained << endl;
    file << this->in_combat << endl;
    file << this->freeIntensity << endl;
    if(this->current_mage != nullptr)
    {
        file << this->current_mage->GetId() << endl; //gets id of mage
    }
    else
    {
        file << -1 << endl; //null case
    }
}

void AncientDemon::restore(ifstream& file, Model& model)
{
    GameObject::restore(file, model);

    file >> this->name;
    file >> this->attack;
    file >> this->health;
    file >> this->variant;
    file >> this->drained;
    file >> this->in_combat;
    file >> this->freeIntensity;
    
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