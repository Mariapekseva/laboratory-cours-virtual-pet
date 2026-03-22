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
    std::cout << getName() << " сотворил " << magicType << "-иллюзию!\n";
}

std::unique_ptr<PetBase> MagicalPet::clone() const {
    auto copy = std::make_unique<MagicalPet>(getName(), getType(), getAge(), magicType);
    copy->getParameters() = getParameters();
    copy->addXP(0); // чтобы не сбросился XP
    return copy;
}