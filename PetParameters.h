#pragma once
#include <map>
#include <string>

// Хранит внутренние параметры питомца
class PetParameters
{
public:
    PetParameters(); // Стандартные значения
    PetParameters(int hunger, int fatigue, int health, int mood);
    ~PetParameters();

    void updateOverTime();     // Параметры меняются со временем
    bool checkCriticalLevels(); // Проверяет, в опасности ли питомец
    std::map<std::string, int> getParameters(); // Возвращает все параметры

    // Геттеры и сеттеры
    int getHunger() const;
    int getFatigue() const;
    int getHealth() const;
    int getMood() const;

    void setHunger(int hunger);
    void setFatigue(int fatigue);
    void setHealth(int health);
    void setMood(int mood);

private:
    int hunger;    // Голод (0–100)
    int fatigue;   // Усталость (0–100)
    int health;    // Здоровье (0–100)
    int mood;      // Настроение (0–100)
};
