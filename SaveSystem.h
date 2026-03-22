#pragma once
#include "PetBase.h"
#include <string>

class SaveSystem {
private:
    std::string savePath;

public:
    SaveSystem(std::string path);
    bool saveGame(const PetBase& pet);
    bool loadGame(PetBase& pet);
};