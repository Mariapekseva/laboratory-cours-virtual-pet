using System;
using System.Collections.Generic;

public class Achievement
{
    public string Name { get; set; }
    public string Description { get; set; }
    public string Requirement { get; set; }
    public bool Unlocked { get; set; }
}

public class AchievementSystem
{
    private List<Achievement> achievements;

    public AchievementSystem()
    {
        achievements = new List<Achievement>
        {
            new Achievement { Name = "Новичок", Description = "Начать игру", Requirement = "Создайте первого питомца", Unlocked = false },
            new Achievement { Name = "Любящий хозяин", Description = "Покормить 10 раз", Requirement = "10 взаимодействий", Unlocked = false },
            new Achievement { Name = "Игрок", Description = "Выиграть 5 игр", Requirement = "5 побед в мини-играх", Unlocked = false },
            new Achievement { Name = "Эксперт C++", Description = "Ответить на 10 вопросов", Requirement = "Викторина C++", Unlocked = false },
            new Achievement { Name = "Маг", Description = "Использовать спецспособность", Requirement = "Магический питомец", Unlocked = false },
            new Achievement { Name = "Долгожитель", Description = "Питомец достиг 10 уровня", Requirement = "Level 10+", Unlocked = false },
            new Achievement { Name = "Перфекционист", Description = "Все параметры 100%", Requirement = "Максимальные статы", Unlocked = false },
            new Achievement { Name = "Коллекционер", Description = "Создать 5 питомцев", Requirement = "5 разных питомцев", Unlocked = false }
        };
    }

    public void UnlockAchievement(string name)
    {
        foreach (var ach in achievements)
        {
            if (ach.Name == name && !ach.Unlocked)
            {
                ach.Unlocked = true;
                Console.WriteLine("\n╔════════════════════════════════════════════════════════╗");
                Console.WriteLine("║ ДОСТИЖЕНИЕ РАЗБЛОКИРОВАНО!                             ");
                Console.WriteLine("╠════════════════════════════════════════════════════════╣");
                Console.WriteLine($"║ {ach.Name,-56} ");
                Console.WriteLine("╟────────────────────────────────────────────────────────╢");
                Console.WriteLine($"║ {ach.Description,-56} ");
                Console.WriteLine("╚════════════════════════════════════════════════════════╝");
            }
        }
    }

    public void CheckAchievements(int level, int interactions, int gamesWon)
    {
        if (interactions >= 10) UnlockAchievement("Любящий хозяин");
        if (gamesWon >= 5) UnlockAchievement("Игрок");
        if (level >= 10) UnlockAchievement("Долгожитель");
    }

    public void DisplayAchievements()
    {
        Console.WriteLine("\n╔════════════════════════════════════════════════════════╗");
        Console.WriteLine("║                 ДОСТИЖЕНИЯ                             ║");
        Console.WriteLine("╠════════════════════════════════════════════════════════╣");

        int unlocked = 0;
        foreach (var ach in achievements)
        {
            string status = ach.Unlocked ? "[*]" : "[ ]";
            Console.WriteLine($"║ {status} {ach.Name,-48} ║");
            Console.WriteLine($"║     {ach.Description,-48} ║");
            Console.WriteLine($"║     Требование: {ach.Requirement,-32} ║");
            Console.WriteLine("╟────────────────────────────────────────────────────────╢");
            if (ach.Unlocked) unlocked++;
        }

        Console.WriteLine($"║ Прогресс: {unlocked}/{achievements.Count,-45} ║");
        Console.WriteLine("╚════════════════════════════════════════════════════════╝");
    }
}