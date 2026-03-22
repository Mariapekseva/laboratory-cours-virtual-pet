// DragonPet.cs
using System;
using System.Collections.Generic;

public class DragonPet : VirtualPet, IPlayable, ISavable
{
    public DragonPet(string name, int age)
        : base(name, "Дракон", age)
    {
    }

    public override void MakeSound()
    {
        Console.WriteLine($"{Name} рычит и извергает огонь: 'РРР-ОГНЬ!'");
    }

    public override void UseSpecialAbility()
    {
        Console.WriteLine($"{Name} окутывает вас защитным пламенем!");
        Parameters.SetHealth(Math.Min(100, Parameters.Health + 20));
        Parameters.SetMood(Math.Min(100, Parameters.Mood + 10));
        Update();
    }

    public override void Greet()
    {
        Console.WriteLine($"{Name} машет крыльями и поднимает ветер!");
    }

    public void PlayMiniGame()
    {
        Console.WriteLine($"{Name} предлагает испытание огнём!");
        var game = new MiniGame("Испытание Дракона", 2, new Dictionary<string, int>
        {
            ["mood"] = 20,
            ["health"] = 10
        });
        game.StartGame();
        game.ApplyEffects(Parameters);
        Update();
    }

    public bool Save(string path)
    {
        var saver = new SaveSystem(path, false);
        return saver.SaveGame(this);
    }

    public bool Load(string path)
    {
        var saver = new SaveSystem(path, false);
        return saver.LoadGame(out VirtualPet loaded);
    }
}