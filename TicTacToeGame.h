#pragma once
#include "MiniGame.h"
#include "PetBase.h"
#include <vector>
#include <map>

class TicTacToeGame : public MiniGame {
private:
    std::vector<char> board;
    char playerSymbol;
    char aiSymbol;
    int wins;
    int losses;
    int draws;

    void printBoard();
    bool checkWin(char player);
    bool isDraw();
    void applyEffects(PetParameters& params, bool win, bool draw);

public:
    TicTacToeGame(std::map<std::string, int> e);
    bool play(PetBase& pet) override;
    void showStats() const;
};