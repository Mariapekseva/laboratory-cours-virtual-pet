#include "PetParameters.h"

void PetParameters::updateOverTime() {
    hunger += 10;
    fatigue += 5;
    if (hunger > 75) health -= 5;
    if (fatigue > 70) mood -= 10;
}

bool PetParameters::checkCriticalLevels() const {
    return health <= 20;
}

std::map<std::string, int> PetParameters::getParameters() const {
    return { {"hunger", hunger}, {"fatigue", fatigue}, {"health", health}, {"mood", mood} };
}

int PetParameters::getHunger() const { return hunger; }
int PetParameters::getFatigue() const { return fatigue; }
int PetParameters::getHealth() const { return health; }
int PetParameters::getMood() const { return mood; }

void PetParameters::setHunger(int value) {
    hunger = (value < 0) ? 0 : (value > 100 ? 100 : value);
}
void PetParameters::setFatigue(int value) {
    fatigue = (value < 0) ? 0 : (value > 100 ? 100 : value);
}
void PetParameters::setHealth(int value) {
    health = (value < 0) ? 0 : (value > 100 ? 100 : value);
}
void PetParameters::setMood(int value) {
    mood = (value < 0) ? 0 : (value > 100 ? 100 : value);
}