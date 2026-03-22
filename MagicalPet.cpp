#include "MagicalPet.h"
#include <iostream>

MagicalPet::MagicalPet(std::string name, std::string type, int age, std::string magicType)
    : VirtualPet(name, type, age), magicType(magicType) {
}

void MagicalPet::showStatus() const {
    
    VirtualPet::showStatus();
    std::cout << "[Магия: " << magicType << "]\n";
}

void MagicalPet::specialAbility() {
    
    std::cout << name << " сотворил " << magicType << "-иллюзию!\n";
}

std::unique_ptr<PetBase> MagicalPet::clone() const {
    auto copy = std::make_unique<MagicalPet>(name, type, age, magicType);
    copy->getParameters() = getParameters(); // копируем параметры
    return copy;
}