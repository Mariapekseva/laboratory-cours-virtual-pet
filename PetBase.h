#pragma once
#include "PetParameters.h"
#include <string>
#include <memory>

class PetBase {
protected:
    std::string name;
    std::string type;
    int age;
    PetParameters parameters;

public:
    PetBase(std::string name, std::string type, int age)
        : name(name), type(type), age(age) {
    }

    virtual ~PetBase() = default;

    // Геттеры
    std::string getName() const { return name; }
    std::string getType() const { return type; }
    int getAge() const { return age; }

    // возвращаем ссылку, чтобы можно было менять параметры
    virtual PetParameters& getParameters() { return parameters; }
    virtual const PetParameters& getParameters() const { return parameters; }

    // Сеттеры
    void setName(const std::string& newName) { name = newName; }
    void setType(const std::string& newType) { type = newType; }
    void setAge(int newAge) { age = newAge; }

    virtual void addXP(int amount) {}

    //  Виртуальные методы
    virtual void showStatus() const = 0;      
    virtual void update() = 0;                 
    virtual std::unique_ptr<PetBase> clone() const = 0; 

    virtual void levelUp() {}                
    virtual void specialAbility() {}           
};