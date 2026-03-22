#pragma once

class ProgressTracker {
private:
    int interactionCount = 0;
    int xpGained = 0;

public:
    void trackInteraction();
    void addXP(int amount);

    int getInteractionCount() const { return interactionCount; }
    int getXPGained() const { return xpGained; }
};