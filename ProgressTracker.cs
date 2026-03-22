using System;
using System.Text;

public class ProgressTracker
{
    private int petLifetime;
    private int interactionCount;
    private int totalPlayTime;
    private double parameterBalance;

    public ProgressTracker()
    {
        petLifetime = 0;
        interactionCount = 0;
        totalPlayTime = 0;
        parameterBalance = 0.0;
    }

    public void UpdateStats(int petLifetime, int interactionCount, int totalPlayTime, double parameterBalance)
    {
        this.petLifetime = petLifetime;
        this.interactionCount = interactionCount;
        this.totalPlayTime = totalPlayTime;
        this.parameterBalance = parameterBalance;
    }

    public string GenerateReport()
    {
        var report = new StringBuilder();
        report.AppendLine("\n=== Отчёт о прогрессе ===");
        report.AppendLine($"Время жизни питомца: {petLifetime} дней");
        report.AppendLine($"Количество взаимодействий: {interactionCount}");
        report.AppendLine($"Общее время игры: {totalPlayTime} минут");
        report.AppendLine($"Средний баланс параметров: {parameterBalance:F1}%");
        report.AppendLine("========================");
        return report.ToString();
    }

    public void TrackInteraction()
    {
        interactionCount++;
    }

    public int GetPetLifetime() => petLifetime;
    public int GetInteractionCount() => interactionCount;
    public int GetTotalPlayTime() => totalPlayTime;
    public double GetParameterBalance() => parameterBalance;
}








