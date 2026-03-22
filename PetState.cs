// Абстрактный базовый класс 
public abstract class PetBase
{
    public string Name { get; protected set; }
    public string Type { get; protected set; }
    public int Age { get; protected set; }
    public abstract PetParameters Parameters { get; }
    public abstract void Update();
    public abstract void ShowStatus();
    public abstract void SpecialAbility();
}