#pragma once
#include <string>
#include <map>
#include "PetParameters.h"

// Мини-игра (викторина)
class MiniGame
{
public:
    MiniGame(); // Стандартная викторина
    MiniGame(std::string gameName, int difficulty, std::map<std::string, int> rewards);
    ~MiniGame();

    void startGame();      // Запускает игру
    void calculateRewards(); // Вычисляет награды (уже заданы)
    void applyEffects(PetParameters& params); // Применяет награды

    std::string getGameName() const;
    int getDifficulty() const;
    std::map<std::string, int> getRewards() const;

private:
    std::string gameName;        // Название игры
    int difficulty;              // Уровень сложности
    std::map<std::string, int> rewards; // Награды (например, +15 настроения)
};
