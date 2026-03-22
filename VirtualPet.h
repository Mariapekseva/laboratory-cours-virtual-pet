#pragma once
#include "PetBase.h"
#include "PetParameters.h"
#include "PetState.h"
#include <memory>

class VirtualPet : public PetBase {
public:
    VirtualPet();
    VirtualPet(std::string name, std::string type, int age);

    void update() override;
    void showStatus() const override;
    void specialAbility() override;
    std::unique_ptr<PetBase> clone() const override;
    PetParameters& getParameters() override;
    const PetParameters& getParameters() const override;

    int getXP() const { return xp; }
    void addXP(int amount);
    void levelUp();

    PetState getState() const;

private:
    std::unique_ptr<PetParameters> parameters = std::make_unique<PetParameters>();
    PetState state;
    int xp = 0;
    int level = 1;
};