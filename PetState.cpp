#include "PetState.h"
#include <vector>
#include <string>
#include <iostream>

// Конструктор по умолчанию: устанавливает состояние "Активное"
PetState::PetState()
    : stateName("Активное")
    , description("Питомец бодр и готов к взаимодействию")
{
    availableActions = { "Покормить", "Поиграть", "Положить спать" };
}

// Деструктор

PetState::~PetState() = default;

// Определяет состояние питомца по его параметрам (голод, усталость, здоровье)
void PetState::determineState(int hunger, int fatigue, int health)
{
    if (health <= 20)
    {
        stateName = "Критическое";
        description = "Питомец в опасности! Требуется срочная помощь.";
        availableActions = { "Вылечить" };
    }
    else if (hunger > 75)
    {
        stateName = "Голодное";
        description = "Питомец голоден и просит еду.";
        availableActions = { "Покормить" };
    }
    else if (fatigue > 70)
    {
        stateName = "Уставшее";
        description = "Питомец устал и хочет спать.";
        availableActions = { "Положить спать" };
    }
    else
    {
        stateName = "Активное";
        description = "Питомец бодр и готов к взаимодействию";
        availableActions = { "Покормить", "Поиграть", "Положить спать" };
    }
}

// Возвращает описание состояния для вывода пользователю
std::string PetState::getVisualization() const
{
    return description;
}

// Проверяет, находится ли питомец не в обычном состоянии ("Активное")
bool PetState::checkStateChange()
{
    return stateName != "Активное";
}

// Возвращает название текущего состояния
std::string PetState::getStateName() const
{
    return stateName;
}

// Возвращает список действий, доступных в текущем состоянии
std::vector<std::string> PetState::getAvailableActions() const
{
    return availableActions;
}

