#pragma once
#include <string>
#include <map>
#include "PetBase.h"

class MiniGame {
protected:
    std::string name;
    std::map<std::string, int> effects;

public:
    MiniGame(std::string n, std::map<std::string, int> e) : name(n), effects(e) {}
    virtual bool play(PetBase& pet) = 0;
    std::string getName() const { return name; }
};