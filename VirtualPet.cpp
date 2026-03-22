#include "VirtualPet.h"
#include <iostream>
#include <iostream>

VirtualPet::VirtualPet() : PetBase("Барсик", "Кот", 0) {
    update();
}

VirtualPet::VirtualPet(std::string name, std::string type, int age) : PetBase(name, type, age) {
    update();
}

void VirtualPet::update() {
    state.determineState(
        parameters->getHunger(),
        parameters->getFatigue(),
        parameters->getHealth()
    );
}

void VirtualPet::showStatus() const {
    std::cout << "\n╔══════════════════════════════════════╗\n";
    std::cout << "║           Статус питомца             ║\n";
    std::cout << "╠══════════════════════════════════════╣\n";
    std::cout << "║ Имя: " << std::setw(30) << std::left << name << " ║\n";
    std::cout << "║ Тип: " << std::setw(30) << std::left << type << " ║\n";
    std::cout << "║ Возраст: " << std::setw(26) << std::to_string(age) + " дней" << " ║\n";
    std::cout << "║ Уровень: " << std::setw(27) << std::to_string(level) << " ║\n";
    std::cout << "║ Состояние: " << std::setw(24) << state.getVisualization() << " ║\n";
    std::cout << "╠──────────────────────────────────────╣\n";

    auto drawBar = [](int value) {
        const int width = 20;
        int filled = value / 5;
        std::cout << "[";
        for (int i = 0; i < width; ++i) {
            if (i < filled) std::cout << "█";
            else std::cout << "░";
        }
        std::cout << "] " << value << "%\n";
        };

    std::cout << "║ Голод:   ";
    drawBar(parameters->getHunger());
    std::cout << "║ Усталость: ";
    drawBar(parameters->getFatigue());
    std::cout << "║ Здоровье: ";
    drawBar(parameters->getHealth());
    std::cout << "║ Настроение: ";
    drawBar(parameters->getMood());
    std::cout << "╚══════════════════════════════════════╝\n";
}

void VirtualPet::specialAbility() {
    std::cout << name << " мурлычет от удовольствия!\n";
}

std::unique_ptr<PetBase> VirtualPet::clone() const {
    auto copy = std::make_unique<VirtualPet>(name, type, age);
    copy->parameters = std::make_unique<PetParameters>(*parameters);
    copy->xp = xp;
    copy->level = level;
    return copy;
}

PetParameters& VirtualPet::getParameters() { return *parameters; }
const PetParameters& VirtualPet::getParameters() const { return *parameters; }

PetState VirtualPet::getState() const { return state; }

void VirtualPet::addXP(int amount) {
    xp += amount;
    if (xp >= level * 100) {
        levelUp();
    }
}

void VirtualPet::levelUp() {
    level++;
    std::cout << name << " достиг " << level << " уровня!\n";
    // Способности по уровням реализуются в FoxPet и DragonPet
}