using System;
using System.Collections.Generic;
using System.Linq;

public class Question
{
    public string Text { get; set; }
    public List<string> Options { get; set; }
    public int Correct { get; set; }
    public string Category { get; set; }
}

public class QuizGame : MiniGame
{
    private List<Question> questions;
    private List<Question> allQuestions;
    private int difficulty;
    private int correctAnswers;

    public QuizGame(Dictionary<string, int> effects) : base("Викторина", effects)
    {
        allQuestions = new List<Question>();
        questions = new List<Question>();
        difficulty = 5;
        correctAnswers = 0;
        LoadQuestions();
    }

    private void LoadQuestions()
    {
        allQuestions.Add(new Question
        {
            Text = "Кто сказал: Ребята, давайте жить дружно!",
            Options = new List<string> { "Волк", "Лиса", "Кот Леопольд", "Матроскин" },
            Correct = 2,
            Category = "мультики"
        });

        allQuestions.Add(new Question
        {
            Text = "Как звали кота из Простоквашино?",
            Options = new List<string> { "Барсик", "Матроскин", "Мурзик", "Феликс" },
            Correct = 1,
            Category = "мультики"
        });

        allQuestions.Add(new Question
        {
            Text = "Что такое std::vector?",
            Options = new List<string> { "Массив", "Динамический массив", "Список", "Очередь" },
            Correct = 1,
            Category = "cpp"
        });

        allQuestions.Add(new Question
        {
            Text = "Какой оператор для доступа через указатель?",
            Options = new List<string> { ".", "->", "::", "*" },
            Correct = 1,
            Category = "cpp"
        });

        allQuestions.Add(new Question
        {
            Text = "Что возвращает main() при успехе?",
            Options = new List<string> { "0", "1", "-1", "nullptr" },
            Correct = 0,
            Category = "cpp"
        });
    }

    private void SelectQuestions()
    {
        var random = new Random();
        var shuffled = allQuestions.OrderBy(x => random.Next()).Take(difficulty).ToList();
        questions = shuffled;
    }

    public override bool Play(PetBase pet)
    {
        Console.WriteLine("\n********************************************************");
        Console.WriteLine("*                    ВИКТОРИНА                         *");
        Console.WriteLine("********************************************************");
        Console.WriteLine("Выберите сложность:");
        Console.WriteLine("  1. Легкая (3 вопроса)");
        Console.WriteLine("  2. Средняя (5 вопросов)");
        Console.WriteLine("  3. Сложная (7 вопросов)");
        Console.Write("Ваш выбор: ");

        int diffChoice = int.Parse(Console.ReadLine() ?? "2");
        difficulty = diffChoice == 1 ? 3 : diffChoice == 3 ? 7 : 5;

        SelectQuestions();
        correctAnswers = 0;

        Console.WriteLine("\nНачинаем! Отвечайте цифрой (1-4)\n");

        for (int i = 0; i < questions.Count; i++)
        {
            var q = questions[i];
            Console.WriteLine($"--------------------------------------------------------");
            Console.WriteLine($"[{(q.Category == "cpp" ? "C++" : "Мультфильмы")}] Вопрос {i + 1}/{questions.Count}");
            Console.WriteLine($"--------------------------------------------------------");
            Console.WriteLine(q.Text);
            Console.WriteLine();

            for (int j = 0; j < q.Options.Count; j++)
            {
                Console.WriteLine($"  {j + 1}. {q.Options[j]}");
            }

            Console.Write("\nВаш ответ: ");
            int answer = int.Parse(Console.ReadLine() ?? "0");

            if (answer == q.Correct + 1)
            {
                correctAnswers++;
                Console.WriteLine("Правильно!");
            }
            else
            {
                Console.WriteLine($"Неправильно! Правильный ответ: {q.Correct + 1}");
            }
        }

        bool win = correctAnswers >= questions.Count / 2;

        Console.WriteLine("\n╔════════════════════════════════════════════════════════╗");
        Console.WriteLine("║                   РЕЗУЛЬТАТЫ                           ║");
        Console.WriteLine("╠════════════════════════════════════════════════════════╣");
        Console.WriteLine($"║  Правильных ответов: {correctAnswers,3} из {questions.Count,-12}               ");
        int percentage = questions.Count > 0 ? correctAnswers * 100 / questions.Count : 0;
        Console.WriteLine($"║  Процент успеха:     {percentage,3}%                              ");
        string resultText = win ? "ПОБЕДА!" : "Попробуйте еще раз";
        Console.WriteLine($"║  {resultText,-52}  ");
        Console.WriteLine("╚════════════════════════════════════════════════════════╝");

        int moodBonus = correctAnswers * 10;
        pet.GetParameters().SetMood(pet.GetParameters().GetMood() + moodBonus);
        pet.GetParameters().SetFatigue(pet.GetParameters().GetFatigue() + 5);

        Console.WriteLine("\nНажмите Enter для продолжения...");
        Console.ReadLine();

        return win;
    }
}