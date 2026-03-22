#pragma once
#include "PetBase.h"
#include "PetParameters.h"
#include <fstream>
#include <string>
#include <memory>

class SaveSystem {
private:
    std::string savePath;

public:
    SaveSystem(std::string path = "save.txt") : savePath(path) {}
    bool saveGame(const PetBase& pet);
    bool loadGame(PetBase& pet);
};