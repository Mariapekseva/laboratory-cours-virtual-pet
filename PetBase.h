#pragma once
#include <string>
#include <memory>
#include <iostream>


class PetParameters;

class PetBase {
public:
    PetBase(std::string name, std::string type, int age);
    virtual ~PetBase() = default; // Виртуальный деструктор 

    // Чисто виртуальные методы — делают класс абстрактным
    virtual void update() = 0;
    virtual void showStatus() const = 0;
    virtual void specialAbility() = 0;
    virtual std::unique_ptr<PetBase> clone() const = 0;

    // Виртуальные геттеры параметров
    virtual PetParameters& getParameters() = 0;
    virtual const PetParameters& getParameters() const = 0;

    // Обычные геттеры (не виртуальные)
    std::string getName() const { return name; }
    std::string getType() const { return type; }
    int getAge() const { return age; }

    // Пример: невиртуальная функция, вызывающая виртуальные
    void dailyRoutine() {
        std::cout << "\n[Суточный цикл]\n";
        update();            // виртуальный вызов
        specialAbility();    //  виртуальный вызов
    }

protected:
    std::string name;
    std::string type;
    int age;
};