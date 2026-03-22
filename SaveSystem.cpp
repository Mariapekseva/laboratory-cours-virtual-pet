#include "SaveSystem.h"
#include "VirtualPet.h"
#include "PetBase.h"
#include <fstream>
#include <string>


SaveSystem::SaveSystem()
    : savePath("save.txt")
    , isAutoSaveEnabled(false)
{
}

SaveSystem::SaveSystem(std::string savePath, bool autoSave)
    : savePath(savePath)
    , isAutoSaveEnabled(autoSave)
{
}

SaveSystem::~SaveSystem() = default;

// ЕДИНСТВЕННАЯ реализация — для PetBase
bool SaveSystem::saveGame(const PetBase& pet)
{
    std::ofstream file(savePath);
    if (!file.is_open())
        return false;

    file << pet.getName() << "\n";
    file << pet.getType() << "\n";
    file << pet.getAge() << "\n";
    file << pet.getParameters().getHunger() << "\n";
    file << pet.getParameters().getFatigue() << "\n";
    file << pet.getParameters().getHealth() << "\n";
    file << pet.getParameters().getMood();

    file.close();
    return true;
}

bool SaveSystem::loadGame(PetBase& pet)
{
    std::ifstream file(savePath);
    if (!file.is_open())
        return false;

    std::string name, type;
    int age, hunger, fatigue, health, mood;
    std::getline(file, name);
    std::getline(file, type);
    file >> age >> hunger >> fatigue >> health >> mood;
    file.close();

    if (age < 0 || hunger < 0 || hunger > 100 ||
        fatigue < 0 || fatigue > 100 ||
        health < 0 || health > 100 ||
        mood < 0 || mood > 100) {
        return false;
    }

    pet.getParameters().setHunger(hunger);
    pet.getParameters().setFatigue(fatigue);
    pet.getParameters().setHealth(health);
    pet.getParameters().setMood(mood);
    pet.update();

    return true;
}

void SaveSystem::autoSave(const PetBase& pet)
{
    if (isAutoSaveEnabled)
    {
        saveGame(pet);
    }
}

std::string SaveSystem::getSavePath() const
{
    return savePath;
}

bool SaveSystem::getAutoSave() const
{
    return isAutoSaveEnabled;
}
