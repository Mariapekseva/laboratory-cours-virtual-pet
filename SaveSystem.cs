using System;
using System.IO;

public class SaveSystem
{
    private string savePath;

    public SaveSystem(string path = "save.txt")
    {
        savePath = path;
    }

    public bool SaveGame(PetBase pet)
    {
        try
        {
            using (StreamWriter file = new StreamWriter(savePath))
            {
                file.WriteLine(pet.GetName());
                file.WriteLine(pet.GetType());
                file.WriteLine(pet.GetAge());

                var parameters = pet.GetParameters();
                file.WriteLine(parameters.GetHunger());
                file.WriteLine(parameters.GetFatigue());
                file.WriteLine(parameters.GetHealth());
                file.WriteLine(parameters.GetMood());
            }
            return true;
        }
        catch
        {
            return false;
        }
    }

    public bool LoadGame(PetBase pet)
    {
        try
        {
            if (!File.Exists(savePath))
                return false;

            using (StreamReader file = new StreamReader(savePath))
            {
                string name = file.ReadLine();
                string type = file.ReadLine();
                int age = int.Parse(file.ReadLine());

                int hunger = int.Parse(file.ReadLine());
                int fatigue = int.Parse(file.ReadLine());
                int health = int.Parse(file.ReadLine());
                int mood = int.Parse(file.ReadLine());

                pet.SetName(name);
                pet.SetType(type);
                pet.SetAge(age);

                var parameters = pet.GetParameters();
                parameters.SetHunger(hunger);
                parameters.SetFatigue(fatigue);
                parameters.SetHealth(health);
                parameters.SetMood(mood);

                pet.Update();
            }
            return true;
        }
        catch
        {
            return false;
        }
    }
}