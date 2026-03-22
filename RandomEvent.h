#pragma once
#include "PetBase.h"
#include <string>
#include <vector>
#include <random>
#include <iostream>

struct GameEvent {
    std::string name;
    std::string description;
    int hungerChange;
    int fatigueChange;
    int healthChange;
    int moodChange;
    int xpChange;
};

class RandomEvent {
private:
    std::vector<GameEvent> events;
    int eventsTriggered;

public:
    RandomEvent();
    bool trigger(PetBase& pet);  
    void showEventLog() const;
};