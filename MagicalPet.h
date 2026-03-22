#pragma once
#include "VirtualPet.h"
#include <string>

class MagicalPet : public VirtualPet {
public:
    MagicalPet(std::string name, std::string type, int age, std::string magicType);

    
    void showStatus() const override;

    
    void specialAbility() override;

    std::unique_ptr<PetBase> clone() const override;

    std::string getMagicType() const { return magicType; }

private:
    std::string magicType;
};