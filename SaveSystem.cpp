#include "SaveSystem.h"
#include <iostream>

bool SaveSystem::saveGame(const PetBase& pet) {
    std::ofstream file(savePath);
    if (!file.is_open()) return false;

    file << pet.getName() << "\n"
        << pet.getType() << "\n"
        << pet.getAge() << "\n";

    const auto& params = pet.getParameters();
    file << params.getHunger() << "\n"
        << params.getFatigue() << "\n"
        << params.getHealth() << "\n"
        << params.getMood() << "\n";

    file.close();
    return true;
}

bool SaveSystem::loadGame(PetBase& pet) {
    std::ifstream file(savePath);
    if (!file.is_open()) return false;

    std::string name, type;
    int age, hunger, fatigue, health, mood;

    if (!(file >> name >> type >> age >> hunger >> fatigue >> health >> mood)) {
        return false;
    }

    pet.setName(name);
    pet.setType(type);
    pet.setAge(age);

    auto& p = pet.getParameters();
    p.setHunger(hunger);
    p.setFatigue(fatigue);
    p.setHealth(health);
    p.setMood(mood);

    pet.update();

    return true;
}