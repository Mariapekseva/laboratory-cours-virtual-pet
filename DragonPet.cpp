#include "DragonPet.h"
#include <iostream>

DragonPet::DragonPet(std::string name, std::string type, int age)
    : MagicalPet(name, type, age, "Огонь") {
}

void DragonPet::specialAbility() {
    if (fireBreathUses > 0) {
        std::cout << getName() << " использует ОГНЕННОЕ ДЫХАНИЕ!\n";
        std::cout << "   Враги получают урон, настроение повышается!\n";
        fireBreathUses--;
        std::cout << "   Осталось использований: " << fireBreathUses << "\n";
    }
    else {
        std::cout << getName() << " слишком устал для огненного дыхания.\n";
        std::cout << "   Отдохните и попробуйте позже!\n";
    }
}

void DragonPet::levelUp() {
    VirtualPet::levelUp();  // Вызываем базовый метод

    // ИСПРАВЛЕНО: используем геттер вместо прямого доступа
    int currentLevel = getXP() / 100;
    if (currentLevel >= 5 && !ancientPowerUnlocked) {
        ancientPowerUnlocked = true;
        fireBreathUses = 5;
        std::cout << getName() << " получил ДРЕВНЮЮ СИЛУ!\n";
        std::cout << "   Огненное дыхание стало мощнее!\n";
    }
}