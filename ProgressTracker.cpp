#include "ProgressTracker.h"
#include <string>
#include <sstream>

// Конструктор по умолчанию: инициализирует все счётчики нулями
ProgressTracker::ProgressTracker()
    : petLifetime(0)
    , interactionCount(0)
    , totalPlayTime(0)
    , parameterBalance(0.0)
{
}

// Деструктор
ProgressTracker::~ProgressTracker() = default;

// Обновляет статистику по питомцу
void ProgressTracker::updateStats(int petLifetime, int interactionCount, int totalPlayTime, double parameterBalance)
{
    this->petLifetime = petLifetime;
    this->interactionCount = interactionCount;
    this->totalPlayTime = totalPlayTime;
    this->parameterBalance = parameterBalance;
}

// Генерирует текстовый отчёт о прогрессе
std::string ProgressTracker::generateReport()
{
    std::ostringstream report;
    report << "\n=== Отчёт о прогрессе ===\n";
    report << "Время жизни питомца: " << petLifetime << " дней\n";
    report << "Количество взаимодействий: " << interactionCount << "\n";
    report << "Общее время игры: " << totalPlayTime << " минут\n";
    report << "Средний баланс параметров: " << parameterBalance << "%\n";
    report << "========================\n";
    return report.str();
}

// Увеличивает счётчик взаимодействий на 1
void ProgressTracker::trackInteraction()
{
    interactionCount++;
}

// Геттеры: возвращают текущие значения статистики
int ProgressTracker::getPetLifetime() const { return petLifetime; }
int ProgressTracker::getInteractionCount() const { return interactionCount; }
int ProgressTracker::getTotalPlayTime() const { return totalPlayTime; }
double ProgressTracker::getParameterBalance() const { return parameterBalance; }

