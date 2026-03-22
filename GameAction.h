#pragma once
#include "PetParameters.h"
#include <string>
#include <map>

class GameAction {
private:
    std::string actionName;
    std::map<std::string, int> effect;

public:
    GameAction(std::string name);
    void execute(PetParameters& params);
};