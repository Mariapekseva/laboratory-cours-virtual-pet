using System;

public class DragonPet : MagicalPet
{
    private int fireBreathUses;
    private bool ancientPowerUnlocked;

    public DragonPet(string name, string type, int age)
        : base(name, type, age, "Огонь")
    {
        fireBreathUses = 3;
        ancientPowerUnlocked = false;
    }

    public override void SpecialAbility()
    {
        if (fireBreathUses > 0)
        {
            Console.WriteLine($"{GetName()} использует ОГНЕННОЕ ДЫХАНИЕ!");
            Console.WriteLine("   Враги получают урон, настроение повышается!");
            fireBreathUses--;
            Console.WriteLine($"   Осталось использований: {fireBreathUses}");
        }
        else
        {
            Console.WriteLine($"{GetName()} слишком устал для огненного дыхания.");
            Console.WriteLine("   Отдохните и попробуйте позже!");
        }
    }

    public override void LevelUp()
    {
        base.LevelUp();
        if (GetLevel() >= 5 && !ancientPowerUnlocked)
        {
            ancientPowerUnlocked = true;
            fireBreathUses = 5;
            Console.WriteLine($"{GetName()} получил ДРЕВНЮЮ СИЛУ!");
            Console.WriteLine("   Огненное дыхание стало мощнее!");
        }
    }
}