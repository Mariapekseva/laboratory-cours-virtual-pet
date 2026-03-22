#include "MiniGame.h"
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

// Конструктор по умолчанию: создаёт стандартную викторину
MiniGame::MiniGame()
    : gameName("Викторина")
    , difficulty(1)
    , rewards({ {"mood", 15}, {"fatigue", 10} })
{
}

// Конструктор с параметрами: создаёт игру с заданным названием, сложностью и наградами
MiniGame::MiniGame(std::string gameName, int difficulty, std::map<std::string, int> rewards)
    : gameName(gameName)
    , difficulty(difficulty)
    , rewards(rewards)
{
}

// Деструктор
MiniGame::~MiniGame() = default;

// Запускает мини-игру (викторину) с вопросом и свободным вводом ответа
void MiniGame::startGame()
{
    std::cout << "\n=== " << gameName << " ===\n";

    // Список вопросов и правильных ответов
    std::vector<std::pair<std::string, std::string>> questions = {
        {"Столица Франции?", "Париж"},
        {"2 + 2 = ?", "4"},
        {"Какой цвет у неба?", "Голубой"},
        {"Самая большая планета?", "Юпитер"}
    };

    // Выбираем случайный вопрос
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    auto question = questions[std::rand() % questions.size()];

    // Задаём вопрос и ждём ответ
    std::cout << question.first << "\nВаш ответ: ";
    std::string answer;
    std::getline(std::cin, answer);

    // Проверяем ответ
    if (answer == question.second) {
        std::cout << "Правильно! \n";
    }
    else {
        std::cout << "Неверно. Правильный ответ: " << question.second << "\n";
    }
}

// Вычисляет награды (в текущей версии они заданы при создании объекта)
void MiniGame::calculateRewards()
{
    // Награды уже заданы в конструкторе — дополнительных вычислений нет
}

// Применяет награды к параметрам питомца (например, +15 к настроению)
void MiniGame::applyEffects(PetParameters& params)
{
    for (const auto& reward : rewards) {
        std::string param = reward.first;
        int value = reward.second;

        if (param == "hunger") {
            params.setHunger(params.getHunger() + value);
        }
        else if (param == "fatigue") {
            params.setFatigue(params.getFatigue() + value);
        }
        else if (param == "health") {
            params.setHealth(params.getHealth() + value);
        }
        else if (param == "mood") {
            params.setMood(params.getMood() + value);
        }
    }
}

// Геттеры: возвращают данные об игре
std::string MiniGame::getGameName() const { return gameName; }
int MiniGame::getDifficulty() const { return difficulty; }
std::map<std::string, int> MiniGame::getRewards() const { return rewards; }

