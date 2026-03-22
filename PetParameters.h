#pragma once
#include <map>
#include <string>

class PetParameters {
private:
    int hunger = 50;
    int fatigue = 0;
    int health = 100;
    int mood = 70;

public:
    // Геттеры
    int getHunger() const;
    int getFatigue() const;
    int getHealth() const;
    int getMood() const;
    int getEnergy() const;  // Новый метод

    // Сеттеры
    void setHunger(int v);
    void setFatigue(int v);
    void setHealth(int v);
    void setMood(int v);

    // Обновление и проверки
    void updateOverTime();
    bool checkCriticalLevels() const;

    // Для совместимости
    std::map<std::string, int> getParameters() const;
};