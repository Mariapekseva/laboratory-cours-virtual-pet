// Главный файл
//  Контейнер с базовыми и производными объектами
// Сортировка, поиск, обобщённая функция, обобщённый класс
using System;
using System.Collections.Generic;
using System.Linq;

class Program
{
    // Обобщённая функция (требование: шаблонная функция вне класса)
    public static double ComputeAverage<T>(IEnumerable<T> items, Func<T, double> selector)
    {
        var list = items.ToList();
        return list.Count == 0 ? 0.0 : list.Average(selector);
    }

    
    static void AnalyzePetGroup()
    {
        // Контейнер с объектами базового и производного классов
        var zoo = new List<PetBase>
        {
            new VirtualPet("Барсик", "Кот", 5),
            new MagicalPet("Хули", "Лис", 50, "Иллюзии"),
            new VirtualPet("Бобик", "Собака", 3),
            new MagicalPet("Дрогон", "Дракон", 200, "Огонь")
        };

        //  Сортировка по возрасту (аналог std::sort)
        var sorted = zoo.OrderBy(p => p.Age).ToList();

        // Поиск магического питомца (аналог std::find_if)
        var firstMagical = zoo.FirstOrDefault(p => p is MagicalPet);

        // Обобщённая функция: среднее настроение
        double avgMood = ComputeAverage(zoo, p => p.Parameters.Mood);

        // Обобщённый класс
        var magicalGroup = new PetContainer<MagicalPet>();
        if (firstMagical != null)
        {
            magicalGroup.Add((MagicalPet)firstMagical);
            magicalGroup.SortByAge();
        }
    }

    static void Main()
    {
        Console.InputEncoding = System.Text.Encoding.UTF8;
        Console.OutputEncoding = System.Text.Encoding.UTF8;

        
        AnalyzePetGroup();

        
    }
}