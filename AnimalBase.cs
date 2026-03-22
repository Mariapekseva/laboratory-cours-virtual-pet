using System;

public abstract class AnimalBase
{
    public string Name { get; protected set; }
    public string Species { get; protected set; }
    public int Age { get; protected set; }
    public PetParameters Parameters { get; protected set; }
    protected PetState State;

    // Абстрактный метод — обязаны реализовать в потомке
    public abstract void MakeSound();

    // Виртуальный метод — можно переопределить
    public virtual void Greet()
    {
        Console.WriteLine($"{Name} машет хвостом.");
    }

    // Общая логика
    public void ShowStatus()
    {
        Console.WriteLine("\n   Статус питомца   ");
        Console.WriteLine($"Имя: {Name}");
        Console.WriteLine($"Тип: {Species}");
        Console.WriteLine($"Возраст: {Age} дней");
        Console.WriteLine($"Состояние: {State?.GetVisualization() ?? "Неизвестно"}");
        Console.WriteLine("Параметры:");
        Console.WriteLine($"  Голод: {Parameters.Hunger}%");
        Console.WriteLine($"  Усталость: {Parameters.Fatigue}%");
        Console.WriteLine($"  Здоровье: {Parameters.Health}%");
        Console.WriteLine($"  Настроение: {Parameters.Mood}%");
        Console.WriteLine("---------------------");
    }

    // Обновление состояния
    public void Update()
    {
        State.DetermineState(Parameters.Hunger, Parameters.Fatigue, Parameters.Health);
    }

    // Конструктор с параметрами — вызывается потомками
    protected AnimalBase(string name, string species, int age)
    {
        Name = name;
        Species = species;
        Age = age;
        Parameters = new PetParameters();
        State = new PetState();
        Update();
    }
}