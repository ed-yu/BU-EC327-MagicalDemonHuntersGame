#include <iostream>
#include "Model.h"
#include "GameCommand.h"
#include <ctime>
#include <cstdlib>

using namespace std;

int main() {
    unsigned int randomSeed = static_cast<unsigned int>(time(nullptr));
    srand(randomSeed);

    Model game_model;
    View view;

    game_model.ShowStatus();
    game_model.Display(view);
    
    while (true) {
        masterConsole(cin, game_model, view);
        
        //game_model.ShowStatus(); 
    }

    return 0;
}