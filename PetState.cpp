#include "PetState.h"

void PetState::determineState(int hunger, int fatigue, int health) {
    if (health <= 20) {
        stateName = "Критическое";
        description = "Питомец в опасности! Требуется срочная помощь.";
        availableActions = { "Вылечить" };
    }
    else if (hunger > 75) {
        stateName = "Голодное";
        description = "Питомец голоден и просит еду.";
        availableActions = { "Покормить" };
    }
    else if (fatigue > 70) {
        stateName = "Уставшее";
        description = "Питомец устал и хочет спать.";
        availableActions = { "Положить спать" };
    }
    else {
        stateName = "Активное";
        description = "Питомец бодр и готов к взаимодействию";
        availableActions = { "Покормить", "Поиграть", "Положить спать" };
    }
}

std::string PetState::getVisualization() const {
    return description;
}

std::vector<std::string> PetState::getAvailableActions() const {
    return availableActions;
}