#include <iostream>
#include <memory>
#include <string>
#include <fstream>
#include <vector>        // ← для std::vector
#include <algorithm>     // ← для std::sort, std::find_if и др.
#include <type_traits>   // ← для static_assert (работает в C++17 и выше)

// Заголовки вашего проекта
#include "GameAction.hpp"
#include "MiniGame.hpp"
#include "VirtualPet.hpp"
#include "MagicalPet.hpp"
#include "SaveSystem.hpp"
#include "ProgressTracker.hpp"

// === ШАБЛОННАЯ ФУНКЦИЯ (вне main, вне класса) ===
// Вычисляет среднее арифметическое для контейнера с числовыми значениями
template<typename T, typename Container>
T computeAverage(const Container& values) {
    static_assert(std::is_arithmetic_v<typename Container::value_type>,
        "Контейнер должен содержать арифметические типы (int, float и т.д.)");
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

int main() {
    setlocale(LC_ALL, "Russian");
    system("chcp 65001 > nul");

    SaveSystem saveSystem;
    ProgressTracker tracker;
    std::unique_ptr<PetBase> pet = nullptr;
    bool isAsleep = false;

    {
        
        // Контейнер с объектами базового и производного классов
        std::vector<std::unique_ptr<PetBase>> demoZoo;
        demoZoo.push_back(std::make_unique<VirtualPet>("Барсик", "Кот", 5));
        demoZoo.push_back(std::make_unique<MagicalPet>("Хули", "Девятихвостый лис", 50, "Иллюзии"));
        demoZoo.push_back(std::make_unique<VirtualPet>("Бобик", "Собака", 3));
        demoZoo.push_back(std::make_unique<MagicalPet>("Дрогон", "Дракон", 200, "Огонь"));

        // Сортировка по возрасту (std::sort)
        std::sort(demoZoo.begin(), demoZoo.end(), [](const auto& a, const auto& b) {
            return a->getAge() < b->getAge();
            });
        std::cout << "Питомцы отсортированы по возрасту:\n";
        for (const auto& p : demoZoo) {
            std::cout << "- " << p->getName() << " (" << p->getAge() << " дней)\n";
        }

        // Поиск магического питомца (std::find_if)
        auto magicalIt = std::find_if(demoZoo.begin(), demoZoo.end(), [](const auto& pet) {
            return dynamic_cast<MagicalPet*>(pet.get()) != nullptr;
            });
        if (magicalIt != demoZoo.end()) {
            std::cout << "Первый магический питомец: " << (*magicalIt)->getName() << "\n";
        }

        std::vector<int> moods;
        for (const auto& p : demoZoo) {
            moods.push_back(p->getParameters().getMood());
        }

        // Вызов шаблонной функции
        double avgMood = computeAverage<double>(moods);
        std::cout << "Среднее настроение: " << avgMood << "\n";

        
        bool hasLowMood = std::any_of(demoZoo.begin(), demoZoo.end(), [](const auto& p) {
            return p->getParameters().getMood() < 60;
            });
        std::cout << "Есть питомцы с плохим настроением? " << (hasLowMood ? "Да" : "Нет") << "\n";

        std::cout << "==================================\n\n";
        std::cout << "Нажмите Enter, чтобы продолжить...";
        std::cin.get();
    }

   

    // Проверка существования файла сохранения
    bool hasSavedPet = false;
    if (std::ifstream("save.txt").good()) {
        pet = std::make_unique<VirtualPet>("Pip", "Кот", 0);
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
        std::cout << "2. Создать нового (старый будет удалён)\n";
        std::cout << "Ваш выбор: ";

        int choice;
        std::cin >> choice;
        std::cin.ignore();

        if (choice != 1) {
            hasSaved Pet = false;
            pet = nullptr;
        }
    }

    if (!hasSavedPet) {
        clearScreen();
        std::cout << "*** Выберите питомца ***\n";
        std::cout << "1. Кот\n";
        std::cout << "2. Собака\n";
        std::cout << "3. Хомяк\n";
        std::cout << "4. Дракон\n";
        std::cout << "5. Девятихвостый лис\n";
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

        std::cout << "Введите имя питомца: ";
        std::string name;
        std::getline(std::cin, name);

        if (type == "Дракон" || type == "Девятихвостый лис") {
            pet = std::make_unique<MagicalPet>(name, type, 0, "Древняя магия");
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
        std::cout << "\nПитомец \"" << name << "\" успешно создан!\n";
        std::cout << "Нажмите Enter...";
        std::cin.get();
    }

    // Основной игровой цикл
    while (pet != nullptr) {
        clearScreen();

        pet->getParameters().updateOverTime();
        pet->update();
        pet->showStatus();

        if (isAsleep) {
            std::cout << "\nПитомец спит.\n";
            std::cout << "1. Проснуться\n";
            std::cout << "2. Сохранить игру\n";
            std::cout << "3. Выход\n";
        }
        else {
            std::cout << "\n1. Покормить\n";
            std::cout << "2. Уложить спать\n";
            std::cout << "3. Проверить состояние\n";
            std::cout << "4. Поиграть (Викторина)\n";
            std::cout << "5. Сохранить игру\n";
            std::cout << "6. Выход\n";
        }

        std::cout << "Выбор: ";
        int action;
        std::cin >> action;
        std::cin.ignore();

        if (isAsleep) {
            if (action == 1) {
                isAsleep = false;
                std::cout << "\nПитомец проснулся и рад вас видеть!\n";
            }
            else if (action == 2) {
                saveSystem.saveGame(*pet);
                std::cout << "\nСохранено!\n";
            }
            else if (action == 3) {
                break;
            }
        }
        else {
            if (action == 1) {
                GameAction feed("Покормить");
                feed.execute(pet->getParameters());
                pet->update();
                tracker.trackInteraction();
                std::cout << "\nПитомец покормлен! Настроение улучшено.\n";
            }
            else if (action == 2) {
                isAsleep = true;
                std::cout << "\nПитомец засыпает...\n";
            }
            else if (action == 3) {
                // Состояние уже выведено
            }
            else if (action == 4) {
                MiniGame game("Угадай мультфильм!", 1, { {"mood", 15}, {"fatigue", 10} });
                game.startGame();
                game.applyEffects(pet->getParameters());
                pet->update();
                tracker.trackInteraction();
            }
            else if (action == 5) {
                saveSystem.saveGame(*pet);
                std::cout << "\nСохранено!\n";
            }
            else if (action == 6) {
                break;
            }
        }

        std::cout << "\nНажмите Enter...";
        std::cin.get();
    }

    if (pet) {
        saveSystem.saveGame(*pet);
    }
    std::cout << "\nДо свидания! Ваш питомец ждёт вас!\n";
    return 0;
}