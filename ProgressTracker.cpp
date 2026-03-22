#include "ProgressTracker.h"

ProgressTracker::ProgressTracker()
    : totalInteractions(0), totalGamesPlayed(0), totalGamesWon(0),
    totalXP(0), highestLevel(1) {
}

void ProgressTracker::trackInteraction() {
    totalInteractions++;
}

void ProgressTracker::trackGame(bool won) {
    totalGamesPlayed++;
    if (won) totalGamesWon++;
}

void ProgressTracker::updateXP(int xp) {
    totalXP = xp;
}

void ProgressTracker::updateLevel(int level) {
    if (level > highestLevel) highestLevel = level;
}

void ProgressTracker::displayProgress() const {
    std::cout << "\n";
    std::cout << "********************************************************\n";
    std::cout << "*                 ПРОГРЕСС ИГРОКА                      *\n";
    std::cout << "********************************************************\n";
    std::cout << "*  Всего взаимодействий: " << std::setw(5) << totalInteractions << "                 *\n";
    std::cout << "*  Сыграно игр:          " << std::setw(5) << totalGamesPlayed << "                 *\n";
    std::cout << "*  Выиграно игр:         " << std::setw(5) << totalGamesWon << "                 *\n";
    std::cout << "*  Всего опыта:          " << std::setw(5) << totalXP << "                 *\n";
    std::cout << "*  Максимальный уровень: " << std::setw(5) << highestLevel << "                 *\n";

    if (totalGamesPlayed > 0) {
        int winRate = (totalGamesWon * 100) / totalGamesPlayed;
        std::cout << "*  Процент побед:        " << std::setw(5) << winRate << "%                 *\n";
    }

    std::cout << "********************************************************\n";
}

void ProgressTracker::reset() {
    totalInteractions = 0;
    totalGamesPlayed = 0;
    totalGamesWon = 0;
    totalXP = 0;
    highestLevel = 1;
}