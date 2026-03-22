#pragma once
#include "PetBase.h"
#include "PetState.h"
#include <memory>
#include <string>

class VirtualPet : public PetBase {
protected:  
    PetParameters parameters;
    PetState state;
    int xp = 0;
    int level = 1;

public:
    VirtualPet();
    VirtualPet(std::string name, std::string type, int age);

    void update() override;
    void showStatus() const override;
    void specialAbility() override;
    std::unique_ptr<PetBase> clone() const override;

    PetParameters& getParameters() override { return parameters; }
    const PetParameters& getParameters() const override { return parameters; }

    PetState getState() const;
    int getXP() const { return xp; }
    void addXP(int amount) override; 
    void levelUp() override;
};