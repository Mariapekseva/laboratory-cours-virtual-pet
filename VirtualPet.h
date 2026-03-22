#pragma once
#include "PetBase.h"
#include "PetParameters.h"
#include "PetState.h"
#include <string>
#include <memory>

class VirtualPet : public PetBase {
public:
    VirtualPet();
    VirtualPet(std::string name, std::string type, int age);

    VirtualPet(const VirtualPet&) = delete;
    VirtualPet& operator=(const VirtualPet&) = delete;

    // Реализация виртуальных методов
    void update() override;
    void showStatus() const override;
    void specialAbility() override;
    std::unique_ptr<PetBase> clone() const override;

    PetParameters& getParameters() override;
    const PetParameters& getParameters() const override;

    
    PetState getState() const;

private:
    PetParameters parameters;
    PetState state;
};