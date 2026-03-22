#pragma once
#include "MiniGame.h"
#include <array>
#include <map>

class TicTacToeGame : public MiniGame {
private:
    std::array<char, 9> board;
    std::map<std::string, int> effects;

public:
    TicTacToeGame(std::map<std::string, int> effects);
    void startGame() override;
    void applyEffects(PetParameters& params) override;

private:
    void printBoard();
    bool checkWin(char player);
    bool isDraw();
};