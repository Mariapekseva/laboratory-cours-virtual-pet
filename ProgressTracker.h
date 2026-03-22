#pragma once
#include <string>
#include <iostream>
#include <iomanip>

class ProgressTracker {
private:
    int totalInteractions;
    int totalGamesPlayed;
    int totalGamesWon;
    int totalXP;
    int highestLevel;

public:
    ProgressTracker();

    void trackInteraction();
    void trackGame(bool won);
    void updateXP(int xp);
    void updateLevel(int level);

    void displayProgress() const;
    void reset();

    int getInteractionCount() const { return totalInteractions; }
    int getGamesWon() const { return totalGamesWon; }
};