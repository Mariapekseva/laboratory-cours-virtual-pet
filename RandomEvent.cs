using System;
using System.Collections.Generic;

public class GameEvent
{
    public string Name { get; set; }
    public string Description { get; set; }
    public int HungerChange { get; set; }
    public int FatigueChange { get; set; }
    public int HealthChange { get; set; }
    public int MoodChange { get; set; }
    public int XPChange { get; set; }
}

public class RandomEvent
{
    private List<GameEvent> events;
    private int eventsTriggered;

    public RandomEvent()
    {
        events = new List<GameEvent>();
        eventsTriggered = 0;
        InitializeEvents();
    }

    private void InitializeEvents()
    {
        // Положительные события
        events.Add(new GameEvent { Name = "Щедрый сосед", Description = "Сосед угостил питомца вкусняшками!", HungerChange = -30, FatigueChange = 0, HealthChange = 5, MoodChange = 15, XPChange = 10 });
        events.Add(new GameEvent { Name = "Находка в парке", Description = "Питомец нашёл потерянную игрушку!", HungerChange = 0, FatigueChange = -10, HealthChange = 0, MoodChange = 20, XPChange = 15 });
        events.Add(new GameEvent { Name = "Лотерея выигрыш", Description = "Вы выиграли 500 монет в лотерею!", HungerChange = 0, FatigueChange = 0, HealthChange = 0, MoodChange = 25, XPChange = 30 });
        events.Add(new GameEvent { Name = "День рождения", Description = "У питомца день рождения!", HungerChange = -25, FatigueChange = -10, HealthChange = 10, MoodChange = 40, XPChange = 50 });

        // Отрицательные события
        events.Add(new GameEvent { Name = "Дождливая погода", Description = "Плохая погода испортила настроение", HungerChange = 5, FatigueChange = 10, HealthChange = -5, MoodChange = -15, XPChange = 0 });
        events.Add(new GameEvent { Name = "Простуда", Description = "Питомец немного простудился", HungerChange = 5, FatigueChange = 10, HealthChange = -15, MoodChange = -10, XPChange = 0 });
        events.Add(new GameEvent { Name = "Голодный день", Description = "Корм закончился раньше времени", HungerChange = 25, FatigueChange = 5, HealthChange = -5, MoodChange = -15, XPChange = 0 });
    }

    public bool Trigger(PetBase pet)
    {
        Random random = new Random();
        int chance = random.Next(1, 101);

        if (chance > 30)
            return false;

        int eventIndex = random.Next(0, events.Count);
        var gameEvent = events[eventIndex];

        pet.GetParameters().SetHunger(pet.GetParameters().GetHunger() + gameEvent.HungerChange);
        pet.GetParameters().SetFatigue(pet.GetParameters().GetFatigue() + gameEvent.FatigueChange);
        pet.GetParameters().SetHealth(pet.GetParameters().GetHealth() + gameEvent.HealthChange);
        pet.GetParameters().SetMood(pet.GetParameters().GetMood() + gameEvent.MoodChange);

        if (gameEvent.XPChange > 0 && pet is VirtualPet vPet)
        {
            vPet.AddXP(gameEvent.XPChange);
        }

        Console.WriteLine("\n╔════════════════════════════════════════════════════════╗");
        Console.WriteLine("║              СЛУЧАЙНОЕ СОБЫТИЕ!                        ║");
        Console.WriteLine("╠════════════════════════════════════════════════════════╣");
        Console.WriteLine($"║ {gameEvent.Name,-56} ║");
        Console.WriteLine("╟────────────────────────────────────────────────────────╢");
        Console.WriteLine($"║ {gameEvent.Description,-56} ");

        if (gameEvent.HungerChange != 0)
            Console.WriteLine($"║ Голод: {(gameEvent.HungerChange > 0 ? "+" : "")}{gameEvent.HungerChange,-3}                                        ");
        if (gameEvent.FatigueChange != 0)
            Console.WriteLine($"║ Усталость: {(gameEvent.FatigueChange > 0 ? "+" : "")}{gameEvent.FatigueChange,-3}                                      ");
        if (gameEvent.HealthChange != 0)
            Console.WriteLine($"║ Здоровье: {(gameEvent.HealthChange > 0 ? "+" : "")}{gameEvent.HealthChange,-3}                                       ");
        if (gameEvent.MoodChange != 0)
            Console.WriteLine($"║ Настроение: {(gameEvent.MoodChange > 0 ? "+" : "")}{gameEvent.MoodChange,-3}                                       ");
        if (gameEvent.XPChange > 0)
            Console.WriteLine($"║ Опыт: +{gameEvent.XPChange,-2}                                             ");

        Console.WriteLine("╚════════════════════════════════════════════════════════╝");

        eventsTriggered++;
        return true;
    }

    public void ShowEventLog()
    {
        Console.WriteLine("\n╔════════════════════════════════════════════════════════╗");
        Console.WriteLine("║           Журнал событий                               ");
        Console.WriteLine("╠════════════════════════════════════════════════════════╣");
        Console.WriteLine($"║ Всего событий произошло: {eventsTriggered,-26} ");
        Console.WriteLine("╚════════════════════════════════════════════════════════╝");
    }
}