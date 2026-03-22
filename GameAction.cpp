#include "GameAction.h"

GameAction::GameAction(std::string name) : actionName(name) {
    if (name == "Покормить") {
        effect["hunger"] = -20;
        effect["mood"] = 10;
    }
    else if (name == "Уложить спать") {
        effect["fatigue"] = -50;
        effect["health"] = 10;
    }
    else if (name == "Поиграть") {
        effect["mood"] = 15;
        effect["fatigue"] = 10;
    }
}

void GameAction::execute(PetParameters& params) {
    params.setHunger(params.getHunger() + effect["hunger"]);
    params.setFatigue(params.getFatigue() + effect["fatigue"]);
    params.setHealth(params.getHealth() + effect["health"]);
    params.setMood(params.getMood() + effect["mood"]);
}