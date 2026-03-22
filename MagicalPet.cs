using System;

public class MagicalPet : VirtualPet
{
    protected string magicType;

    public MagicalPet(string name, string type, int age, string magicType)
        : base(name, type, age)
    {
        this.magicType = magicType;
    }

    public string GetMagicType() => magicType;

    public override void ShowStatus()
    {
        base.ShowStatus();
        Console.WriteLine("╔════════════════════════════════════════════════════════╗");
        Console.WriteLine($"║  Магический тип: {magicType,-35}   ");
        Console.WriteLine("╚════════════════════════════════════════════════════════╝");
    }
}