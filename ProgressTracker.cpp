#include "ProgressTracker.h"

void ProgressTracker::trackInteraction() {
    interactionCount++;
    xpGained += 5;
}

void ProgressTracker::addXP(int amount) {
    xpGained += amount;
}