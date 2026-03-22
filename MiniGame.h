#pragma once
#include "PetParameters.h"
#include <string>
#include <map>

class MiniGame {
public:
    virtual void startGame() = 0;
    virtual void applyEffects(PetParameters& params) = 0;
};