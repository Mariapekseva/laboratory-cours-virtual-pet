#pragma once
#include <vector>
#include <string>

struct Achievement {
    std::string name;
    std::string description;
    bool unlocked = false;
};

class AchievementSystem {
private:
    std::vector<Achievement> achievements;

public:
    AchievementSystem();
    void checkAchievements(int level, int interactions);
    void displayAchievements() const;
};