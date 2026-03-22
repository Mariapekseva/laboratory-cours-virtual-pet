// Program.cs
using System;

class Program
{
    static void Main()
    {


        var dragon = new DragonPet("Игнас", 5);
        var fox = new FoxPet("Юйху", 8);

        Console.WriteLine("--- Дракон ---");
        dragon.MakeSound();
        dragon.Greet();
        dragon.UseSpecialAbility();
        dragon.ShowStatus();

        Console.WriteLine("\n--- Лис ---");
        fox.MakeSound();
        fox.Greet();
        fox.UseSpecialAbility();
        fox.ShowStatus();

        Console.WriteLine("\n--- Полиморфизм ---");
        VirtualPet pet1 = dragon;
        VirtualPet pet2 = fox;
        pet1.Interact();
        pet2.Interact();

        Console.WriteLine("\n--- Клонирование ---");
        var clone = (VirtualPet)fox.Clone();
        Console.WriteLine($"Клон {clone.Name}: настроение = {clone.Parameters.Mood}");

        Console.WriteLine("\n--- Интерфейсы ---");
        (dragon as IPlayable)?.PlayMiniGame();
        fox.Save("fox_save.txt");

        Console.WriteLine("\n✅ Все требования выполнены!");
    }
}