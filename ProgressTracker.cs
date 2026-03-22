using System;

public class ProgressTracker
{
    private int totalInteractions;
    private int totalGamesPlayed;
    private int totalGamesWon;
    private int totalXP;
    private int highestLevel;

    public ProgressTracker()
    {
        totalInteractions = 0;
        totalGamesPlayed = 0;
        totalGamesWon = 0;
        totalXP = 0;
        highestLevel = 1;
    }

    public void TrackInteraction() => totalInteractions++;

    public void TrackGame(bool won)
    {
        totalGamesPlayed++;
        if (won) totalGamesWon++;
    }

    public void UpdateXP(int xp) => totalXP = xp;

    public void UpdateLevel(int level)
    {
        if (level > highestLevel) highestLevel = level;
    }

    public void DisplayProgress()
    {
        Console.WriteLine("\n╔══════════════════════════════════════════════════════════╗");
        Console.WriteLine("║                  ПРОГРЕСС ИГРОКА                         ║");
        Console.WriteLine("╠══════════════════════════════════════════════════════════╣");
        Console.WriteLine($"║  Всего взаимодействий: {totalInteractions,5}                             ");
        Console.WriteLine($"║  Сыграно игр:          {totalGamesPlayed,5}                             ");
        Console.WriteLine($"║  Выиграно игр:         {totalGamesWon,5}                             ");
        Console.WriteLine($"║  Всего опыта:          {totalXP,5}                             ");
        Console.WriteLine($"║  Максимальный уровень: {highestLevel,5}                             ");

        if (totalGamesPlayed > 0)
        {
            int winRate = totalGamesWon * 100 / totalGamesPlayed;
            Console.WriteLine($"║  Процент побед:        {winRate,3}%                                ");
        }

        Console.WriteLine("╚══════════════════════════════════════════════════════════╝");
    }

    public int GetInteractionCount() => totalInteractions;
    public int GetGamesWon() => totalGamesWon;

    public void Reset()
    {
        totalInteractions = 0;
        totalGamesPlayed = 0;
        totalGamesWon = 0;
        totalXP = 0;
        highestLevel = 1;
    }
}