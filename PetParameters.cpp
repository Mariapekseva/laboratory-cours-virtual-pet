#include "PetParameters.h"
#include <map>
#include <string>

// Конструктор по умолчанию: задаёт начальные значения параметров
PetParameters::PetParameters()
    : hunger(50)
    , fatigue(50)
    , health(100)
    , mood(50)
{
}

// Конструктор с параметрами: устанавливает значения с проверкой через сеттеры
PetParameters::PetParameters(int hunger, int fatigue, int health, int mood)
    : hunger(hunger)
    , fatigue(fatigue)
    , health(health)
    , mood(mood)
{
    // Используем сеттеры для валидации
    setHunger(hunger);
    setFatigue(fatigue);
    setHealth(health);
    setMood(mood);
}

// Деструктор
PetParameters::~PetParameters() = default;

// Обновляет параметры со временем: питомец голодает и устаёт
void PetParameters::updateOverTime()
{
    hunger += 10;
    fatigue += 5;
    if (hunger > 75)
        health -= 5;
    if (fatigue > 70)
        mood -= 10;
}

// Проверяет, находится ли питомец в критическом состоянии (здоровье ≤ 20)
bool PetParameters::checkCriticalLevels()
{
    return health <= 20;
}

// Возвращает все параметры в виде словаря
std::map<std::string, int> PetParameters::getParameters()
{
    return {
        {"hunger", hunger},
        {"fatigue", fatigue},
        {"health", health},
        {"mood", mood}
    };
}

// Геттеры: возвращают текущие значения параметров
int PetParameters::getHunger() const { return hunger; }
int PetParameters::getFatigue() const { return fatigue; }
int PetParameters::getHealth() const { return health; }
int PetParameters::getMood() const { return mood; }

// Сеттеры: устанавливают значения с ограничением от 0 до 100
void PetParameters::setHunger(int hunger)
{
    this->hunger = (hunger < 0) ? 0 : (hunger > 100 ? 100 : hunger);
}

void PetParameters::setFatigue(int fatigue)
{
    this->fatigue = (fatigue < 0) ? 0 : (fatigue > 100 ? 100 : fatigue);
}

void PetParameters::setHealth(int health)
{
    this->health = (health < 0) ? 0 : (health > 100 ? 100 : health);
}

void PetParameters::setMood(int mood)
{
    this->mood = (mood < 0) ? 0 : (mood > 100 ? 100 : mood);
}
