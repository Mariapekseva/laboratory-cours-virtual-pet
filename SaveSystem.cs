using System;
using System.IO;

public class SaveSystem
{
    private string savePath;
    private bool isAutoSaveEnabled;

    public SaveSystem() : this("save.txt", false) { }

    public SaveSystem(string savePath, bool autoSave)
    {
        this.savePath = savePath;
        this.isAutoSaveEnabled = autoSave;
    }

    public bool SaveGame(VirtualPet pet)
    {
        try
        {
            using (var writer = new StreamWriter(savePath))
            {
                writer.WriteLine(pet.Name);
                writer.WriteLine(pet.Type);
                writer.WriteLine(pet.Age);
                writer.WriteLine(pet.Parameters.Hunger);
                writer.WriteLine(pet.Parameters.Fatigue);
                writer.WriteLine(pet.Parameters.Health);
                writer.WriteLine(pet.Parameters.Mood);
            }
            return true;
        }
        catch
        {
            return false;
        }
    }

    public bool LoadGame(out VirtualPet pet)
    {
        pet = new VirtualPet();
        if (!File.Exists(savePath)) return false;

        try
        {
            var lines = File.ReadAllLines(savePath);
            if (lines.Length < 7) return false;

            string name = lines[0];
            string type = lines[1];
            if (!int.TryParse(lines[2], out int age)) return false;
            if (!int.TryParse(lines[3], out int hunger)) return false;
            if (!int.TryParse(lines[4], out int fatigue)) return false;
            if (!int.TryParse(lines[5], out int health)) return false;
            if (!int.TryParse(lines[6], out int mood)) return false;

            if (age < 0 || hunger < 0 || hunger > 100 ||
                fatigue < 0 || fatigue > 100 ||
                health < 0 || health > 100 ||
                mood < 0 || mood > 100)
                return false;

            pet = new VirtualPet(name, type, age);
            pet.Parameters.SetHunger(hunger);
            pet.Parameters.SetFatigue(fatigue);
            pet.Parameters.SetHealth(health);
            pet.Parameters.SetMood(mood);
            pet.Update();
            return true;
        }
        catch
        {
            return false;
        }
    }

    public void AutoSave(VirtualPet pet)
    {
        if (isAutoSaveEnabled) SaveGame(pet);
    }

    public string GetSavePath() => savePath;
    public bool GetAutoSave() => isAutoSaveEnabled;
}

