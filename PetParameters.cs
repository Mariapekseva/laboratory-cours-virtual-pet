using System;
using System.Collections.Generic;

public class PetParameters
{
    private int hunger, fatigue, health, mood;

    public int Hunger => hunger;
    public int Fatigue => fatigue;
    public int Health => health;
    public int Mood => mood;

    public PetParameters(int hunger = 50, int fatigue = 50, int health = 100, int mood = 50)
    {
        SetHunger(hunger);
        SetFatigue(fatigue);
        SetHealth(health);
        SetMood(mood);
    }

    public void UpdateOverTime()
    {
        hunger += 10;
        fatigue += 5;
        if (hunger > 75) health -= 5;
        if (fatigue > 70) mood -= 10;
    }

    public bool CheckCriticalLevels() => health <= 20;

    public Dictionary<string, int> GetParameters() =>
        new() { ["hunger"] = hunger, ["fatigue"] = fatigue, ["health"] = health, ["mood"] = mood };

    public void SetHunger(int value) => hunger = Math.Clamp(value, 0, 100);
    public void SetFatigue(int value) => fatigue = Math.Clamp(value, 0, 100);
    public void SetHealth(int value) => health = Math.Clamp(value, 0, 100);
    public void SetMood(int value) => mood = Math.Clamp(value, 0, 100);
}

