#include "PetParameters.h"

void PetParameters::updateOverTime() {
    // Увеличиваем параметры (с проверкой границ через сеттеры)
    setHunger(getHunger() + 5);      // Голод растёт медленнее
    setFatigue(getFatigue() + 3);    // Усталость растёт

    // Если голод высокий - здоровье падает
    if (getHunger() > 75) {
        setHealth(getHealth() - 3);
    }

    // Если усталость высокая - настроение падает
    if (getFatigue() > 70) {
        setMood(getMood() - 5);
    }

    // Если здоровье низкое - настроение тоже падает
    if (getHealth() < 30) {
        setMood(getMood() - 5);
    }
}

bool PetParameters::checkCriticalLevels() const {
    return health <= 20 || hunger >= 90 || fatigue >= 90;
}

// Сеттеры с ограничением 0-100
void PetParameters::setHunger(int v) {
    hunger = (v < 0) ? 0 : (v > 100 ? 100 : v);
}

void PetParameters::setFatigue(int v) {
    fatigue = (v < 0) ? 0 : (v > 100 ? 100 : v);
}

void PetParameters::setHealth(int v) {
    health = (v < 0) ? 0 : (v > 100 ? 100 : v);
}

void PetParameters::setMood(int v) {
    mood = (v < 0) ? 0 : (v > 100 ? 100 : v);
}

// Геттеры
int PetParameters::getHunger() const {
    return hunger;
}

int PetParameters::getFatigue() const {
    return fatigue;
}

int PetParameters::getHealth() const {
    return health;
}

int PetParameters::getMood() const {
    return mood;
}

// Для совместимости со старым кодом
std::map<std::string, int> PetParameters::getParameters() const {
    return {
        {"hunger", hunger},
        {"fatigue", fatigue},
        {"health", health},
        {"mood", mood}
    };
}

// Дополнительный метод для энергии (если нужен в VirtualPet)
int PetParameters::getEnergy() const {
    return 100 - fatigue;  // Энергия = 100 - усталость
}