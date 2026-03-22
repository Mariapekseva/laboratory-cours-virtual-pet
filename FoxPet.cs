// FoxPet.cs
using System;
using System.Collections.Generic;

public class FoxPet : VirtualPet, IPlayable, ISavable
{
    public FoxPet(string name, int age)
        : base(name, "Девятихвостый лис", age)
    {
    }

    public override void MakeSound()
    {
        Console.WriteLine($"{Name} тихо смеётся: 'Хи-хи-хи...'");
    }

    public override void UseSpecialAbility()
    {
        Console.WriteLine($"{Name} создаёт иллюзию — вы получаете +25 к настроению!");
        Parameters.SetMood(Math.Min(100, Parameters.Mood + 25));
        Update();
    }

    public override void Greet()
    {
        base.Greet();
        Console.WriteLine($"{Name} кланяется изящно, хвосты мерцают.");
    }

    public void PlayMiniGame()
    {
        Console.WriteLine($"{Name} предлагает загадку древнего лиса!");
        var game = new MiniGame("Загадки Лиса", 1, new Dictionary<string, int>
        {
            ["mood"] = 30
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