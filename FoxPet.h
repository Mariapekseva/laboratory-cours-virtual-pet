#pragma once
#include "MagicalPet.h"
#include <string>

class FoxPet : public MagicalPet {
public:
    FoxPet(std::string name, std::string type, int age);

    void specialAbility() override;
    void levelUp() override;

private:
    int illusionUses = 3;
    bool eternalLifeUsed = false;
};