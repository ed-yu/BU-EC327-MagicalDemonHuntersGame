#include <iostream>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include "Mage.h"
#include "ManaSpire.h"
#include "DemonHideout.h"
#include "RoamingDemon.h"
#include "AncientDemon.h"
#include "Model.h"

using namespace std;

Mage::Mage() : GameObject('M') //default constructor
{
    this->speed = 5;
    this->mana = 20;
    this->experience = 0;
    this->gold_pieces = 0.0;
    this->battles_to_buy =0;
    this->crystals_to_buy = 0;
    this->is_at_spire = false;
    this->is_in_hideout = false;
    this->name = "";
    this->state = STOPPED;
    this->current_spire = nullptr;
    this->current_hideout = nullptr;
    this->currentFollower = nullptr;
    this->currentAncientCurse = nullptr;
    this->isCursed = false;
    this->isFollowed = false;
    cout<< "Mage default constructed." << endl;
}
Mage::Mage(char in_code) : GameObject(in_code)
{
    this->speed = 5;
    this->mana = 20;
    this->experience = 0;
    this->gold_pieces = 0.0;
    this->battles_to_buy =0;
    this->crystals_to_buy = 0;
    this->is_at_spire = false;
    this->is_in_hideout = false;
    this->name = "";
    this->current_spire = nullptr;
    this->current_hideout = nullptr;
    this->currentFollower = nullptr;
    this->currentAncientCurse = nullptr;
    this->isCursed = false;
    this->state = STOPPED;
    this->isFollowed = false;
    cout << "Mage constructed." << endl;
}
Mage::Mage(string in_name, int in_id, char in_code, unsigned int in_speed, Point2D in_loc) : GameObject(in_loc, in_id, in_code)
{
    this->mana = 20;
    this->experience = 0;
    this->gold_pieces = 0.0;
    this->battles_to_buy =0;
    this->crystals_to_buy = 0;
    this->is_at_spire = false;
    this->is_in_hideout = false;
    this->current_spire = nullptr;
    this->current_hideout = nullptr;
    this->currentFollower = nullptr;
    this->currentAncientCurse = nullptr;
    this->isCursed = false;
    this->state = STOPPED;
    this->speed = in_speed;
    this->name = in_name;
    this->isFollowed = false;
    cout << "Mage constructed." << endl;
}
Mage::~Mage()
{
    cout << "Mage destructed." << endl;
}
void Mage::StartMoving(Point2D dest)
{
    if(this->location.x == dest.x && this->location.y == dest.y)
    {
        cout << this->display_code << this->id_num << ": I'm already there. See?" << endl;
        return;
    }
    if (this->is_at_spire) 
    {
        this->current_spire->RemoveOneMage();
        this->is_at_spire = false;
    }
    if (this->is_in_hideout) 
    {
        this->current_hideout->RemoveOneMage();
        this->is_in_hideout = false;
    }
    SetupDestination(dest);
    this->state = MOVING;


    if(this->IsKnockedOut() == true)
    {
        cout << this->display_code << this->id_num << ": I am knocked out. I may move but you cannot see me." << endl;
    }
    else
    {
        cout << this->display_code << this->id_num << ": On my way." << endl;
    }

}

void Mage::StartMovingToHideout(DemonHideout* hideout)
{  
    if(is_in_hideout == true)
    {
        cout << this->display_code << this->id_num << ": I am already at the Demon Hideout!" << endl; 
        return;
    }
    if (this->is_at_spire) 
    {
        this->current_spire->RemoveOneMage();
        this->is_at_spire = false;
    }
    if (this->is_in_hideout) 
    {
        this->current_hideout->RemoveOneMage();
        this->is_in_hideout = false;
    }

    this->current_hideout = hideout;
    SetupDestination(hideout->GetLocation());

    if(this->IsKnockedOut() == true)
    {
        cout << this->display_code << this->id_num << ": I am knocked out so I can't move to hideout..." << endl; 
    }
    else
    {
        this->state = MOVING_TO_HIDEOUT;
        cout << this->display_code << this->id_num << ": on my way to hideout " << this->current_hideout->GetId() << endl; 
    }
}

void Mage::StartMovingToSpire(ManaSpire* spire)
{
    if(is_at_spire == true)
    {
        cout << this->display_code << this->id_num << ": I am already at the spire!" << endl;
        return;
    }

    if (this->is_at_spire) 
    {
        this->current_spire->RemoveOneMage();
        this->is_at_spire = false;
    }
    if (this->is_in_hideout) 
    {
        this->current_hideout->RemoveOneMage();
        this->is_in_hideout = false;
    }

    this->current_spire = spire;
    SetupDestination(spire->GetLocation());

    if(this->mana == 0)
    {
        cout << this->display_code << this->id_num << ": I am knocked out so I should have gone to the spire..." << endl;
    }
    
    else
    {
        this->state = MOVING_TO_SPIRE;
        cout << this->display_code << this->id_num << ": On my way to Spire " << this->current_spire->GetId() << endl;
    }
}

void Mage::StartBattling(unsigned int num_battles)
{
    if(this->mana == 0)
    {
        cout << this->display_code << this->id_num << ": I'm knocked out and out of mana so no more battles for me..." << endl;
    }
    else if(this->is_in_hideout == false)
    {
        cout << this->display_code << this->id_num << ": I can only battle in a DemonHideout!" << endl;
    }
    else if(this->gold_pieces < this->current_hideout->GetGoldCost(num_battles))
    {
        cout << this->display_code << this->id_num << ": Not enought money for battles." <<endl;
    }
    else if(this->current_hideout->GetNumBattlesRemaining() == 0)
    {
        cout << this->display_code << this->id_num << ": Cannot battle! This DemonHideout has no more mages to battle!" << endl;
    }
    else
    {
        this->state = BATTLING_IN_HIDEOUT;

        this->battles_to_buy = num_battles;
        this->current_hideout->DemonBattle(battles_to_buy);
        cout << this->display_code << this->id_num << ": Started to battle at the DemonHideout " << this->current_hideout->GetId() << " with " << num_battles << " battles." << endl;
    }
}

void Mage::StartRecoveringMana(unsigned int num_crystals)
{
    if(this->is_at_spire == false)
    {
        cout << this->display_code << this->id_num << ": I can only recover mana at a Mana Spire!" << endl;
    }
    else if(this->current_spire->CanAffordCrystal(num_crystals, this->gold_pieces) == false)
    {
        cout << this->display_code << this->id_num << ": Not enough money to recover mana." << endl;
    }
    else if(this->current_spire->GetNumCrystalsRemaining()<1)
    {
        cout << this->display_code << this->id_num << ": Cannot recover! No crystal remaining in this Mana Spire." << endl;
    }
    else
    {
        this->state = RECOVERING_MANA;
        cout << this->display_code << this->id_num << ": Started recovering " << num_crystals << " crystals at Mana Spire " << this->current_spire->GetId() << endl;
        this->crystals_to_buy = this->current_spire->DistributeCrystals(num_crystals);
    }
}

void Mage::Stop()
{
    this->state = STOPPED;
    cout << this->display_code << this->id_num << ": Stopping.." << endl;
}

bool Mage::IsKnockedOut()
{
    if(this->mana == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
    return false; //occurs if fatal
}

bool Mage::ShouldBeVisible()
{
    if(this->IsKnockedOut() == false)
    {
        return true;
    }
    else
    {
        return false;
    }
    return false; //occurs if fatal
}

void Mage::setFreeCase(double input)
{
    if(this->mana>= input*2) //2x
    {
        this->mana -= input*2;
        this->currentAncientCurse->setFreeIntensity(input);
    }
}

void Mage::setBleedCase(double input)
{
    if(this->isFollowed == true)
    {
        if(this->mana>=input)
        {
            this->mana -= input;
            this->currentFollower->setBleedIntensity(input);
            cout << "Used mana to fight Roaming Demon with intensity " << input << "!"<< endl;
        }
        else
        {
            cout << "Not enought mana!" << endl;
        }
    }
}

void Mage::ShowStatus()
{
    cout << this->name << " status: ";
    GameObject::ShowStatus();

    switch(this->state) 
    {
        case STOPPED:
            cout << " stopped" << endl;
            break;
        case MOVING:
            cout << " moving at a speed of " << this->speed << " to destination " << this->destination << " at each step of " << this->delta << endl;
            break;
        case MOVING_TO_HIDEOUT:
            cout << " heading to DemonHideout " << this->current_hideout->GetId() << " at a speed of " << this->speed << " at each step of " << this->delta << endl;
            break;
        case MOVING_TO_SPIRE:
            cout << " heading to Mana Spire " << this->current_spire->GetId() << " at a speed of " << this->speed << " at each step of " << this->delta << endl;
            break;
        case IN_HIDEOUT:
            cout << " inside Demon Hideout " << this->current_hideout->GetId() << endl;
            break;
        case AT_SPIRE:
            cout << " inside Mana Spire " << this->current_spire->GetId() << endl;
            break;
        case KNOCKED_OUT:
            cout << " knocked out" << endl;
            break;
        case BATTLING_IN_HIDEOUT:
            cout << " battling in DemonHideout " << this->current_hideout->GetId() << endl;
            break;
        case RECOVERING_MANA:
            cout << " recovering mana in Mana Spire " << this->current_spire->GetId() << endl;
            break;
        default:
            cout << "FATAL ERROR --should not have occured.";
            break;
    }
    cout << "Mana: " << this->mana << endl;
    cout << "Gold Pieces: " << this-> gold_pieces << endl;
    cout << "Experience: " << this->experience << endl;

}

bool Mage::Update()
{
    if(this->isFollowed == true)
    {
        if(this->mana >=currentFollower->get_attack())
        {
        this->mana -= currentFollower->get_attack();  
        }
        else
        {
            this->mana = 0;
        }
        cout<< "The Roaming Demon is draining " << this->name << "'s mana! Current mana is now: " << this->mana << " with a bleed intensity of 1." << endl; 
        
        if(this->mana == 0)
        {
            this->state = KNOCKED_OUT;
            cout << this->name << " is out of mana and can't move!" << endl;
        }
    }

    if(this->isCursed == true && this->currentAncientCurse != nullptr)
    {
        if(this->mana >=currentAncientCurse->get_attack())
        {
        this->mana -= currentAncientCurse->get_attack();  
        }
        else
        {
            this->mana = 0;
        }
        cout<< "The Ancient Demon is draining " << this->name << "'s mana! Current mana is now: " << this->mana << " with a bleed intensity of " << this->currentAncientCurse->get_attack() << "." << endl; 
        
        if(this->mana == 0)
        {
            this->state = KNOCKED_OUT;
            cout << this->name << " is out of mana and can't move!" << endl;
        }
    }
    switch(this->state)
    {  
        case STOPPED:
            // if(this->mana == 0)
            // {
            //     cout << this->name << " is out of mana and can't move" << endl;
            //     this->state = KNOCKED_OUT;
            //     return true;
            // }
            return false;
        case MOVING:
            if(this->UpdateLocation())
            {
                if(this->state != KNOCKED_OUT)
                {
                    this->state = STOPPED;
                }
                
                return true;
            }
            return false;
        case MOVING_TO_HIDEOUT:
            if(this->UpdateLocation())
            {
                if(this->state != KNOCKED_OUT)
                {
                    this->state = IN_HIDEOUT;
                    this->is_in_hideout = true;
                    this->current_hideout->AddOneMage();
                }
                
                return true;
            }
            return false;
        case MOVING_TO_SPIRE:
            if(this->UpdateLocation())
            {
                if(this->state != KNOCKED_OUT)
                {
                    this->state = AT_SPIRE;
                    this->is_at_spire = true;
                    this->current_spire->AddOneMage();
                }
                return true;
            }
            return false;
        case IN_HIDEOUT:
            return false;
        case AT_SPIRE:
            return false;
        case BATTLING_IN_HIDEOUT:
            this->mana -= this->current_hideout->GetManaCost(this->battles_to_buy);
            this->gold_pieces -= this->current_hideout->GetGoldCost(this->battles_to_buy);
            this->experience += this->current_hideout->GetExperiencePerBattle() * this->battles_to_buy;
            if(battles_to_buy == 1)
            {
                cout << "** " << this->name << " completed " << this->battles_to_buy << " battle! **" << endl;
            }
            else
            {
                cout << "** " << this->name << " completed " << this->battles_to_buy << " battles! **" << endl;
            }
            cout << "** " << this->name << " gained " << this->current_hideout->GetExperiencePerBattle()*this->battles_to_buy << " experience! **" << endl;
            this->state = IN_HIDEOUT;
            return true;
        case KNOCKED_OUT:
            return false;
        case RECOVERING_MANA:
            //StartRecoveringMana(this->crystals_to_buy);
            this->gold_pieces -= this->current_spire->GetCrystalCost(this->crystals_to_buy);
            this->mana += 5.0*this->crystals_to_buy;
            cout << "**" << this->name << " recovered " << this->crystals_to_buy*5 << " mana!**" << endl;
            if(this->crystals_to_buy == 1)
            {
                cout << "**" << this->name << " bought " << this->crystals_to_buy << " crystal!**" << endl;
            }
            else
            {
                cout << "**" << this->name << " bought " << this->crystals_to_buy << " crystals!**" << endl;
            }
            this->state = AT_SPIRE;
            return true;
        default:
            cout << "FATAL ERROR --should not have occured.";
            return false;
    }
    return false;
}


bool Mage::UpdateLocation()
{
    if(fabs(destination.x - location.x) <= fabs(delta.x) && fabs(destination.y - location.y) <= fabs(delta.y))
    {
        this->location = this->destination;
        cout << this->display_code << this->id_num << ": I'm there!" << endl;
        return true;
    }
    else
    {
        if(this->mana == 0)
            {
                cout << this->name << " is out of mana and can't move" << endl;
                this->state = KNOCKED_OUT;
                return true;
            }
        this->location = (this->location + this->delta);
        cout << this->display_code << this->id_num << ": step..." << endl;
        if(!IsKnockedOut())
        {
            this->mana--;
        }
        this->gold_pieces += GetRandomAmountOfGP();
    
        return false;
    }
    
}

void Mage::SetupDestination(Point2D dest)
{
    this->destination = dest;
    this->delta = (this->destination - this->location) * (this->speed / GetDistanceBetween(this->destination, this->location));

}

string Mage::GetName()
{
    return this->name;
}

bool Mage::IsBeingFollowed()
{
    return this->isFollowed;
}

bool Mage::IsCursed()
{
    return this->isCursed;
}

void Mage::SetCurse(bool setter, AncientDemon* follower)
{
    this->isCursed = setter;
    this->currentAncientCurse = follower;
}

void Mage::SetFollowed(bool setter, RoamingDemon* follower)
{
    this->isFollowed = setter;
    this->currentFollower = follower;
}

void Mage::AncientRelief(bool status)
{
    if(status == true)
    {
        this->mana += 50; //reward for defeating an ancient demon
    }
}

void Mage::save(ofstream& file)
{
    GameObject::save(file);

    file << this->speed << endl;
    file << this->mana << endl;
    file << this->experience << endl;
    file << this->gold_pieces << endl;
    file << this->battles_to_buy << endl;
    file << this->crystals_to_buy << endl;
    file << this->is_at_spire << endl;
    file << this->is_in_hideout << endl;
    file << this->name << endl;
    file << this->destination.x << endl;
    file << this->destination.y << endl;
    file << this->delta.x << endl;
    file << this->delta.y << endl;
    file << this->isFollowed << endl;
    file << this->isCursed << endl;

    if(this->current_spire != nullptr)
    {
        file << this->current_spire->GetId() << endl; //gets object id if pointer is found
    }
    else
    {
        file << -1 << endl; //null case
    }

    if(this->current_hideout != nullptr)
    {
        file << this->current_hideout->GetId() << endl; //gets object id if pointer is found
    }
    else
    {
        file << -1 << endl; //null case
    }

    if(this->currentFollower != nullptr) //gets object id if pointer is found
    {
        file << this->currentFollower->GetId() << endl;
    }
    else
    {
        file << -1 << endl; //null case
    }

    if(this->currentAncientCurse != nullptr) //gets object id if pointer is found
    {
        file << this->currentAncientCurse->GetId() << endl;
    }
    else
    {
        file << -1 << endl; //null case
    }
}

void Mage::restore(ifstream& file, Model& model)
{
    GameObject::restore(file, model);

    file >> this->speed;
    file >> this->mana;
    file >> this->experience;
    file >> this->gold_pieces;
    file >> this->battles_to_buy;
    file >> this->crystals_to_buy;
    file >> this->is_at_spire;
    file >> this->is_in_hideout;
    file >> this->name;
    file >> this->destination.x;
    file >> this->destination.y;
    file >> this->delta.x;
    file >> this->delta.y;
    file >> this->isFollowed;
    file >> this->isCursed;

    int spireId; //temp val check
    file >> spireId;

    if(spireId != -1)
    {
        this->current_spire = model.GetManaSpirePtr(spireId);
    }
    else
    {
        this->current_spire = nullptr;
    }

    int hideoutId; //temp val check
    file >> hideoutId;

    if(hideoutId != -1)
    {
        this->current_hideout = model.GetDemonHideoutPtr(hideoutId);
    }
    else
    {
        this->current_hideout = nullptr;
    }
    
    int currentFollowerId; //temp val check
    file >> currentFollowerId;

    if(currentFollowerId != -1)
    {
        this->currentFollower = model.GetRoamingDemonPtr(currentFollowerId);
    }
    else
    {
        this->currentFollower = nullptr;
    }

    int currentAncientId; //temp val check
    file >> currentAncientId;

    if(currentAncientId != -1)
    {
        this->currentAncientCurse = model.GetAncientDemonPtr(currentAncientId);
    }
    else
    {
        this->currentAncientCurse = nullptr;
    }
}

double GetRandomAmountOfGP()
{
    return ((double)rand()/RAND_MAX)*2.0 ;
}