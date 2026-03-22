#include <iostream>
#include <memory>
#include <vector>
#include <fstream>
#include <algorithm>
#include <type_traits>
#include <iomanip>
#include <cstdlib>
#include <locale>

#include "PetBase.h"
#include "VirtualPet.h"
#include "MagicalPet.h"
#include "FoxPet.h"
#include "DragonPet.h"
#include "GameAction.h"
#include "QuizGame.h"
#include "TicTacToeGame.h"
#include "SaveSystem.h"
#include "ProgressTracker.h"
#include "AchievementSystem.h"
#include "PetContainer.h"
#include "RandomEvent.h"

template<typename T, typename Container>
T computeAverage(const Container& values) {
    static_assert(std::is_arithmetic_v<typename Container::value_type>,
        "Ошибка: контейнер должен содержать числовые значения");
    if (values.empty()) return T{ 0 };
    T sum = T{ 0 };
    for (const auto& v : values) {
        sum += static_cast<T>(v);
    }
    return sum / static_cast<T>(values.size());
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void analyzePetGroup() {
    std::vector<std::unique_ptr<PetBase>> group;
    group.push_back(std::make_unique<VirtualPet>("Барсик", "Кот", 5));
    group.push_back(std::make_unique<FoxPet>("Юйху", "Девятихвостый лис", 8));
    group.push_back(std::make_unique<DragonPet>("Игнас", "Дракон", 5));
    group.push_back(std::make_unique<VirtualPet>("Бобик", "Собака", 3));

    for (auto& pet : group) {
        pet->getParameters().setMood(70 + (rand() % 30));
    }

    std::sort(group.begin(), group.end(),
        [](const auto& a, const auto& b) { return a->getAge() < b->getAge(); });

    std::cout << "\n********************************************************\n";
    std::cout << "*                   ГРУППА ПИТОМЦЕВ                    *\n";
    std::cout << "********************************************************\n";
    std::cout << "Питомцы (по возрасту):\n";
    for (const auto& pet : group) {
        std::cout << "  - " << pet->getName() << " (" << pet->getAge() << " дней)\n";
    }

    auto magicalIt = std::find_if(group.begin(), group.end(),
        [](const auto& p) { return dynamic_cast<MagicalPet*>(p.get()) != nullptr; });
    if (magicalIt != group.end()) {
        std::cout << "\nПервый магический питомец: " << (*magicalIt)->getName() << "\n";
    }

    std::vector<int> moods;
    for (const auto& pet : group) {
        moods.push_back(pet->getParameters().getMood());
    }
    double avgMood = computeAverage<double>(moods);
    std::cout << "Среднее настроение: " << avgMood << "\n";

    bool hasLowMood = std::any_of(group.begin(), group.end(),
        [](const auto& p) { return p->getParameters().getMood() < 65; });
    std::cout << "Есть грустные питомцы? " << (hasLowMood ? "Да" : "Нет") << "\n";
    std::cout << "********************************************************\n";
}

int main() {
    std::locale::global(std::locale(""));
#ifdef _WIN32
    system("chcp 65001 > nul");
#endif

    SaveSystem saveSystem;
    ProgressTracker tracker;
    AchievementSystem achievements;
    RandomEvent randomEvents;

    std::unique_ptr<PetBase> pet = nullptr;
    bool isAsleep = false;
    int gamesWon = 0;

    bool hasSavedPet = false;
    if (std::ifstream("save.txt").good()) {
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
        std::cout << "********************************************************\n";
        std::cout << "*             ОБНАРУЖЕН СОХРАНЁННЫЙ ПИТОМЕЦ           *\n";
        std::cout << "********************************************************\n";
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
        std::cout << "********************************************************\n";
        std::cout << "*                  ВЫБЕРИТЕ ПИТОМЦА                   *\n";
        std::cout << "********************************************************\n";
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
        std::cout << "\nПитомец создан!\n";
        std::cin.get();
    }

    while (pet != nullptr) {
        clearScreen();
        pet->getParameters().updateOverTime();
        pet->update();
        pet->showStatus();

        if (isAsleep) {
            std::cout << "\n1. Проснуться\n";
            std::cout << "2. Сохранить\n";
            std::cout << "3. Достижения\n";
            std::cout << "4. Выход\n";
        }
        else {
            std::cout << "\n1. Покормить\n";
            std::cout << "2. Полечить\n";
            std::cout << "3. Уложить спать\n";
            std::cout << "4. Анализ группы питомцев\n";
            std::cout << "5. Поиграть (Викторина)\n";
            std::cout << "6. Поиграть (Крестики-нолики)\n";
            std::cout << "7. Использовать спецспособность\n";
            std::cout << "8. Сохранить\n";
            std::cout << "9. Достижения\n";
            std::cout << "10. Просмотр прогресса\n";
            std::cout << "11. Журнал событий\n";
            std::cout << "12. Выход\n";
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
                    tracker.updateXP(vPet->getXP());
                }
                std::cout << "\nПитомец покормлен!\n";
                randomEvents.trigger(*pet);
            }
            else if (action == 2) {
                pet->getParameters().setHealth(100);
                pet->getParameters().setMood(pet->getParameters().getMood() + 10);
                std::cout << "\nПитомец вылечен! Здоровье: 100%\n";
                tracker.trackInteraction();
            }
            else if (action == 3) {
                isAsleep = true;
                std::cout << "\nПитомец засыпает...\n";
            }
            else if (action == 4) {
                analyzePetGroup();
            }
            else if (action == 5) {
                QuizGame game({ {"mood", 15}, {"fatigue", 10} });
                bool won = game.play(*pet);
                if (won) gamesWon++;
                tracker.trackGame(won);
                pet->update();
                tracker.trackInteraction();
                if (auto* vPet = dynamic_cast<VirtualPet*>(pet.get())) {
                    vPet->addXP(15);
                    tracker.updateXP(vPet->getXP());
                }
            }
            else if (action == 6) {
                TicTacToeGame game({ {"mood", 20} });
                bool won = game.play(*pet);
                if (won) gamesWon++;
                tracker.trackGame(won);
                pet->update();
                tracker.trackInteraction();
                if (auto* vPet = dynamic_cast<VirtualPet*>(pet.get())) {
                    vPet->addXP(15);
                    tracker.updateXP(vPet->getXP());
                }
            }
            else if (action == 7) {
                pet->specialAbility();
                tracker.trackInteraction();
                achievements.unlockAchievement("Маг");
            }
            else if (action == 8) {
                saveSystem.saveGame(*pet);
                std::cout << "\nСохранено!\n";
            }
            else if (action == 9) {
                achievements.displayAchievements();
            }
            else if (action == 10) {
                if (auto* vPet = dynamic_cast<VirtualPet*>(pet.get())) {
                    tracker.updateXP(vPet->getXP());
                    tracker.updateLevel(vPet->getXP() / 100);
                }
                tracker.displayProgress();
            }
            else if (action == 11) {
                randomEvents.showEventLog();
            }
            else if (action == 12) break;
        }

        // Обновление достижений
        if (action != 8 && action != 4) {
            if (auto* vPet = dynamic_cast<VirtualPet*>(pet.get())) {
                achievements.checkAchievements(vPet->getXP() / 100, tracker.getInteractionCount(), gamesWon);
            }
        }

        // Пауза перед возвратом в меню (кроме выхода)
        if (action != 8 && action != 12) {
            std::cout << "\nНажмите Enter для продолжения...";
            std::cin.get();
        }
    }

    if (pet) {
        saveSystem.saveGame(*pet);
    }
    std::cout << "\nДо свидания! Ваш питомец ждёт вас!\n";
    return 0;
}