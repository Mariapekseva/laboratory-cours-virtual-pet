#pragma once
#include <iostream>
#include <memory>
#include <string>

class PetParameters;

class PetBase {
public:
    PetBase(std::string name, std::string type, int age);
    virtual ~PetBase() = default;

    virtual void update() = 0;
    virtual void showStatus() const = 0;
    virtual void specialAbility() = 0;
    virtual std::unique_ptr<PetBase> clone() const = 0;
    virtual PetParameters& getParameters() = 0;
    virtual const PetParameters& getParameters() const = 0;

    std::string getName() const { return name; }
    std::string getType() const { return type; }
    int getAge() const { return age; }

    void dailyRoutine() {
        std::cout << "\n[Суточный цикл]\n";
        update();
        specialAbility();
    }

protected:
    std::string name;
    std::string type;
    int age;
};