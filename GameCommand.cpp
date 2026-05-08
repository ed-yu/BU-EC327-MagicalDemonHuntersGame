#include <iostream>
#include <istream>
#include <cstdlib>
#include <fstream>
#include "GameCommand.h"
#include "Model.h"
#include "Input_Handling.h"

class Model;

using namespace std;

void DoMoveCommand(Model& model, int mage_id, Point2D p1)
{
    if(model.GetMagePtr(mage_id) != 0)
    {
        cout << "Moving " << model.GetMagePtr(mage_id)->GetName() << " to " << p1 << endl;
        model.GetMagePtr(mage_id)->StartMoving(p1);
    }
    else
    {
        throw Invalid_Input("Please enter valid Mage ID.");
    }
    
}

void DoMoveToSpireCommand(Model& model, int mage_id, int spire_id)
{
    if(model.GetMagePtr(mage_id) != 0 && model.GetManaSpirePtr(spire_id) !=0)
    {
        cout << "Moving " << model.GetMagePtr(mage_id)->GetName() << " to Mana Spire " << spire_id << endl;
        model.GetMagePtr(mage_id)->StartMovingToSpire(model.GetManaSpirePtr(spire_id));
    }
    else
    {
        throw Invalid_Input("Please enter valid Mage ID and Mana Spire ID.");
    }

}

void DoMoveToHideoutCommand(Model& model, int mage_id, int hideout_id)
{
    if(model.GetMagePtr(mage_id) != 0 && model.GetDemonHideoutPtr(hideout_id) !=0)
    {
        cout << "Moving " << model.GetMagePtr(mage_id)->GetName() << " to hideout " << hideout_id << endl;
        model.GetMagePtr(mage_id)->StartMovingToHideout(model.GetDemonHideoutPtr(hideout_id));
    }
    else
    {
        throw Invalid_Input("Please enter valid Mage ID and Demon Hideout ID.");
    }
}
void DoStopCommand(Model& model, int mage_id)
{
    if(model.GetMagePtr(mage_id) != 0)
    {
        cout << "Stopping " << model.GetMagePtr(mage_id)->GetName() << endl;
        model.GetMagePtr(mage_id)->Stop();
    }
    else
    {
        throw Invalid_Input("Please enter valid Mage ID.");
    }
}

void DoBattleCommand(Model& model, int mage_id, unsigned int battles)
{
    if(model.GetMagePtr(mage_id) != 0)
    {
        cout << model.GetMagePtr(mage_id)->GetName() << " is battling" << endl;
        model.GetMagePtr(mage_id)->StartBattling(battles);
    }
    else
    {
        throw Invalid_Input("Please enter valid Mage ID.");
    }

}

void DoRecoverInSpireCommand(Model& model, int mage_id, unsigned int crystals_needed)
{
    if(model.GetMagePtr(mage_id) != 0)
    {
        cout << "Recovering " << model.GetMagePtr(mage_id)->GetName() << "'s mana" << endl;
        model.GetMagePtr(mage_id)->StartRecoveringMana(crystals_needed);
    }
    else
    {
        throw Invalid_Input("Please enter valid Mage ID.");
    }
}

void DoAdvanceCommand(Model& model, View& view)
{
    cout << "Advancing one tick." << endl;
    model.Update();
    model.ShowStatus();
    model.Display(view);
}

void DoRunCommand(Model& model, View& view)
{
    cout << "Advancing to next event." << endl;
    int counter = 0;
    bool event = false;
    while(counter < 5 && event != true)
    {
        event = model.Update();
        counter++;
    }
    model.ShowStatus();
    model.Display(view);

}

void DoBleedCommand(Model& model, int mage_id, int amt)
{
    if(model.GetMagePtr(mage_id) != 0)
    {
        if(model.GetMagePtr(mage_id)->IsBeingFollowed()==true)
        {
        cout << model.GetMagePtr(mage_id)->GetName() << " is attempting to use mana to bleed following Demon " << endl;
        model.GetMagePtr(mage_id)->setBleedCase(amt);
        }
        else
        {
            throw Invalid_Input("Current mage is not being followed!");
        }
    }
    else
    {
        throw Invalid_Input("Please enter valid Mage ID.");
    }
}

void DoFreeCommand(Model& model, int mage_id, int amt)
{
    if(model.GetMagePtr(mage_id) != 0)
    {
        if(model.GetMagePtr(mage_id)->IsCursed()==true)
        {
        cout << model.GetMagePtr(mage_id)->GetName() << " is attempting to use mana to bleed following Ancient Demon" << endl;
        model.GetMagePtr(mage_id)->setFreeCase(amt);
        }
        else
        {
            throw Invalid_Input("Current mage is not being followed!");
        }
    }
    else
    {
        throw Invalid_Input("Please enter valid Mage ID.");
    }
}

void masterConsole(istream& in, Model& model, View& view)
{
    //key parameters
    char command;
    string filename;

    char type;
    int id;
    int id1;
    int id2;
    int x;
    int y;
    int bleedInt;
    unsigned int cry_amt;
    unsigned int bat_amt;

    cout << "Enter command parameter: " << endl;
    in >> command;

    try{
        switch(command)
        {
            case 'm':
                //cout << "Enter ID x y" << endl;
                if(!(in >> id >> x >> y))
                {
                    throw Invalid_Input("Integers for ID and coordinates (x,y) were expected.");
                }
                DoMoveCommand(model ,id, Point2D(x,y));
                break;
            case 's':
                //cout << "Enter ID1 ID2" << endl;
                if(!(in >> id1 >> id2))
                {
                    throw Invalid_Input("Integers for ID1 and ID2 were expected.");
                }
                DoMoveToSpireCommand(model, id1, id2);
                break;
            case 'd':
                //cout << "Enter ID1 ID2" << endl;
                if(!(in >> id1 >> id2))
                {
                    throw Invalid_Input("Integers for ID1 and ID2 were expected.");
                }
                DoMoveToHideoutCommand(model, id1, id2);
                break;
            case 'h':
                //cout << "Enter ID" << endl;
                if(!(in >> id))
                {
                    throw Invalid_Input("Integer for ID was expected.");
                }
                DoStopCommand(model, id);
                break;
            case 'c':
                //cout << "Enter ID cry_amt" << endl;
                if(!(in >> id >> cry_amt))
                {
                    throw Invalid_Input("Integer for ID and crystal amount were expected.");
                }
                DoRecoverInSpireCommand(model, id, cry_amt);
                break;
            case 'b':
                //cout << "Enter ID bat_amt" << endl;
                if(!(in >> id >> bat_amt))
                {
                    throw Invalid_Input("Integer for ID and battle amount were expected.");
                }
                DoBattleCommand(model, id, bat_amt);
                break;
            case 'w':
                if(!(in >> id >> bleedInt))
                {
                    throw Invalid_Input("Integer for bleed intensity expected.");
                }
                DoBleedCommand(model, id, bleedInt);

                model.ShowStatus();
                model.Display(view);
                break;
            case 'x':
                if(!(in >> id >> bleedInt))
                {
                    throw Invalid_Input("Integer for free intensity expected.");
                }
                DoFreeCommand(model, id, bleedInt);

                model.ShowStatus();
                model.Display(view);
                break;
            case 'n':
                if(!(in >> type >> id >> x >> y))
                {
                    throw Invalid_Input("Character for type, integer for id, and coordinates (x,y) were expected.");
                }
                model.NewCommand(type, id, x, y);
                model.ShowStatus();
                model.Display(view);
                break;
            case 'a':
                DoAdvanceCommand(model, view);
                break;
            case 'r':
                DoRunCommand(model, view);
                break;
            case 'q':
                cout << "Terminating process.. ";
                cout << "-stopped" << endl;
                exit(0); //exit--terminates program, no break needed
            case 'S':
            {
                in >> filename;

                if(filename.length() > 99)
                {
                    throw Invalid_Input("File name exceeds 99 characters.");
                }
                ofstream outFile(filename);
                if (!outFile.is_open()) 
                {
                    throw Invalid_Input("ERROR: Could not open file to save.");
                }
                model.save(outFile);
                outFile.close();

                cout << "Game data successfully saved to " << filename << endl;
                break;
            }
            case 'R':
            {
                in >> filename;
                ifstream inFile(filename);

                if(!inFile.is_open())
                {
                    throw Invalid_Input("File does not exist/not found.");
                }
                model.restore(inFile);
                inFile.close();

                cout << "Game data successfully restored via " << filename << endl;

                model.ShowStatus();
                model.Display(view);
                break;
            }
                
            default: //default case
                throw Invalid_Input("Invalid Command!");
        }
    }
    catch(Invalid_Input& except) //fallback
    {
        cout << "ERROR: Invalid Input - " << except.msg_ptr << endl;
        in.clear();
        in.ignore(256, '\n');
    }
}