using System;
using System.Collections.Generic;

public class MiniGame
{
    private string gameName;
    private int difficulty;
    private Dictionary<string, int> rewards;

    public MiniGame()
        : this("Угадай мультфильм!", 1, new Dictionary<string, int>
        {
            ["mood"] = 15,
            ["fatigue"] = 10
        })
    {
    }

    public MiniGame(string gameName, int difficulty, Dictionary<string, int> rewards)
    {
        this.gameName = gameName;
        this.difficulty = difficulty;
        this.rewards = new Dictionary<string, int>(rewards);
    }

    public void StartGame()
    {
        Console.WriteLine($"\n=== {gameName} ===");
        Console.WriteLine("Ответьте на 3 вопроса!");

        var questions = new List<(string Text, string[] Options, int Correct)>
        {
            ("Кто главный герой \"Ледникового периода\"?", new[] { "Марти", "Сид", "Манфред", "Диего" }, 3),
            ("Как зовут русалочку Тритона?", new[] { "Ариэль", "Анастасия", "Эльза", "Белль" }, 1),
            ("Фраза \"Каааакс!\" из какого мультфильма?", new[] { "Ну, погоди!", "Том и Джерри", "Смешарики", "Маша и Медведь" }, 1),
            ("Кто из них — дракон из \"Как приручить дракона\"?", new[] { "Шрек", "Тоторо", "Беззубик", "Пушистик" }, 3)
        };

        var random = new Random();
        var selectedQuestions = new List<(string, string[], int)>();
        for (int i = 0; i < 3 && questions.Count > 0; i++)
        {
            int idx = random.Next(questions.Count);
            selectedQuestions.Add(questions[idx]);
            questions.RemoveAt(idx);
        }

        int correctCount = 0;
        for (int i = 0; i < selectedQuestions.Count; i++)
        {
            var (text, options, correct) = selectedQuestions[i];
            Console.WriteLine($"\nВопрос {i + 1}:");
            Console.WriteLine(text);
            for (int j = 0; j < options.Length; j++)
            {
                Console.WriteLine($"{j + 1}. {options[j]}");
            }

            Console.Write($"Ваш выбор (1–{options.Length}): ");
            if (int.TryParse(Console.ReadLine(), out int choice) && choice == correct)
            {
                Console.WriteLine("Правильно!");
                correctCount++;
            }
            else
            {
                Console.WriteLine($"Неверно. Правильный ответ: {options[correct - 1]}");
            }
        }

        Console.WriteLine($"\nИгра завершена! Правильных ответов: {correctCount}/3");
    }

    public void ApplyEffects(PetParameters parameters)
    {
        foreach (var reward in rewards)
        {
            switch (reward.Key)
            {
                case "hunger":
                    parameters.SetHunger(parameters.Hunger + reward.Value);
                    break;
                case "fatigue":
                    parameters.SetFatigue(parameters.Fatigue + reward.Value);
                    break;
                case "health":
                    parameters.SetHealth(parameters.Health + reward.Value);
                    break;
                case "mood":
                    parameters.SetMood(parameters.Mood + reward.Value);
                    break;
            }
        }
        Console.WriteLine("Вы получили награду за участие!");
    }
}
