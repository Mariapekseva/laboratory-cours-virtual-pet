#include "GameAction.h"
#include <map>
#include <string>
#include <algorithm>

// Конструктор по умолчанию: создаёт действие без эффекта
GameAction::GameAction()
    : actionName("Неизвестное действие")
{
    effect["hunger"] = 0;
    effect["fatigue"] = 0;
    effect["health"] = 0;
    effect["mood"] = 0;
}

// Конструктор с названием действия: задаёт эффекты в зависимости от типа действия
GameAction::GameAction(std::string actionName)
    : actionName(actionName)
{
    if (actionName == "Покормить") {
        effect["hunger"] = -20;  // уменьшаем голод
        effect["mood"] = +10;    // улучшаем настроение
        effect["fatigue"] = 0;
        effect["health"] = 0;
    }
    else if (actionName == "Уложить спать") {
        effect["fatigue"] = -100; // полностью снимаем усталость
        effect["health"] = +15;   // улучшаем здоровье
        effect["hunger"] = 0;
        effect["mood"] = 0;
    }
    else if (actionName == "Поиграть") {
        effect["mood"] = +15;     // улучшаем настроение
        effect["fatigue"] = +10;  // добавляем усталость
        effect["hunger"] = 0;
        effect["health"] = 0;
    }
    else {
        // Для неизвестных действий — нулевой эффект
        effect["hunger"] = 0;
        effect["fatigue"] = 0;
        effect["health"] = 0;
        effect["mood"] = 0;
    }
}

// Деструктор
GameAction::~GameAction() = default;

// Применяет действие к параметрам питомца
void GameAction::execute(PetParameters& params)
{
    params.setHunger(params.getHunger() + effect["hunger"]);
    params.setFatigue(params.getFatigue() + effect["fatigue"]);
    params.setHealth(params.getHealth() + effect["health"]);
    params.setMood(params.getMood() + effect["mood"]);
}

// Возвращает эффект действия в виде словаря
std::map<std::string, int> GameAction::calculateEffects()
{
    return effect;
}

// Проверяет, доступно ли действие в текущем состоянии питомца
bool GameAction::isAvailable(PetState state)
{
    std::vector<std::string> actions = state.getAvailableActions();
    return std::find(actions.begin(), actions.end(), actionName) != actions.end();
}

// Возвращает название действия
std::string GameAction::getActionName() const
{
    return actionName;
}

// Возвращает эффект действия (изменения параметров)
std::map<std::string, int> GameAction::getEffect() const
{
    return effect;
}
