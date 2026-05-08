#ifndef GAMECOMMAND_H
#define GAMECOMMAND_H

#include <iostream>
#include "View.h"
#include "Point2D.h"

using namespace std;

class Model;

//function prototypes
void DoMoveCommand(Model& model, int mage_id, Point2D p1);
void DoMoveToSpireCommand(Model& model, int mage_id, int spire_id);
void DoMoveToHideoutCommand(Model& model, int mage_id, int hideout_id);
void DoStopCommand(Model& model, int mage_id);
void DoBattleCommand(Model& model, int mage_id, unsigned int battles);
void DoRecoverInSpireCommand(Model& model, int mage_id, unsigned int crystals_needed);
void DoAdvanceCommand(Model& model, View& view);
void DoRunCommand(Model& model, View& view);
void DoBleedCommand(Model& model, int mage_id, int amt);
void DoFreeCommand(Model& model, int mage_id, int amt);
void masterConsole(istream& in, Model& model, View& view);


#endif