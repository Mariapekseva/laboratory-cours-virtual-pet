#include "QuizGame.h"
#include <iostream>
#include <random>
#include <algorithm>
#include <iomanip>

QuizGame::QuizGame(std::map<std::string, int> e)
    : MiniGame("Викторина", e), difficulty(5), correctAnswers(0) {
    loadQuestions();
}

void QuizGame::loadQuestions() {
    allQuestions.push_back({
        "Кто сказал: Ребята, давайте жить дружно!",
        {"Волк", "Лиса", "Кот Леопольд", "Матроскин"},
        2, "мультики"
        });
    allQuestions.push_back({
        "Как звали кота из Простоквашино?",
        {"Барсик", "Матроскин", "Мурзик", "Феликс"},
        1, "мультики"
        });
    allQuestions.push_back({
        "Кто такой Чебурашка?",
        {"Обезьяна", "Неизвестный зверь", "Медведь", "Енот"},
        1, "мультики"
        });
    allQuestions.push_back({
        "Какого цвета был Волк из Ну погоди?",
        {"Серый", "Белый", "Чёрный", "Рыжий"},
        0, "мультики"
        });
    allQuestions.push_back({
        "Кто жил в Изумрудном городе с Элли?",
        {"Тотошка", "Бим", "Бобик", "Шарик"},
        0, "мультики"
        });
    allQuestions.push_back({
        "Что такое std::vector?",
        {"Массив", "Динамический массив", "Список", "Очередь"},
        1, "cpp"
        });
    allQuestions.push_back({
        "Какой оператор для доступа через указатель?",
        {".", "->", "::", "*"},
        1, "cpp"
        });
    allQuestions.push_back({
        "Что возвращает main() при успехе?",
        {"0", "1", "-1", "nullptr"},
        0, "cpp"
        });
    allQuestions.push_back({
        "Как объявить константу в C++?",
        {"const", "final", "static", "define"},
        0, "cpp"
        });
    allQuestions.push_back({
        "Что такое unique_ptr?",
        {"Умный указатель", "Обычный указатель", "Массив", "Функция"},
        0, "cpp"
        });
}

void QuizGame::selectQuestions() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(allQuestions.begin(), allQuestions.end(), g);

    questions.clear();
    int count = std::min(difficulty, (int)allQuestions.size());
    for (int i = 0; i < count; i++) {
        questions.push_back(allQuestions[i]);
    }
}

bool QuizGame::play(PetBase& pet) {
    std::cout << "\n";
    std::cout << "********************************************************\n";
    std::cout << "*                    ВИКТОРИНА                         *\n";
    std::cout << "********************************************************\n";
    std::cout << "Выберите сложность:\n";
    std::cout << "  1. Легкая (3 вопроса)\n";
    std::cout << "  2. Средняя (5 вопросов)\n";
    std::cout << "  3. Сложная (7 вопросов)\n";
    std::cout << "Ваш выбор: ";

    int diffChoice;
    std::cin >> diffChoice;
    difficulty = (diffChoice == 1) ? 3 : (diffChoice == 3) ? 7 : 5;

    selectQuestions();
    correctAnswers = 0;

    std::cout << "\nНачинаем! Отвечайте цифрой (1-4)\n";

    for (size_t i = 0; i < questions.size(); ++i) {
        const auto& q = questions[i];
        std::cout << "\n--------------------------------------------------------\n";
        std::cout << "[" << (q.category == "cpp" ? "C++" : "Мультфильмы") << "] ";
        std::cout << "Вопрос " << (i + 1) << "/" << questions.size() << "\n";
        std::cout << "--------------------------------------------------------\n";
        std::cout << q.text << "\n\n";

        for (size_t j = 0; j < q.options.size(); ++j) {
            std::cout << "  " << (j + 1) << ". " << q.options[j] << "\n";
        }

        int answer;
        std::cout << "\nВаш ответ: ";
        std::cin >> answer;
        if (answer == q.correct + 1) {
            correctAnswers++;
            std::cout << "Правильно!\n";
        }
        else {
            std::cout << "Неправильно! Правильный ответ: " << (q.correct + 1) << "\n";
        }
    }

    bool win = (correctAnswers >= questions.size() / 2);

    // ПОКАЗАТЬ РЕЗУЛЬТАТЫ
    std::cout << "\n";
    std::cout << "********************************************************\n";
    std::cout << "*                   РЕЗУЛЬТАТЫ                         *\n";
    std::cout << "********************************************************\n";
    std::cout << "*  Правильных ответов: " << std::setw(3) << correctAnswers << " из " << questions.size() << "              *\n";
    std::cout << "*  Процент успеха:     " << std::setw(3) << (correctAnswers * 100 / questions.size()) << "%                      *\n";
    std::cout << "*  " << (win ? "ПОБЕДА!" : "Попробуйте еще раз") << "                              *\n";
    std::cout << "********************************************************\n";

    int moodBonus = (correctAnswers * 10);
    pet.getParameters().setMood(pet.getParameters().getMood() + moodBonus);
    pet.getParameters().setFatigue(pet.getParameters().getFatigue() + 5);

    // ПАУЗА
    std::cout << "\nНажмите Enter для продолжения...";
    std::cin.ignore(10000, '\n');
    std::cin.get();

    return win;
}

void QuizGame::showResults() const {
    std::cout << "\nСтатистика викторины: " << correctAnswers << " правильных ответов\n";
}