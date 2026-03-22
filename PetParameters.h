#pragma once
#include <map>
#include <string>

class PetParameters {
private:
    int hunger = 50;
    int fatigue = 50;
    int health = 100;
    int mood = 50;

public:
    void updateOverTime();
    bool checkCriticalLevels() const;
    std::map<std::string, int> getParameters() const;

    int getHunger() const;
    int getFatigue() const;
    int getHealth() const;
    int getMood() const;

    void setHunger(int value);
    void setFatigue(int value);
    void setHealth(int value);
    void setMood(int value);
};