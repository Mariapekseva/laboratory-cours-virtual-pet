#pragma once
#include <string>
#include <vector>

// Отвечает за состояние питомца (голодный, спит и т.д.)
class PetState
{
public:
    PetState(); // Состояние по умолчанию — "Активное"
    ~PetState();

    void determineState(int hunger, int fatigue, int health); // Определяет состояние
    std::string getVisualization() const; // Описание состояния
    bool checkStateChange(); // Проверяет, изменилось ли состояние
    std::string getStateName() const; // Название состояния
    std::vector<std::string> getAvailableActions() const; // Доступные действия

private:
    std::string stateName;         // Название (например, "Голодное")
    std::string description;       // Описание для пользователя
    std::vector<std::string> availableActions; // Что можно сделать
};

