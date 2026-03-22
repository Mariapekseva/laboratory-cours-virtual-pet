#include "VirtualPet.h"
#include <iostream>

VirtualPet::VirtualPet() : PetBase("Барсик", "Кот", 0) {
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
    std::cout << "\n====================================\n";
    std::cout << "          СТАТУС ПИТОМЦА            \n";
    std::cout << "====================================\n";
    std::cout << "Имя:        " << name << "\n";
    std::cout << "Тип:        " << type << "\n";
    std::cout << "Возраст:    " << age << " дней\n";
    std::cout << "Уровень:    " << level << "\n";
    std::cout << "Состояние:  " << state.getVisualization() << "\n";
    std::cout << "\nПараметры:\n";
    std::cout << "Голод:      " << parameters.getHunger() << "%\n";
    std::cout << "Усталость:  " << parameters.getFatigue() << "%\n";
    std::cout << "Здоровье:   " << parameters.getHealth() << "%\n";
    std::cout << "Настроение: " << parameters.getMood() << "%\n";
    std::cout << "====================================\n";
}

void VirtualPet::specialAbility() {
    std::cout << name << " мурлычет от удовольствия!\n";
}

std::unique_ptr<PetBase> VirtualPet::clone() const {
    auto copy = std::make_unique<VirtualPet>(name, type, age);
    copy->parameters = this->parameters;
    copy->xp = xp;
    copy->level = level;
    copy->state = state;
    return copy;
}

void VirtualPet::addXP(int amount) {
    xp += amount;
    if (xp >= level * 100) {
        levelUp();
    }
}

void VirtualPet::levelUp() {
    level++;
    std::cout << name << " достиг " << level << " уровня!\n";
    parameters.setHealth(100);
}

PetState VirtualPet::getState() const { return state; }