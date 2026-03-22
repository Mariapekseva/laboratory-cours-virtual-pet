using System;
using System.Collections.Generic;

public abstract class MiniGame
{
    protected string name;
    protected Dictionary<string, int> effects;

    public MiniGame(string name, Dictionary<string, int> effects)
    {
        this.name = name;
        this.effects = effects;
    }

    public string GetName() => name;
    public abstract bool Play(PetBase pet);
}