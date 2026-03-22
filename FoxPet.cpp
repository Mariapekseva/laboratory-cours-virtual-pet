#include "FoxPet.h"
#include <iostream>

FoxPet::FoxPet(std::string name, std::string type, int age)
    : MagicalPet(name, type, age, "Иллюзия") {
}

void FoxPet::specialAbility() {
    if (illusionUses > 0) {
        std::cout << getName() << " создаёт ИЛЛЮЗИЮ!\n";
        std::cout << "   Враги запутались, можно убежать!\n";
        illusionUses--;
        std::cout << "   Осталось использований: " << illusionUses << "\n";
    }
    else {
        std::cout << getName() << " слишком устал для иллюзий.\n";
    }
}

void FoxPet::levelUp() {
    VirtualPet::levelUp();  // Вызываем базовый метод

    // ИСПРАВЛЕНО: используем геттер вместо прямого доступа
    int currentLevel = getXP() / 100;
    if (currentLevel >= 3) {
        illusionUses = 3;
        std::cout << getName() << " восстановил иллюзии!\n";
    }
}