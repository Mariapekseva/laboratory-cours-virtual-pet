using System;

public enum PetStateType
{
    Healthy,
    Hungry,
    Tired,
    Sick,
    Happy,
    Sad
}

public class PetState
{
    private PetStateType state;

    public PetStateType GetState() => state;

    public string GetVisualization()
    {
        return state switch
        {
            PetStateType.Healthy => "😊 Здоров",
            PetStateType.Hungry => "😋 Голоден",
            PetStateType.Tired => "😴 Устал",
            PetStateType.Sick => "😷 Болен",
            PetStateType.Happy => "😄 Счастлив",
            PetStateType.Sad => "😢 Грустит",
            _ => "😐 Нормально"
        };
    }

    public void DetermineState(int hunger, int fatigue, int health)
    {
        if (health < 30)
            state = PetStateType.Sick;
        else if (hunger > 70)
            state = PetStateType.Hungry;
        else if (fatigue > 70)
            state = PetStateType.Tired;
        else if (hunger < 30 && fatigue < 30 && health > 70)
            state = PetStateType.Happy;
        else if (hunger > 60 || fatigue > 60)
            state = PetStateType.Sad;
        else
            state = PetStateType.Healthy;
    }
}