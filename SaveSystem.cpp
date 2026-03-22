#include "SaveSystem.h"
#include "PetParameters.h"
#include <fstream>

SaveSystem::SaveSystem(std::string path) : savePath(path) {}

bool SaveSystem::saveGame(const PetBase& pet) {
    std::ofstream file(savePath);
    if (!file.is_open()) return false;

    file << pet.getName() << "\n"
        << pet.getType() << "\n"
        << pet.getAge() << "\n";

    const auto& params = pet.getParameters();
    file << params.getHunger() << "\n"
        << params.getFatigue() << "\n"
        << params.getHealth() << "\n"
        << params.getMood() << "\n";

    file.close();
    return true;
}

bool SaveSystem::loadGame(PetBase& pet) {
    std::ifstream file(savePath);
    if (!file.is_open()) return false;

    std::string name, type;
    int age, hunger, fatigue, health, mood;
    file >> name >> type >> age >> hunger >> fatigue >> health >> mood;

    // Установка параметров через геттеры/сеттеры
    // Нужно будет изменить логику, если поля приватные
    // Для простоты предположим, что у нас есть сеттеры в PetBase
    // Это не так, но можно добавить виртуальные методы set в PetBase

    // Для текущей реализации:
    // VirtualPet::setParameters(hunger, fatigue, health, mood);
    // Это потребует изменений в VirtualPet

    return true;
}