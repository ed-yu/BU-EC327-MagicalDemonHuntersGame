#include <iostream>
#include <cstdlib>
#include <list>
#include <algorithm>
#include <istream>
#include "Model.h"
#include "Input_Handling.h"

using namespace std;

Model::Model()
{
    this->time = 0;

    // this->num_objects = 8;
    // this->num_mages = 2;
    // this->num_spires = 2;
    // this->num_hideouts = 2;
    // this->num_roamingdemons = 2;
   
    ManaSpire *S1 = new ManaSpire(1, 1.0, 100, Point2D(1,20));
    ManaSpire *S2 = new ManaSpire(2, 2.0, 200, Point2D(10,20));
    Mage *M1 = new Mage("Serena", 1, 'M', 1, Point2D(5,1));
    Mage *M2 = new Mage("Rumi", 2, 'M', 2, Point2D(10,1));
    DemonHideout *D1 = new DemonHideout(10, 1, 2.0, 3, 1, Point2D(0,0));
    DemonHideout *D2 = new DemonHideout(20, 5, 7.5, 4, 2, Point2D(5,5));
    RoamingDemon *R1 = new RoamingDemon("Demon1", 5.0, 2.0, false, 1, Point2D(10, 12));
    RoamingDemon *R2 = new RoamingDemon("Demon2", 5.0, 2.0, false, 2, Point2D(15, 5));
    AncientDemon *A1 = new AncientDemon("ADemon1", 10.0, 4.0, false, 1, Point2D(20,20));

    object_ptrs.push_back(M1);
    object_ptrs.push_back(M2);
    object_ptrs.push_back(S1);
    object_ptrs.push_back(S2);
    object_ptrs.push_back(D1);
    object_ptrs.push_back(D2);
    object_ptrs.push_back(R1);
    object_ptrs.push_back(R2);
    object_ptrs.push_back(A1);

    active_ptrs.push_back(M1);
    active_ptrs.push_back(M2);
    active_ptrs.push_back(S1);
    active_ptrs.push_back(S2);
    active_ptrs.push_back(D1);
    active_ptrs.push_back(D2);
    active_ptrs.push_back(R1);
    active_ptrs.push_back(R2);
    active_ptrs.push_back(A1);

    mage_ptrs.push_back(M1);
    mage_ptrs.push_back(M2);
    
    spire_ptrs.push_back(S1);
    spire_ptrs.push_back(S2);

    hideout_ptrs.push_back(D1);
    hideout_ptrs.push_back(D2);

    roamingdemon_ptrs.push_back(R1);
    roamingdemon_ptrs.push_back(R2);

    ancientdemon_ptrs.push_back(A1);

    cout << "Model default constructed" << endl;

}
Model::~Model()
{
    for(GameObject* obj : object_ptrs)
    {
        delete obj;
    }
    cout << "Model destructed." << endl;
}

Mage* Model::GetMagePtr(int id)
{
    for(Mage* mage : mage_ptrs)
    {
        if(mage->GetId() == id)
        {
            return mage;
        }
    }
    return 0; //default case if none is statisfied
}

ManaSpire* Model::GetManaSpirePtr(int id)
{
    for(ManaSpire* manaspire : spire_ptrs)
    {
        if(manaspire->GetId() == id)
        {
            return manaspire;
        }
    }
    return 0; //default case if none is statisfied
}

DemonHideout* Model::GetDemonHideoutPtr(int id)
{
    for(DemonHideout* demonhideout : hideout_ptrs)
    {
        if(demonhideout->GetId() == id)
        {
            return demonhideout;
        }
    }
    return 0; //default case if none is satisfied
}

RoamingDemon* Model::GetRoamingDemonPtr(int id)
{
    for(RoamingDemon* roamingdemon : roamingdemon_ptrs)
    {
        if(roamingdemon->GetId() == id)
        {
            return roamingdemon;
        }
    }
    return 0; //default case if none is satisfied
}

AncientDemon* Model::GetAncientDemonPtr(int id)
{
    for(AncientDemon* ancientdemon : ancientdemon_ptrs)
    {
        if(ancientdemon->GetId() == id)
        {
            return ancientdemon;
        }
    }
    return 0; //default case if none is satisfied
}

bool Model::Update()
{
    this->time++; //time increment
    bool updateprocess = false;
    for(GameObject* obj : active_ptrs)
    {
        if(obj->Update() == true)
        {
            updateprocess = true;
        }

    }
    for(RoamingDemon* roamingdemon : roamingdemon_ptrs)
    {
        for(Mage* mage : mage_ptrs)
        {
            double dist = GetDistanceBetween(roamingdemon->GetLocation(), mage->GetLocation());
            if(dist <= 1)//proximity
            {
                if(roamingdemon->GetState() != IN_HUNT)
                {
                    roamingdemon->follow(mage);
                    updateprocess = true;
                    cout << "A Roaming Demon has spotted a Mage! Following.." << endl;
                }
            }
        }
    }

    for(AncientDemon* ancientdemon : ancientdemon_ptrs)
    {
        for(Mage* mage : mage_ptrs)
        {
            double dist = GetDistanceBetween(ancientdemon->GetLocation(), mage->GetLocation());
            if(dist <= 1)//proximity
            {
                if(ancientdemon->GetState() != AD_IN_HUNT)
                {
                    ancientdemon->follow(mage);
                    updateprocess = true;
                    cout << "An Ancient Demon has spotted a Mage! Following.." << endl;
                }
            }
        }
    }

    for(Mage* obj : mage_ptrs)
    {
        if(obj->IsKnockedOut() == true)
        {
            if(find(active_ptrs.begin(), active_ptrs.end(), obj) != active_ptrs.end())
            {
                active_ptrs.remove(obj);
                cout << "Knocked out mage removed." << endl;
            }
        }
    }
    for(ManaSpire* obj : spire_ptrs)
    {
        if(obj->GetNumCrystalsRemaining() == 0)
        {
            if(find(active_ptrs.begin(), active_ptrs.end(), obj) != active_ptrs.end())
            {
                active_ptrs.remove(obj);
                cout << "Depleted mana spire removed." << endl;
            }
        }
    }
    for(DemonHideout* obj : hideout_ptrs)
    {
        if(obj->GetNumBattlesRemaining() == 0)
        {
            if(find(active_ptrs.begin(), active_ptrs.end(), obj) != active_ptrs.end())
            {
                active_ptrs.remove(obj);
                cout << "Defeated demon hideout removed." << endl;
            }
        }
    }
    for(RoamingDemon* obj : roamingdemon_ptrs)
    {
        if(obj->IsAlive() == false)
        {
            if(find(active_ptrs.begin(), active_ptrs.end(), obj) != active_ptrs.end())
            {
                active_ptrs.remove(obj);
                cout << "Dead roaming demon removed." << endl;
            }
        }
    }
    for(AncientDemon* obj : ancientdemon_ptrs)
    {
        if(obj->IsAlive() == false)
        {
            if(find(active_ptrs.begin(), active_ptrs.end(), obj) != active_ptrs.end())
            {
                active_ptrs.remove(obj);
                cout << "Dead ancient demon removed." << endl;
            }
        }
    }

    bool all_hideouts_passed = true;
    bool all_mages_inactive = true;
    for(DemonHideout* demonhideout : hideout_ptrs)
    {
        if(demonhideout->passed() != true)
        {
            all_hideouts_passed = false;
        }
    }
    for(Mage* mage : mage_ptrs)
    {
        if(mage->IsKnockedOut() != true)
        {
            all_mages_inactive = false;
        }
    }
    if(all_hideouts_passed == true)
    {
        cout << "GAME OVER: You win! All battles done!" << endl;
        exit(EXIT_SUCCESS);
    }
    else if(all_mages_inactive == true)
    {
        cout << "GAME OVER: You lose! All of your Mages' mana is lost!" << endl;
        exit(0);
    }
    return updateprocess;
}


void Model::Display(View& view)
    {
        cout << "Time: " << this->time << endl;
        view.Clear();
        
        for(GameObject* obj : active_ptrs)
        {
            view.Plot(obj);
        }
        view.Draw();
    }

void Model::ShowStatus()
{
    cout << "Time: " << this->time << endl;
    for(GameObject* obj : object_ptrs)
    {
        obj->ShowStatus(); //call function
    }
}

void Model::NewCommand(char type, int id, double x, double y)
{
    try{
        switch(type)
        {
            case('s'):
            {
                for(ManaSpire* obj : spire_ptrs)
                {
                    if(id == obj->GetId())
                    {
                        throw Invalid_Input("Duplicate ID");
                    }
                }
                ManaSpire* addedSpire = new ManaSpire(id, 1.0, 100, Point2D(x,y));
                object_ptrs.push_back(addedSpire);
                active_ptrs.push_back(addedSpire);
                spire_ptrs.push_back(addedSpire);
                break;
            }
            case('d'):
            {
                for(DemonHideout* obj : hideout_ptrs)
                {
                    if(id==obj->GetId())
                    {
                        throw Invalid_Input("Duplicate ID");
                    }
                }
                DemonHideout* addedHideout = new DemonHideout(10, 1, 2.0, 2, id, Point2D(x,y));
                object_ptrs.push_back(addedHideout);
                active_ptrs.push_back(addedHideout);
                hideout_ptrs.push_back(addedHideout);
                break;
            }
            case('g'):
            {
                for(Mage* obj : mage_ptrs)
                {
                    if(id==obj->GetId())
                    {
                        throw Invalid_Input("Duplicate ID");
                    }
                }
                Mage* addedMage = new Mage("Additional", id, 'M', 1, Point2D(x,y));
                object_ptrs.push_back(addedMage);
                active_ptrs.push_back(addedMage);
                mage_ptrs.push_back(addedMage);
                break;     
            }           
            case('o'):
            {
                for(RoamingDemon* obj : roamingdemon_ptrs)
                {
                    if(id==obj->GetId())
                    {
                        throw Invalid_Input("Duplicate ID");
                    }
                }
                RoamingDemon* addedRoam = new RoamingDemon("AddedDemon", 5.0, 2.0, false, id, Point2D(x,y));
                object_ptrs.push_back(addedRoam);
                active_ptrs.push_back(addedRoam);
                roamingdemon_ptrs.push_back(addedRoam);
                break;
            }
            case('z'):
            {
                for(AncientDemon* obj : ancientdemon_ptrs)
                {
                    if(id==obj->GetId())
                    {
                        throw Invalid_Input("Duplicate ID");
                    }
                }
                AncientDemon* addedAnc = new AncientDemon("AddedADemon", 5.0, 2.0, false, id, Point2D(x,y));
                object_ptrs.push_back(addedAnc);
                active_ptrs.push_back(addedAnc);
                ancientdemon_ptrs.push_back(addedAnc);
                break;
            }

            default:
            throw Invalid_Input("Invalid command.");

        }
    }
    catch(Invalid_Input& except)
    {
        cout << "ERROR: Invalid Input - " << except.msg_ptr << endl;
    }
}

void Model::save(ofstream& file)
{
    file << this->time << endl;
    file << this->active_ptrs.size() << endl;

    for(GameObject* obj : active_ptrs)
    {
        file << obj->GetDisplayCode() << obj->GetId() << endl;
    }
    for(GameObject* obj : active_ptrs)
    {
        obj->save(file);
    }
}

void Model::restore(ifstream& file)
{
    //clear process
    for(GameObject *obj : object_ptrs)
    {
        delete obj;
    }

    object_ptrs.clear();
    active_ptrs.clear();
    mage_ptrs.clear();
    spire_ptrs.clear();
    hideout_ptrs.clear();
    roamingdemon_ptrs.clear();
    ancientdemon_ptrs.clear();
    //terminus of clear process

    file >> this->time;
    int numObjects; //temp val check
    file >> numObjects;

    for(int x = 0; x < numObjects; x++)
    {
        char type;
        int id;
        file >> type >> id;

        GameObject* new_obj = nullptr; //temp
        //default values here will be overwritten in the coming restoration process
        if(type == 'M')
        {
            Mage* m = new Mage("Restored", id, 'M', 5, Point2D(0,0));
            mage_ptrs.push_back(m);
            new_obj = m;
        }
        else if(type == 'S')
        {
            ManaSpire* s = new ManaSpire(id, 1.0, 100, Point2D(0,0));
            spire_ptrs.push_back(s);
            new_obj = s;
        }
        else if(type == 'D')
        {
            DemonHideout* d = new DemonHideout(10, 1, 1.0, 2, id, Point2D(0,0));
            hideout_ptrs.push_back(d);
            new_obj = d;
        }
        else if(type == 'W')
        {
            RoamingDemon* r = new RoamingDemon("Restored", 5.0, 2.0, false, id, Point2D(0,0));
            roamingdemon_ptrs.push_back(r);
            new_obj = r;
        }
        else if(type == 'X')
        {
            AncientDemon* z = new AncientDemon("Restored", 10.0, 4.0, false, id, Point2D(0,0));
            ancientdemon_ptrs.push_back(z);
            new_obj = z;
        }

        if(new_obj != nullptr)
        {
            object_ptrs.push_back(new_obj);
            active_ptrs.push_back(new_obj);
        }
    }
    //restoration process
    for(GameObject* obj : active_ptrs)
    {
        obj->restore(file, *this);
    }
}