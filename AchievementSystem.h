#pragma once
#include <vector>
#include <string>

struct Achievement {
    std::string name;
    std::string description;
    std::string requirement;
    bool unlocked;
};

class AchievementSystem {
private:
    std::vector<Achievement> achievements;

public:
    AchievementSystem();
    void checkAchievements(int level, int interactions, int gamesWon);
    void displayAchievements() const;
    void unlockAchievement(const std::string& name);
};