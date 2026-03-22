#pragma once
#include "MagicalPet.h"
#include <string>

class DragonPet : public MagicalPet {
public:
    DragonPet(std::string name, std::string type, int age);

    void specialAbility() override;
    void levelUp() override;

private:
    int fireBreathUses = 3;
    bool ancientPowerUnlocked = false;
};