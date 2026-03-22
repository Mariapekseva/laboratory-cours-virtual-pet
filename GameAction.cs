using System;
using System.Collections.Generic;
using System.Linq;

public class GameAction
{
    private string actionName;
    private Dictionary<string, int> effect;

    public GameAction()
        : this("Неизвестное действие")
    {
    }

    public GameAction(string actionName)
    {
        this.actionName = actionName;
        effect = new Dictionary<string, int>
        {
            ["hunger"] = 0,
            ["fatigue"] = 0,
            ["health"] = 0,
            ["mood"] = 0
        };

        if (actionName == "Покормить")
        {
            effect["hunger"] = -20;
            effect["mood"] = +10;
        }
        else if (actionName == "Уложить спать")
        {
            effect["fatigue"] = -100;
            effect["health"] = +15;
        }
        else if (actionName == "Поиграть")
        {
            effect["mood"] = +15;
            effect["fatigue"] = +10;
        }
    }

    public void Execute(PetParameters parameters)
    {
        parameters.SetHunger(parameters.Hunger + effect["hunger"]);
        parameters.SetFatigue(parameters.Fatigue + effect["fatigue"]);
        parameters.SetHealth(parameters.Health + effect["health"]);
        parameters.SetMood(parameters.Mood + effect["mood"]);
    }

    public Dictionary<string, int> CalculateEffects() => new Dictionary<string, int>(effect);

    public bool IsAvailable(PetState state)
    {
        var actions = state.GetAvailableActions();
        return actions.Contains(actionName);
    }

    public string GetActionName() => actionName;
    public Dictionary<string, int> GetEffect() => new Dictionary<string, int>(effect);
}