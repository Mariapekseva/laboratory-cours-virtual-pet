using System;

public abstract class PetBase
{
    protected string name;
    protected string type;
    protected int age;
    protected PetParameters parameters;

    public PetBase(string name, string type, int age)
    {
        this.name = name;
        this.type = type;
        this.age = age;
        this.parameters = new PetParameters();
    }

    public string GetName() => name;
    public string GetType() => type;
    public int GetAge() => age;
    public PetParameters GetParameters() => parameters;

    public void SetName(string newName) => name = newName;
    public void SetType(string newType) => type = newType;
    public void SetAge(int newAge) => age = newAge;

    public virtual void AddXP(int amount) { }

    public abstract void ShowStatus();
    public abstract void Update();
    public abstract void SpecialAbility();
}