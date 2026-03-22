using System;
// ISavable.cs
public interface ISavable
{
    bool Save(string path);
    bool Load(string path);
}