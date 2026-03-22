using System;

public class VirtualPet : PetBase
{
    protected PetState state;
    protected int xp;
    protected int level;

    public VirtualPet(string name, string type, int age) : base(name, type, age)
    {
        state = new PetState();
        xp = 0;
        level = 1;
    }

    public int GetXP() => xp;
    public int GetLevel() => level;
    public PetState GetState() => state;

    public override void Update()
    {
        state.DetermineState(
            parameters.GetHunger(),
            parameters.GetFatigue(),
            parameters.GetHealth()
        );
    }

    public override void ShowStatus()
    {
        // Эмодзи для типа питомца
        string petEmoji = type switch
        {
            "Кот" => "🐱",
            "Собака" => "🐶",
            "Хомяк" => "🐹",
            "Дракон" => "🐉",
            "Девятихвостый лис" => "🦊",
            _ => "🐾"
        };

        // Эмодзи для состояния
        string stateEmoji = parameters.GetHealth() < 30 ? "😷" :
                           parameters.GetHunger() > 70 ? "😋" :
                           parameters.GetFatigue() > 70 ? "😴" :
                           parameters.GetMood() > 70 ? "😄" : "😐";

        string nameStr = $"{name} ({type})";
        string stateStr = state.GetVisualization();

        Console.WriteLine("\n╔══════════════════════════════════════════════════════════╗");
        Console.WriteLine($"║                   {petEmoji} СТАТУС ПИТОМЦА {petEmoji}             ");
        Console.WriteLine("╠══════════════════════════════════════════════════════════╣");
        Console.WriteLine($"║  Имя:        {nameStr,-44}");
        Console.WriteLine($"║  Возраст:    {age,3} дней                                     ");
        Console.WriteLine($"║  Уровень:    {level,3} {GetStars(level),-42}");
        Console.WriteLine($"║  Состояние:  {stateEmoji} {stateStr,-40} ");
        Console.WriteLine("╠══════════════════════════════════════════════════════════╣");
        Console.WriteLine("║  Параметры:                                              ║");
        Console.WriteLine($"║    🍖 Голод:      {GetProgressBar(parameters.GetHunger()), -44}");
        Console.WriteLine($"║    😴 Усталость:  {GetProgressBar(parameters.GetFatigue()), -44}");
        Console.WriteLine($"║    ❤️  Здоровье:  {GetProgressBar(parameters.GetHealth()), -44}");
        Console.WriteLine($"║    😊 Настроение: {GetProgressBar(parameters.GetMood()), -44}");
        Console.WriteLine("╚══════════════════════════════════════════════════════════╝");
    }

    private string GetProgressBar(int percentage)
    {
        int filled = percentage / 10;
        int empty = 10 - filled;
        string bar = new string('█', filled) + new string('░', empty);
        return $"{bar} {percentage,3}%";
    }

    private string GetStars(int level)
    {
        return new string('⭐', Math.Min(level, 10));
    }

    public override void SpecialAbility()
    {
        Console.WriteLine($"\n💕 {name} мурлычет от удовольствия!");
    }

    public override void AddXP(int amount)
    {
        xp += amount;
        if (xp >= level * 100)
        {
            LevelUp();
        }
    }

    public virtual void LevelUp()
    {
        int oldLevel = level;
        level++;

        Console.WriteLine("\n╔══════════════════════════════════════════════════════════╗");
        Console.WriteLine("║           ⭐⭐⭐ УРОВЕНЬ ПОВЫШЕН! ⭐⭐⭐                ");
        Console.WriteLine("╠══════════════════════════════════════════════════════════╣");
        Console.WriteLine($"║  {name,-54} ");
        Console.WriteLine($"║  Уровень: {oldLevel,2} ➜ {level,2}                                  ");
        Console.WriteLine($"║  Опыт: +100                                              ");
        Console.WriteLine($"║  Здоровье восстановлено!                                 ");
        Console.WriteLine("╚══════════════════════════════════════════════════════════╝");

        parameters.SetHealth(100);
    }
}