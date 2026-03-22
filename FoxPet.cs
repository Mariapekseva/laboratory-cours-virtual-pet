using System;

public class FoxPet : MagicalPet
{
    private int illusionUses;
    private bool eternalLifeUsed;

    public FoxPet(string name, string type, int age)
        : base(name, type, age, "Иллюзия")
    {
        illusionUses = 3;
        eternalLifeUsed = false;
    }

    public override void SpecialAbility()
    {
        if (illusionUses > 0)
        {
            Console.WriteLine($"{GetName()} создаёт ИЛЛЮЗИЮ!");
            Console.WriteLine("   Враги запутались, можно убежать!");
            illusionUses--;
            Console.WriteLine($"   Осталось использований: {illusionUses}");
        }
        else
        {
            Console.WriteLine($"{GetName()} слишком устал для иллюзий.");
        }
    }

    public override void LevelUp()
    {
        base.LevelUp();
        if (GetLevel() >= 3)
        {
            illusionUses = 3;
            Console.WriteLine($"{GetName()} восстановил иллюзии!");
        }
    }
}