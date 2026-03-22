#include "AchievementSystem.h"
#include <iostream>

AchievementSystem::AchievementSystem() {
    achievements = {
        {"Первый шаг", "Достичь 1 уровня", false},
        {"Малыш", "Достичь 5 уровня", false},
        {"Зоолог", "Создать 5 питомцев", false},
        {"Маг", "Создать магического питомца 10 уровня", false}
    };
}

void AchievementSystem::checkAchievements(int level, int interactions) {
    if (level >= 1 && !achievements[0].unlocked) {
        achievements[0].unlocked = true;
        std::cout << "Достижение разблокировано: " << achievements[0].name << "!\n";
    }
    if (level >= 5 && !achievements[1].unlocked) {
        achievements[1].unlocked = true;
        std::cout << "Достижение разблокировано: " << achievements[1].name << "!\n";
    }
    if (interactions >= 10 && !achievements[2].unlocked) {
        achievements[2].unlocked = true;
        std::cout << "Достижение разблокировано: " << achievements[2].name << "!\n";
    }
}

void AchievementSystem::displayAchievements() const {
    std::cout << "\n=== Достижения ===\n";
    for (const auto& a : achievements) {
        std::cout << (a.unlocked ? "[✓] " : "[ ] ") << a.name << " — " << a.description << "\n";
    }
}