#include "TicTacToeGame.h"
#include <iostream>
#include <random>
#include <algorithm>
#include <iomanip>  // ДОБАВЛЕНО: нужно для std::setw

TicTacToeGame::TicTacToeGame(std::map<std::string, int> e)
    : MiniGame("Крестики-нолики", e),
    board({ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' }),
    playerSymbol('X'), aiSymbol('O'), wins(0), losses(0), draws(0) {
}

void TicTacToeGame::printBoard() {
    std::cout << "\n";
    std::cout << "     1   2   3\n";
    std::cout << "   +---+---+---+\n";
    for (int i = 0; i < 9; i += 3) {
        std::cout << " " << (i / 3 + 1) << " | " << board[i] << " | " << board[i + 1] << " | " << board[i + 2] << " |\n";
        if (i < 6) std::cout << "   +---+---+---+\n";
    }
    std::cout << "   +---+---+---+\n";
}

bool TicTacToeGame::checkWin(char player) {
    int wins[8][3] = { {0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6} };
    for (auto& w : wins) {
        if (board[w[0]] == player && board[w[1]] == player && board[w[2]] == player)
            return true;
    }
    return false;
}

bool TicTacToeGame::isDraw() {
    return std::find(board.begin(), board.end(), ' ') == board.end();
}

void TicTacToeGame::applyEffects(PetParameters& params, bool win, bool draw) {
    if (draw) {
        params.setMood(params.getMood() + 5);
        params.setFatigue(params.getFatigue() + 5);
        draws++;
    }
    else if (win) {
        params.setMood(params.getMood() + 20);
        params.setHunger(params.getHunger() + 10);
        wins++;
    }
    else {
        params.setMood(params.getMood() - 10);
        params.setFatigue(params.getFatigue() + 10);
        losses++;
    }
}

void TicTacToeGame::showStats() const {
    std::cout << "\n********************************************************\n";
    std::cout << "*                   СТАТИСТИКА ИГРЫ                  *\n";
    std::cout << "********************************************************\n";
    std::cout << "*  Побед:     " << std::setw(5) << wins << "                               *\n";
    std::cout << "*  Поражений: " << std::setw(5) << losses << "                               *\n";
    std::cout << "*  Ничьих:    " << std::setw(5) << draws << "                               *\n";
    std::cout << "********************************************************\n";
}

bool TicTacToeGame::play(PetBase& pet) {
    std::cout << "\n";
    std::cout << "********************************************************\n";
    std::cout << "*               КРЕСТИКИ-НОЛИКИ                        *\n";
    std::cout << "********************************************************\n";
    std::cout << "Выберите символ:\n";
    std::cout << "  1. Крестики (X) - ходите первым\n";
    std::cout << "  2. Нолики (O) - ходит компьютер\n";
    std::cout << "Ваш выбор: ";
    int symbolChoice;
    std::cin >> symbolChoice;
    playerSymbol = (symbolChoice == 2) ? 'O' : 'X';
    aiSymbol = (playerSymbol == 'X') ? 'O' : 'X';

    std::cout << "\nВы играете за " << playerSymbol << "\n";
    printBoard();

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 8);

    bool gameEnded = false;
    bool playerTurn = (playerSymbol == 'X');
    bool playerWon = false;

    while (!gameEnded) {
        if (playerTurn) {
            int choice;
            std::cout << "\nВаш ход! Выберите клетку (1-9): ";
            if (!(std::cin >> choice)) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                continue;
            }
            choice--;
            if (choice < 0 || choice > 8 || board[choice] != ' ') {
                std::cout << "Неверный выбор. Повторите.\n";
                continue;
            }
            board[choice] = playerSymbol;
            printBoard();

            if (checkWin(playerSymbol)) {
                std::cout << "\n********************************************************\n";
                std::cout << "*                    ВЫ ВЫИГРАЛИ!                      *\n";
                std::cout << "********************************************************\n";
                applyEffects(pet.getParameters(), true, false);
                gameEnded = true;
                playerWon = true;
            }
            else if (isDraw()) {
                std::cout << "\n********************************************************\n";
                std::cout << "*                      НИЧЬЯ!                          *\n";
                std::cout << "********************************************************\n";
                applyEffects(pet.getParameters(), false, true);
                gameEnded = true;
            }
            playerTurn = false;
        }
        else {
            std::cout << "\nХод компьютера...\n";
            int aiChoice;
            do {
                aiChoice = dis(gen);
            } while (board[aiChoice] != ' ');
            board[aiChoice] = aiSymbol;
            printBoard();

            if (checkWin(aiSymbol)) {
                std::cout << "\n********************************************************\n";
                std::cout << "*                   ВЫ ПРОИГРАЛИ!                      *\n";
                std::cout << "********************************************************\n";
                applyEffects(pet.getParameters(), false, false);
                gameEnded = true;
            }
            else if (isDraw()) {
                std::cout << "\n********************************************************\n";
                std::cout << "*                      НИЧЬЯ!                          *\n";
                std::cout << "********************************************************\n";
                applyEffects(pet.getParameters(), false, true);
                gameEnded = true;
            }
            playerTurn = true;
        }
    }

    showStats();
    std::cout << "\nНажмите Enter для продолжения...";
    std::cin.ignore(10000, '\n');
    std::cin.get();

    return playerWon;
}