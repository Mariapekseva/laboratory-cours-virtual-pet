#pragma once
#include "MagicalPet.h"
#include <string>

class DragonPet : public MagicalPet {
public:
    DragonPet(std::string name, std::string type, int age);

    void specialAbility() override;
    void levelUp() override;

private:
    bool armorActive = false;
    bool ancientRageUsed = false;
};