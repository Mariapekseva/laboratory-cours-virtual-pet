#pragma once
#include <string>
#include "PetBase.h"

class VirtualPet;

// Сохранение и загрузка игры
class SaveSystem
{
public:
    SaveSystem(); // Сохраняет в "save.txt", без автосохранения
    SaveSystem(std::string savePath, bool autoSave);
    ~SaveSystem();

    bool saveGame(const PetBase& pet);
    bool loadGame(PetBase& pet);
    void autoSave(const PetBase& pet);

    std::string getSavePath() const;
    bool getAutoSave() const;

private:
    std::string savePath;        // Путь к файлу
    bool isAutoSaveEnabled;      // Включено ли автосохранение
};
