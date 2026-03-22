#pragma once
#include <string>
#include <vector>

class PetState {
private:
    std::string stateName = "Активное";
    std::string description = "Питомец бодр и готов к взаимодействию";
    std::vector<std::string> availableActions = { "Покормить", "Поиграть", "Положить спать" };

public:
    void determineState(int hunger, int fatigue, int health);
    std::string getVisualization() const;
    std::vector<std::string> getAvailableActions() const;
};