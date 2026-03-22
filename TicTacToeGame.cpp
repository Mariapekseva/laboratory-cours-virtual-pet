#include "TicTacToeGame.h"
#include <iostream>
#include <random>
#include <algorithm>

TicTacToeGame::TicTacToeGame(std::map<std::string, int> effects) : effects(effects) {
    std::fill(board.begin(), board.end(), ' ');
}

void TicTacToeGame::printBoard() {
    for (int i = 0; i < 9; i += 3) {
        std::cout << board[i] << " | " << board[i + 1] << " | " << board[i + 2] << "\n";
        if (i < 6) std::cout << "--+---+--\n";
    }
}

bool TicTacToeGame::checkWin(char player) {
    int wins[8][3] = { {0,1,2}, {3,4,5}, {6,7,8}, {0,3,6}, {1,4,7}, {2,5,8}, {0,4,8}, {2,4,6} };
    for (auto& w : wins) {
        if (board[w[0]] == player && board[w[1]] == player && board[w[2]] == player)
            return true;
    }
    return false;
}

bool TicTacToeGame::isDraw() {
    return std::find(board.begin(), board.end(), ' ') == board.end();
}

void TicTacToeGame::startGame() {
    std::cout << "Игра: Крестики-нолики!\n";
    printBoard();

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 8);

    while (true) {
        // Игрок
        int choice;
        std::cout << "Выберите клетку (1-9): ";
        std::cin >> choice;
        choice--;
        if (choice < 0 || choice > 8 || board[choice] != ' ') {
            std::cout << "Неверный выбор. Повторите.\n";
            continue;
        }
        board[choice] = 'X';
        printBoard();

        if (checkWin('X')) {
            std::cout << "Вы выиграли!\n";
            applyEffects(*new PetParameters()); // Не используем, но можно вызвать
            return;
        }
        if (isDraw()) {
            std::cout << "Ничья!\n";
            applyEffects(*new PetParameters());
            return;
        }

        // ИИ
        int aiChoice;
        do {
            aiChoice = dis(gen);
        } while (board[aiChoice] != ' ');
        board[aiChoice] = 'O';
        printBoard();

        if (checkWin('O')) {
            std::cout << "Вы проиграли!\n";
            applyEffects(*new PetParameters());
            return;
        }
        if (isDraw()) {
            std::cout << "Ничья!\n";
            applyEffects(*new PetParameters());
            return;
        }
    }
}

void TicTacToeGame::applyEffects(PetParameters& params) {
    // Пример: победа даёт +20 к настроению
    params.setMood(params.getMood() + effects["mood"]);
}