using System;
using System.Threading;

public static class Animation
{
    public static void ShowLoadingBar(int duration = 1000)
    {
        Console.Write("Загрузка [");
        for (int i = 0; i < 20; i++)
        {
            Console.Write("█");
            Thread.Sleep(duration / 20);
        }
        Console.WriteLine("] Готово!");
    }

    public static void ShowSpinner(string message, int duration = 2000)
    {
        string[] frames = { "⠋", "⠙", "", "⠸", "⠼", "⠴", "", "⠧", "⠇", "⠏" };
        Console.Write(message + " ");

        int end = Console.CursorLeft;
        for (int i = 0; i < duration / 50; i++)
        {
            Console.SetCursorPosition(end - message.Length - 2, Console.CursorTop);
            Console.Write(frames[i % frames.Length]);
            Thread.Sleep(50);
        }
        Console.WriteLine();
    }

    public static void AnimateHeart()
    {
        string[] hearts = { "💕", "💖", "💗", "💓", "💕" };
        int left = Console.CursorLeft;
        int top = Console.CursorTop;

        for (int i = 0; i < 5; i++)
        {
            Console.SetCursorPosition(left, top);
            Console.Write(hearts[i]);
            Thread.Sleep(200);
        }
        Console.WriteLine();
    }

    public static void AnimateFeeding()
    {
        Console.WriteLine("\n🍖 Кормим питомца...");
        string[] animation = { "🍖", "🍖>", "🍖>>", "🍖>>>", "🍖>>>>", "😋 Ням!" };

        foreach (var frame in animation)
        {
            Console.Write("\r" + new string(' ', 30) + "\r");
            Console.Write(frame);
            Thread.Sleep(300);
        }
        Console.WriteLine();
    }

    public static void AnimateSleep()
    {
        string[] zzz = { "💤", "💤💤", "💤💤" };
        int left = Console.CursorLeft;
        int top = Console.CursorTop;

        for (int i = 0; i < 3; i++)
        {
            Console.SetCursorPosition(left + i * 2, top - i);
            Console.Write(zzz[i % zzz.Length]);
            Thread.Sleep(500);
        }
    }

    public static void AnimateLevelUp(int oldLevel, int newLevel)
    {
        Console.WriteLine("\n╔══════════════════════════════════════════════════╗");
        Console.WriteLine("║             ⭐ УРОВЕНЬ ПОВЫШЕН! ⭐                ║");
        Console.WriteLine("╚══════════════════════════════════════════════════╝\n");

        // Анимация звёздочек
        for (int i = 0; i < 3; i++)
        {
            Console.WriteLine(new string(' ', i * 2) + "✨✨✨");
            Thread.Sleep(200);
        }

        Console.WriteLine($"\n🎉 Уровень {oldLevel} → {newLevel}!");
        Console.WriteLine("📈 Опыт: +100\n");
    }

    public static void AnimateBattle()
    {
        string[] frames = { "⚔️", "⚔️", "💥", "🎯✨" };

        foreach (var frame in frames)
        {
            Console.Write("\r" + frame + new string(' ', 20));
            Thread.Sleep(300);
        }
        Console.WriteLine();
    }

    public static void ClearWithFade()
    {
        for (int i = 0; i < 5; i++)
        {
            Console.BackgroundColor = (ConsoleColor)i;
            Console.Clear();
            Thread.Sleep(100);
        }
        Console.ResetColor();
        Console.Clear();
    }

    public static void ShowCelebration()
    {
        string[] emojis = { "🎉", "", "✨", "", "💫" };
        Random rand = new Random();

        for (int i = 0; i < 10; i++)
        {
            int left = rand.Next(0, 60);
            int top = Console.CursorTop + rand.Next(0, 5);
            Console.SetCursorPosition(left, top);
            Console.Write(emojis[rand.Next(emojis.Length)]);
            Thread.Sleep(100);
        }
        Console.WriteLine();
    }
}