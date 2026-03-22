#include <iostream>
#include <memory>
#include <vector>
#include <fstream>
#include <algorithm>
#include <type_traits>

#include "PetBase.h"
#include "VirtualPet.h"
#include "MagicalPet.h"
#include "FoxPet.h"
#include "DragonPet.h"
#include "PetContainer.h"
#include "GameAction.h"
#include "QuizGame.h"
#include "TicTacToeGame.h"
#include "SaveSystem.h"
#include "ProgressTracker.h"
#include "AchievementSystem.h"

template<typename T, typename Container>
T computeAverage(const Container& values) {
    static_assert(std::is_arithmetic_v<typename Container::value_type>, "Ошибка: контейнер должен содержать числовые значения(int, float и т.д.)");
    if (values.empty()) return T{ 0 };
    T sum = T{ 0 };
    for (const auto& v : values) {
        sum += static_cast<T>(v);
    }
    return sum / static_cast<T>(values.size());
}

void clearScreen() {
    system("cls");
}

void analyzePetGroup() {
    std::vector<std::unique_ptr<PetBase>> group;
    group.push_back(std::make_unique<VirtualPet>("Барсик", "Кот", 5));
    group.push_back(std::make_unique<FoxPet>("Юйху", 8));
    group.push_back(std::make_unique<DragonPet>("Игнас", 5));
    group.push_back(std::make_unique<VirtualPet>("Бобик", "Собака", 3));

    for (auto& pet : group) {
        pet->getParameters().setMood(70 + (rand() % 30));
    }

    std::sort(group.begin(), group.end(), [](const auto& a, const auto& b) {
        return a->getAge() < b->getAge();
        });

    std::cout << "\n=== Группа питомцев ===\n";
    for (const auto& pet : group) {
        std::cout << "- " << pet->getName() << " (" << pet->getAge() << " дней)\n";
    }

    auto magicalIt = std::find_if(group.begin(), group.end(), [](const auto& p) {
        return dynamic_cast<MagicalPet*>(p.get()) != nullptr;
        });

    if (magicalIt != group.end()) {
        std::cout << "\nПервый магический питомец: " << (*magicalIt)->getName() << "\n";
    }

    std::vector<int> moods;
    for (const auto& pet : group) {
        moods.push_back(pet->getParameters().getMood());
    }

    double avgMood = computeAverage<double>(moods);
    std::cout << "Среднее настроение: " << avgMood << "\n";

    bool hasLowMood = std::any_of(group.begin(), group.end(), [](const auto& p) {
        return p->getParameters().getMood() < 65;
        });
    std::cout << "Есть грустные питомцы? " << (hasLowMood ? "Да" : "Нет") << "\n";

    PetContainer<MagicalPet> magicalGroup;
    magicalGroup.add(std::make_unique<FoxPet>("Феникс", "Птица", 1000));
    magicalGroup.sortByAge();
    std::cout << "\nМагическая группа отсортирована по возрасту.\n";
    std::cout << "=============================\n";
}

int main() {
    setlocale(LC_ALL, "Russian");
    system("chcp 65001> nul");

    SaveSystem saveSystem("save.txt");
    ProgressTracker tracker;
    AchievementSystem achievements;

    std::unique_ptr<PetBase> pet = nullptr;
    bool isAsleep = false;

    bool hasSavedPet = false;
    if (std::ifstream("save.txt").good()) {
        // Проверка типа сохранённого питомца и создание соответствующего объекта
        // Это требует более сложной логики в SaveSystem
        // Пока предположим, что всегда VirtualPet
        pet = std::make_unique<VirtualPet>("Загрузка", "Кот", 0);
        if (saveSystem.loadGame(*pet)) {
            hasSavedPet = true;
        }
        else {
            pet = nullptr;
        }
    }

    if (hasSavedPet) {
        clearScreen();
        std::cout << "*** Обнаружен сохранённый питомец ***\n";
        std::cout << "Имя: " << pet->getName() << "\n";
        std::cout << "Тип: " << pet->getType() << "\n";
        std::cout << "Возраст: " << pet->getAge() << " дней\n";
        std::cout << "\n1. Продолжить с этим питомцем\n";
        std::cout << "2. Создать нового\n";
        std::cout << "Ваш выбор: ";
        int choice;
        std::cin >> choice;
        std::cin.ignore();
        if (choice != 1) {
            hasSavedPet = false;
            pet = nullptr;
        }
    }

    if (!hasSavedPet) {
        clearScreen();
        std::cout << "*** Выберите питомца ***\n";
        std::cout << "1. Кот\n2. Собака\n3. Хомяк\n4. Дракон\n5. Девятихвостый лис\n";
        std::cout << "Ваш выбор: ";
        int choice;
        std::cin >> choice;
        std::cin.ignore();
        std::string type;
        switch (choice) {
        case 1: type = "Кот"; break;
        case 2: type = "Собака"; break;
        case 3: type = "Хомяк"; break;
        case 4: type = "Дракон"; break;
        case 5: type = "Девятихвостый лис"; break;
        default: type = "Кот";
        }

        std::cout << "Имя: ";
        std::string name;
        std::getline(std::cin, name);

        if (type == "Дракон" || type == "Девятихвостый лис") {
            if (type == "Дракон") {
                pet = std::make_unique<DragonPet>(name, type, 0);
            }
            else {
                pet = std::make_unique<FoxPet>(name, type, 0);
            }
        }
        else {
            pet = std::make_unique<VirtualPet>(name, type, 0);
        }

        pet->getParameters().setHunger(50);
        pet->getParameters().setFatigue(0);
        pet->getParameters().setHealth(100);
        pet->getParameters().setMood(70);
        pet->update();
        saveSystem.saveGame(*pet);
        std::cout << "\nПитомец \"" << name << "\" создан!\n";
        std::cin.get();
    }

    while (pet != nullptr) {
        clearScreen();
        pet->getParameters().updateOverTime();
        pet->update();
        pet->showStatus();

        if (isAsleep) {
            std::cout << "\n1. Проснуться\n2. Сохранить\n3. Достижения\n4. Выход\n";
        }
        else {
            std::cout << "\n1. Покормить\n2. Уложить спать\n";
            std::cout << "3. Анализ группы питомцев\n";
            std::cout << "4. Поиграть (Викторина)\n";
            std::cout << "5. Поиграть (Крестики-нолики)\n";
            std::cout << "6. Сохранить\n";
            std::cout << "7. Достижения\n";
            std::cout << "8. Выход\n";
        }

        std::cout << "Выбор: ";
        int action;
        std::cin >> action;
        std::cin.ignore();

        if (isAsleep) {
            if (action == 1) {
                isAsleep = false;
                std::cout << "\nПитомец проснулся!\n";
            }
            else if (action == 2) {
                saveSystem.saveGame(*pet);
                std::cout << "\nСохранено!\n";
            }
            else if (action == 3) {
                achievements.displayAchievements();
            }
            else if (action == 4) break;
        }
        else {
            if (action == 1) {
                GameAction feed("Покормить");
                feed.execute(pet->getParameters());
                pet->update();
                tracker.trackInteraction();
                if (auto* vPet = dynamic_cast<VirtualPet*>(pet.get())) {
                    vPet->addXP(10);
                }
                std::cout << "\nПитомец покормлен!\n";
            }
            else if (action == 2) {
                isAsleep = true;
                std::cout << "\nПитомец засыпает...\n";
            }
            else if (action == 3) {
                analyzePetGroup();
                std::cout << "\nНажмите Enter...";
                std::cin.get();
            }
            else if (action == 4) {
                QuizGame game({ {"mood", 15}, {"fatigue", 10} });
                game.startGame();
                game.applyEffects(pet->getParameters());
                pet->update();
                tracker.trackInteraction();
                if (auto* vPet = dynamic_cast<VirtualPet*>(pet.get())) {
                    vPet->addXP(15);
                }
                std::cout << "\nИгра окончена!\n";
            }
            else if (action == 5) {
                TicTacToeGame game({ {"mood", 20} });
                game.startGame();
                game.applyEffects(pet->getParameters());
                pet->update();
                tracker.trackInteraction();
                if (auto* vPet = dynamic_cast<VirtualPet*>(pet.get())) {
                    vPet->addXP(15);
                }
            }
            else if (action == 6) {
                saveSystem.saveGame(*pet);
                std::cout << "\nСохранено!\n";
            }
            else if (action == 7) {
                achievements.displayAchievements();
                std::cout << "\nНажмите Enter...";
                std::cin.get();
            }
            else if (action == 8) break;
        }

        if (action != 3 && action != 7) {
            std::cout << "\nНажмите Enter...";
            std::cin.get();
        }

        // Проверка достижений
        if (auto* vPet = dynamic_cast<VirtualPet*>(pet.get())) {
            achievements.checkAchievements(vPet->getXP() / 100, tracker.getInteractionCount());
        }
    }

    if (pet) {
        saveSystem.saveGame(*pet);
    }
    std::cout << "\nДо свидания! Ваш питомец ждёт вас!\n";
    return 0;
}