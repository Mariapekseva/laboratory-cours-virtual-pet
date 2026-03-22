#include "AchievementSystem.h"
#include <iostream>

AchievementSystem::AchievementSystem() {
    achievements = {
        {"Новичок", "Начать игру", "Создайте первого питомца", false},
        {"Любящий хозяин", "Покормить 10 раз", "10 взаимодействий", false},
        {"Игрок", "Выиграть 5 игр", "5 побед в мини-играх", false},
        {"Эксперт C++", "Ответить на 10 вопросов", "Викторина C++", false},
        {"Маг", "Использовать спецспособность", "Магический питомец", false},
        {"Долгожитель", "Питомец достиг 10 уровня", "Level 10+", false},
        {"Перфекционист", "Все параметры 100%", "Максимальные статы", false},
        {"Коллекционер", "Создать 5 питомцев", "5 разных питомцев", false}
    };
}

void AchievementSystem::unlockAchievement(const std::string& name) {
    for (auto& ach : achievements) {
        if (ach.name == name && !ach.unlocked) {
            ach.unlocked = true;
            std::cout << "\n************************************************\n";
            std::cout << "* ДОСТИЖЕНИЕ РАЗБЛОКИРОВАНО: " << ach.name << "          *\n";
            std::cout << "************************************************\n";
            std::cout << "* " << ach.description << "                      *\n";
            std::cout << "************************************************\n";
        }
    }
}

void AchievementSystem::checkAchievements(int level, int interactions, int gamesWon) {
    if (interactions >= 10) unlockAchievement("Любящий хозяин");
    if (gamesWon >= 5) unlockAchievement("Игрок");
    if (level >= 10) unlockAchievement("Долгожитель");
}

void AchievementSystem::displayAchievements() const {
    std::cout << "\n************************************************\n";
    std::cout << "*                 ДОСТИЖЕНИЯ                    *\n";
    std::cout << "************************************************\n";

    int unlocked = 0;
    for (const auto& ach : achievements) {
        std::cout << "* " << (ach.unlocked ? "[*]" : "[ ]") << " " << ach.name << "\n";
        std::cout << "*     " << ach.description << "\n";
        std::cout << "*     Требование: " << ach.requirement << "\n";
        std::cout << "*--------------------------------------------*\n";
        if (ach.unlocked) unlocked++;
    }

    std::cout << "* Прогресс: " << unlocked << "/" << achievements.size() << "                          *\n";
    std::cout << "************************************************\n";
}