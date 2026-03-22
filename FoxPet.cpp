#include "FoxPet.h"
#include <iostream>

FoxPet::FoxPet(std::string name, std::string type, int age)
    : MagicalPet(name, type, age, "Иллюзии") {
}

void FoxPet::specialAbility() {
    std::cout << getName() << " создаёт иллюзию — вы получаете +25 к настроению!\n";
    getParameters().setMood(getParameters().getMood() + 25);
    update();
}

void FoxPet::levelUp() {
    MagicalPet::levelUp();
    int newLevel = getXP() / 100;
    if (newLevel == 3) {
        std::cout << getName() << " получил способность 'Иллюзия'!\n";
        illusionUses = 1;
    }
    else if (newLevel == 5) {
        std::cout << getName() << " получил способность 'Танец луны'!\n";
        getParameters().setHealth(getParameters().getHealth() + 20);
        getParameters().setMood(getParameters().getMood() + 20);
    }
    else if (newLevel == 10 && !eternalLifeUsed) {
        std::cout << getName() << " получил способность 'Вечная жизнь'!\n";
        eternalLifeUsed = true;
    }
}