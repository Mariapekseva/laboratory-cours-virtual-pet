using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Threading;

class Program
{
    static void Main(string[] args)
    {
        Console.OutputEncoding = System.Text.Encoding.UTF8;
        Console.CursorVisible = false; // Скрываем курсор для красоты

        // 🎬 Анимация приветствия
        ShowWelcomeAnimation();

        SaveSystem saveSystem = new SaveSystem();
        ProgressTracker tracker = new ProgressTracker();
        AchievementSystem achievements = new AchievementSystem();
        RandomEvent randomEvents = new RandomEvent();

        PetBase pet = null;
        bool isAsleep = false;
        int gamesWon = 0;

        // 🔄 Анимация загрузки сохранения
        if (File.Exists("save.txt"))
        {
            ShowLoading("Проверка сохранений");
            pet = new VirtualPet("Загрузка", "Кот", 0);
            if (saveSystem.LoadGame(pet))
            {
                ShowSuccess("Сохранение найдено!");
                Thread.Sleep(500);
            }
            else
            {
                pet = null;
            }
        }

        // 🐾 Выбор питомца
        if (!CreateOrLoadPet(ref pet, ref isAsleep, saveSystem))
        {
            ShowGoodbye();
            return;
        }

        // 🎮 Игровой цикл
        while (pet != null)
        {
            Console.Clear();
            pet.GetParameters().UpdateOverTime();
            pet.Update();
            pet.ShowStatus();

            ShowMenu(isAsleep);

            Console.Write("Выбор: ");
            string input = Console.ReadLine();
            if (!int.TryParse(input, out int action)) action = 0;

            bool exit = HandleAction(action, pet, isAsleep, ref isAsleep,
                saveSystem, tracker, achievements, randomEvents, ref gamesWon);

            if (exit) break;

            // Плавная пауза
            if (action != 7 && action != 11)
            {
                Console.WriteLine();
                ShowPressEnter();
            }
        }

        // 💾 Сохранение при выходе
        if (pet != null)
        {
            ShowLoading("Сохранение прогресса");
            saveSystem.SaveGame(pet);
            ShowSuccess("Игра сохранена!");
        }

        ShowGoodbye();
    }

    // 🎬 Анимация приветствия
    static void ShowWelcomeAnimation()
    {
        Console.Clear();
        Console.WriteLine("\n\n");
        TypewriterEffect("🎮 ВИРТУАЛЬНЫЙ ПИТОМЕЦ 🎮", ConsoleColor.Cyan, 50);
        Console.WriteLine();
        Thread.Sleep(300);

        string[] loadingFrames = { "🌱", "🌿", "🌳", "🌿", "🌱" };
        for (int i = 0; i < 5; i++)
        {
            Console.Write($"\r{new string(' ', 30)}\r");
            Console.Write($"Загрузка мира {loadingFrames[i]}");
            Thread.Sleep(200);
        }
        Console.WriteLine("\n");
        Thread.Sleep(500);
    }

    // ⌨️ Эффект печатной машинки
    static void TypewriterEffect(string text, ConsoleColor color, int delay)
    {
        Console.ForegroundColor = color;
        foreach (char c in text)
        {
            Console.Write(c);
            Thread.Sleep(delay);
        }
        Console.ResetColor();
    }

    // 🔄 Анимация загрузки
    static void ShowLoading(string message)
    {
        Console.Write($"\r{message} ");
        string[] spinner = { "⠋", "⠙", "", "⠸", "⠼", "⠴", "", "⠧", "⠇", "⠏" };
        for (int i = 0; i < 10; i++)
        {
            Console.Write($"\r{message} {spinner[i % spinner.Length]}");
            Thread.Sleep(80);
        }
        // Очищаем строку со спиннером
        Console.Write("\r" + new string(' ', message.Length + 2) + "\r");
    }

    // ✅ Анимация успеха
    static void ShowSuccess(string message)
    {
        Console.ForegroundColor = ConsoleColor.Green;
        Console.WriteLine($"\n✨ {message} ✨");
        Console.ResetColor();
    }

    // ❌ Анимация ошибки
    static void ShowError(string message)
    {
        Console.ForegroundColor = ConsoleColor.Red;
        Console.WriteLine($"\n❌ {message}");
        Console.ResetColor();
    }

    // 🎉 Анимация праздника
    static void ShowCelebration()
    {
        string[] emojis = { "🎉", "", "✨", "", "💫", "" };
        Random rand = new Random();
        int originalLeft = Console.CursorLeft;
        int originalTop = Console.CursorTop;

        for (int i = 0; i < 8; i++)
        {
            
            int newLeft = originalLeft + rand.Next(-5, 10);
            int newTop = originalTop + rand.Next(0, 3);

           
            if (newLeft < 0) newLeft = 0;
            if (newTop < 0) newTop = 0;
            if (newLeft >= Console.BufferWidth) newLeft = Console.BufferWidth - 1;
            if (newTop >= Console.BufferHeight) newTop = Console.BufferHeight - 1;

            Console.SetCursorPosition(newLeft, newTop);
            Console.Write(emojis[rand.Next(emojis.Length)]);
            Thread.Sleep(100);
        }
        Console.SetCursorPosition(0, originalTop + 3);
    }

    // 👇 Анимация "Нажмите Enter"
    static void ShowPressEnter()
    {
        Console.ForegroundColor = ConsoleColor.Gray;
        Console.Write("Нажмите Enter");

        string[] dots = { ".", "..", "...", "..", "." };
        for (int i = 0; i < 5; i++)
        {
            Console.Write($"\rНажмите Enter{dots[i % dots.Length]}");
            Thread.Sleep(200);
        }
        Console.ResetColor();
        Console.ReadLine();
        Console.Write("\r" + new string(' ', 20) + "\r");
    }

    // 🐾 Создание или загрузка питомца
    static bool CreateOrLoadPet(ref PetBase pet, ref bool isAsleep, SaveSystem saveSystem)
    {
        bool hasSavedPet = pet != null && saveSystem.LoadGame(pet);

        if (hasSavedPet)
        {
            Console.Clear();
            Console.WriteLine("\n╔══════════════════════════════════════════════════════════╗");
            Console.WriteLine("║         🎮 ОБНАРУЖЕН СОХРАНЁННЫЙ ПИТОМЕЦ 🎮              ║");
            Console.WriteLine("╠══════════════════════════════════════════════════════════╣");
            Console.WriteLine($"║  Имя:  {pet.GetName(),-48}  ║");
            Console.WriteLine($"║  Тип:  {pet.GetType(),-48}  ║");
            Console.WriteLine($"║  Возраст: {pet.GetAge(),3} дней                                       ║");
            Console.WriteLine("╟──────────────────────────────────────────────────────────╢");
            Console.WriteLine("║  1. Продолжить с этим питомцем                           ║");
            Console.WriteLine("║  2. Создать нового                                       ║");
            Console.WriteLine("╚══════════════════════════════════════════════════════════╝");
            Console.Write("\nВаш выбор: ");

            if (Console.ReadLine() != "1")
            {
                pet = null;
            }
            else
            {
                ShowSuccess($"Добро пожаловать, {pet.GetName()}! 🎉");
                Thread.Sleep(800);
                return true;
            }
        }

        return CreateNewPet(ref pet, saveSystem);
    }

    // 🆕 Создание нового питомца
    static bool CreateNewPet(ref PetBase pet, SaveSystem saveSystem)
    {
        Console.Clear();

        Console.WriteLine("\n╔══════════════════════════════════════════════════════════╗");
        Console.WriteLine("║              🐾 ВЫБЕРИТЕ ПИТОМЦА 🐾                      ║");
        Console.WriteLine("╠══════════════════════════════════════════════════════════╣");
        Console.WriteLine("║  1. 🐱 Кот                2. 🐶 Собака                   ║");
        Console.WriteLine("║  3. 🐹 Хомяк              4. 🐉 Дракон                   ║");
        Console.WriteLine("║  5. 🦊 Девятихвостый лис                                 ║");
        Console.WriteLine("╚══════════════════════════════════════════════════════════╝");
        Console.Write("\nВаш выбор: ");

        int choice = int.Parse(Console.ReadLine() ?? "1");
        string type = choice switch
        {
            1 => "Кот",
            2 => "Собака",
            3 => "Хомяк",
            4 => "Дракон",
            5 => "Девятихвостый лис",
            _ => "Кот"
        };

        string[] petEmojis = { "", "🐱", "🐶", "🐹", "🐉", "🦊" };
        Console.Write($"\n{petEmojis[choice]} Имя питомца: ");
        string name = Console.ReadLine();

        // 🎬 Анимация создания
        Console.WriteLine();
        ShowLoading("Создание питомца");
        Thread.Sleep(300);

        if (type == "Дракон")
            pet = new DragonPet(name, type, 0);
        else if (type == "Девятихвостый лис")
            pet = new FoxPet(name, type, 0);
        else
            pet = new VirtualPet(name, type, 0);

        pet.GetParameters().SetHunger(50);
        pet.GetParameters().SetFatigue(0);
        pet.GetParameters().SetHealth(100);
        pet.GetParameters().SetMood(70);
        pet.Update();
        saveSystem.SaveGame(pet);

        ShowCelebration();
        Console.ForegroundColor = ConsoleColor.Green;
        Console.WriteLine($"\n✨ {name} присоединился к вашей семье! ✨");
        Console.ResetColor();
        ShowPressEnter();

        return true;
    }

    // 📋 Отображение меню
    static void ShowMenu(bool isAsleep)
    {
        Console.WriteLine("\n╔══════════════════════════════════════════════════════════╗");
        Console.WriteLine("║                    🎮 МЕНЮ 🎮                            ║");
        Console.WriteLine("╠══════════════════════════════════════════════════════════╣");

        if (isAsleep)
        {
            Console.WriteLine("║  1. ☀️  Проснуться                                        ║");
            Console.WriteLine("║  2. 💾 Сохранить                                         ║");
            Console.WriteLine("║  3. 🏆 Достижения                                        ║");
            Console.WriteLine("║  4. 🚪 Выход                                             ║");
        }
        else
        {
            Console.WriteLine("║  1. 🍖 Покормить                                         ║");
            Console.WriteLine("║  2. 💊 Полечить                                          ║");
            Console.WriteLine("║  3. 💤 Уложить спать                                     ║");
            Console.WriteLine("║  4. 🧠 Поиграть (Викторина)                              ║");
            Console.WriteLine("║  5. ⭕ Поиграть (Крестики-нолики)                        ║");
            Console.WriteLine("║  6. ✨ Использовать спецспособность                      ║");
            Console.WriteLine("║  7. 💾 Сохранить                                         ║");
            Console.WriteLine("║  8. 🏆 Достижения                                        ║");
            Console.WriteLine("║  9. 📊 Просмотр прогресса                                ║");
            Console.WriteLine("║ 10. 📜 Журнал событий                                    ║");
            Console.WriteLine("║ 11. 🚪 Выход                                             ║");
        }
        Console.WriteLine("╚══════════════════════════════════════════════════════════╝");
    }

    // ⚡ Обработка действий
    static bool HandleAction(int action, PetBase pet, bool isAsleep, ref bool newIsAsleep,
        SaveSystem saveSystem, ProgressTracker tracker, AchievementSystem achievements,
        RandomEvent randomEvents, ref int gamesWon)
    {
        if (isAsleep)
        {
            return HandleSleepAction(action, pet, ref newIsAsleep, saveSystem, achievements);
        }
        else
        {
            return HandleAwakeAction(action, pet, saveSystem, tracker, achievements,
                randomEvents, ref gamesWon);
        }
    }

    // 😴 Действия когда питомец спит
    static bool HandleSleepAction(int action, PetBase pet, ref bool isAsleep,
        SaveSystem saveSystem, AchievementSystem achievements)
    {
        if (action == 1)
        {
            Console.WriteLine("\n☀️  Питомец проснулся!");
            Animation.AnimateHeart();
            isAsleep = false;
        }
        else if (action == 2)
        {
            ShowLoading("Сохранение");
            saveSystem.SaveGame(pet);
            ShowSuccess("Сохранено! 💾");
        }
        else if (action == 3)
        {
            achievements.DisplayAchievements();
        }
        else if (action == 4)
        {
            return true; // Выход
        }
        return false;
    }

    // 😊 Действия когда питомец не спит
    static bool HandleAwakeAction(int action, PetBase pet, SaveSystem saveSystem,
        ProgressTracker tracker, AchievementSystem achievements, RandomEvent randomEvents,
        ref int gamesWon)
    {
        switch (action)
        {
            case 1: // 🍖 Покормить
                Animation.AnimateFeeding();
                GameAction feed = new GameAction("Покормить");
                feed.Execute(pet.GetParameters());
                pet.Update();
                tracker.TrackInteraction();

                if (pet is VirtualPet vPet1)
                {
                    vPet1.AddXP(10);
                    tracker.UpdateXP(vPet1.GetXP());
                }

                ShowSuccess("Питомец покормлен! 🍽️");
                randomEvents.Trigger(pet);
                break;

            case 2: // 💊 Полечить
                Console.ForegroundColor = ConsoleColor.Green;
                Console.WriteLine("\n💊 Лечение...");
                Console.ResetColor();

                for (int i = 0; i <= 100; i += 20)
                {
                    pet.GetParameters().SetHealth(i);
                    Console.Write($"\r❤️  Здоровье: {i}%");
                    Thread.Sleep(150);
                }
                pet.GetParameters().SetMood(pet.GetParameters().GetMood() + 10);
                Console.WriteLine("\n✨ Питомец полностью здоров!");
                tracker.TrackInteraction();
                break;

            case 3: // 💤 Спать
                Console.WriteLine("\n💤 Питомец засыпает...");
                Animation.AnimateSleep();
                Thread.Sleep(500);
                Console.ForegroundColor = ConsoleColor.Gray;
                Console.WriteLine("😴 Zzz...");
                Console.ResetColor();
                break;

            case 4: // 🧠 Викторина
                QuizGame game1 = new QuizGame(new Dictionary<string, int> { { "mood", 15 }, { "fatigue", 10 } });
                bool won1 = game1.Play(pet);
                if (won1)
                {
                    gamesWon++;
                    ShowCelebration();
                }
                tracker.TrackGame(won1);
                pet.Update();
                tracker.TrackInteraction();
                if (pet is VirtualPet vPet2)
                {
                    vPet2.AddXP(15);
                    tracker.UpdateXP(vPet2.GetXP());
                }
                break;

            case 5: // ⭕ Крестики-нолики
                TicTacToeGame game2 = new TicTacToeGame(new Dictionary<string, int> { { "mood", 20 } });
                bool won2 = game2.Play(pet);
                if (won2)
                {
                    gamesWon++;
                    ShowCelebration();
                }
                tracker.TrackGame(won2);
                pet.Update();
                tracker.TrackInteraction();
                if (pet is VirtualPet vPet3)
                {
                    vPet3.AddXP(15);
                    tracker.UpdateXP(vPet3.GetXP());
                }
                break;

            case 6: // ✨ Спецспособность
                Console.WriteLine();
                pet.SpecialAbility();
                tracker.TrackInteraction();
                achievements.UnlockAchievement("Маг");
                break;

            case 7: // 💾 Сохранить
                ShowLoading("Сохранение");
                saveSystem.SaveGame(pet);
                ShowSuccess("Игра сохранена! 💾");
                break;

            case 8: // 🏆 Достижения
                achievements.DisplayAchievements();
                break;

            case 9: // 📊 Прогресс
                if (pet is VirtualPet vPet4)
                {
                    tracker.UpdateXP(vPet4.GetXP());
                    tracker.UpdateLevel(vPet4.GetXP() / 100);
                }
                tracker.DisplayProgress();
                break;

            case 10: // 📜 Журнал событий
                randomEvents.ShowEventLog();
                break;

            case 11: // 🚪 Выход
                return true;
        }
        return false;
    }

    // 👋 Анимация прощания
    static void ShowGoodbye()
    {
        Console.Clear();
        Console.WriteLine("\n\n");
        TypewriterEffect("💕 До свидания! 💕", ConsoleColor.Magenta, 80);
        Console.WriteLine("\n\n");
        Console.WriteLine("╔══════════════════════════════════════════════════════════╗");
        Console.WriteLine("║  🐾 Ваш питомец ждёт вас! Возвращайтесь скорее! 🐾      ║");
        Console.WriteLine("╚══════════════════════════════════════════════════════════╝");
        Console.WriteLine("\n");

        for (int i = 0; i < 3; i++)
        {
            Console.Write("🐾 ");
            Thread.Sleep(200);
        }
        Console.WriteLine("\n\n");
        Console.CursorVisible = true;
    }
}