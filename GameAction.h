#pragma once
#include <string>
#include <map>
#include <vector>
#include "PetParameters.h"
#include "PetState.h"

// Простые действия: покормить, поиграть и т.д.
class GameAction
{
public:
    GameAction();
    GameAction(std::string actionName); // Создаёт действие по названию
    ~GameAction();

    void execute(PetParameters& params); // Применяет действие к питомцу
    std::map<std::string, int> calculateEffects(); // Возвращает эффект
    bool isAvailable(PetState state); // Проверяет, можно ли выполнить сейчас

    std::string getActionName() const;
    std::map<std::string, int> getEffect() const;

private:
    std::string actionName;        // Название действия
    std::map<std::string, int> effect; // Как меняются параметры
};
