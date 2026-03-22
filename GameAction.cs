using System;

public class GameAction
{
    private string name;

    public GameAction(string name)
    {
        this.name = name;
    }

    public void Execute(PetParameters parameters)
    {
        if (name == "Покормить")
        {
            parameters.SetHunger(parameters.GetHunger() - 20);
            parameters.SetMood(parameters.GetMood() + 5);
            parameters.SetFatigue(parameters.GetFatigue() + 5);
        }
    }
}