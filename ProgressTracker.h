#pragma once
#include <string>

// Следит за прогрессом: сколько дней живёт питомец, сколько раз взаимодействовали и т.д.
class ProgressTracker
{
public:
    ProgressTracker();
    ~ProgressTracker();

    void updateStats(int petLifetime, int interactionCount, int totalPlayTime, double parameterBalance);
    std::string generateReport(); // Создаёт отчёт
    void trackInteraction();      // Считает взаимодействия

    // Геттеры
    int getPetLifetime() const;
    int getInteractionCount() const;
    int getTotalPlayTime() const;
    double getParameterBalance() const;

private:
    int petLifetime;          // Сколько дней живёт питомец
    int interactionCount;     // Сколько раз игрок взаимодействовал
    int totalPlayTime;        // Общее время игры (минуты)
    double parameterBalance;  // Средний баланс параметров
};
