// Производный класс: обычный питомец 
using System;

public class VirtualPet : PetBase
{
    public override PetParameters Parameters { get; }
    private PetState state;

    public VirtualPet(string name, string type, int age)
    {
        Name = name;
        Type = type;
        Age = age;
        Parameters = new PetParameters();
        state = new PetState();
        Update();
    }

    public override void Update()
    {
        state.DetermineState(Parameters.Hunger, Parameters.Fatigue, Parameters.Health);
    }

    public PetState GetState() => state;

    public override void ShowStatus()
    {
        Console.WriteLine($"\n[Статус] {Name} ({Type}), {Age} дней");
    }

    public override void SpecialAbility()
    {
        
    }
}