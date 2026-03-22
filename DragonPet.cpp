#include "DragonPet.h"
#include <iostream>

DragonPet::DragonPet(std::string name, std::string type, int age)
    : MagicalPet(name, type, age, "ќгонь") {
}

void DragonPet::specialAbility() {
    std::cout << getName() << " извергает огонь: 'PPP-ќ√Ќ№!'\n";
}

void DragonPet::levelUp() {
    MagicalPet::levelUp();
    int newLevel = getXP() / 100;
    if (newLevel == 3) {
        std::cout << getName() << " получил способность 'ќгненное дыхание'!\n";
    }
    else if (newLevel == 5) {
        std::cout << getName() << " получил способность 'ƒраконь€ брон€'!\n";
        armorActive = true;
    }
    else if (newLevel == 10 && !ancientRageUsed) {
        std::cout << getName() << " получил способность 'ƒревн€€ €рость'!\n";
        getParameters().setHealth(getParameters().getHealth() + 50);
        getParameters().setMood(getParameters().getMood() + 50);
        ancientRageUsed = true;
    }
}