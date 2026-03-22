using System;

public class PetParameters
{
    private int hunger;
    private int fatigue;
    private int health;
    private int mood;

    public PetParameters()
    {
        hunger = 50;
        fatigue = 0;
        health = 100;
        mood = 70;
    }

    public int GetHunger() => hunger;
    public int GetFatigue() => fatigue;
    public int GetHealth() => health;
    public int GetMood() => mood;
    public int GetEnergy() => 100 - fatigue;

    public void SetHunger(int value) => hunger = Math.Max(0, Math.Min(100, value));
    public void SetFatigue(int value) => fatigue = Math.Max(0, Math.Min(100, value));
    public void SetHealth(int value) => health = Math.Max(0, Math.Min(100, value));
    public void SetMood(int value) => mood = Math.Max(0, Math.Min(100, value));

    public void UpdateOverTime()
    {
        SetHunger(GetHunger() + 5);
        SetFatigue(GetFatigue() + 3);

        if (GetHunger() > 75)
            SetHealth(GetHealth() - 3);

        if (GetFatigue() > 70)
            SetMood(GetMood() - 5);

        if (GetHealth() < 30)
            SetMood(GetMood() - 5);
    }

    public bool CheckCriticalLevels()
    {
        return health <= 20 || hunger >= 90 || fatigue >= 90;
    }
}