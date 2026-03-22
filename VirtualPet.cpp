#include "VirtualPet.h"
#include <iostream>

VirtualPet::VirtualPet()
    : PetBase("Name", "Кот", 0) {
    update();
}

VirtualPet::VirtualPet(std::string name, std::string type, int age)
    : PetBase(name, type, age) {
    update();
}

void VirtualPet::update() {
    state.determineState(
        parameters.getHunger(),
        parameters.getFatigue(),
        parameters.getHealth()
    );
}

void VirtualPet::showStatus() const {
    std::cout << "\n=== Статус ===\n";
    std::cout << "Имя: " << name << "\n";
    std::cout << "Тип: " << type << "\n";
    std::cout << "Возраст: " << age << " дней\n";
    std::cout << "Состояние: " << state.getVisualization() << "\n";
    std::cout << "Параметры:\n";
    std::cout << "  Голод: " << parameters.getHunger() << "%\n";
    std::cout << "  Усталость: " << parameters.getFatigue() << "%\n";
    std::cout << "  Здоровье: " << parameters.getHealth() << "%\n";
    std::cout << "  Настроение: " << parameters.getMood() << "%\n";
    std::cout << "==============\n";
}

void VirtualPet::specialAbility() {
    std::cout << name << " мурлычет от удовольствия!\n";
}

std::unique_ptr<PetBase> VirtualPet::clone() const {
    auto copy = std::make_unique<VirtualPet>(name, type, age);
    copy->parameters = parameters;
    copy->state = state;
    return copy;
}

PetParameters& VirtualPet::getParameters() {
    return parameters;
}

const PetParameters& VirtualPet::getParameters() const {
    return parameters;
}

PetState VirtualPet::getState() const {
    return state;
}