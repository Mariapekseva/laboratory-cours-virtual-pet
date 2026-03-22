using System;
using System.Collections.Generic;
using System.Linq;

public class TicTacToeGame : MiniGame
{
    private List<char> board;
    private char playerSymbol;
    private char aiSymbol;
    private int wins;
    private int losses;
    private int draws;

    public TicTacToeGame(Dictionary<string, int> effects) : base("Крестики-нолики", effects)
    {
        // ИСПРАВЛЕНО: правильная инициализация доски
        board = new List<char> { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' };
        playerSymbol = 'X';
        aiSymbol = 'O';
        wins = 0;
        losses = 0;
        draws = 0;
    }

    private void PrintBoard()
    {
        Console.WriteLine("\n     1   2   3");
        Console.WriteLine("   +---+---+---+");
        for (int i = 0; i < 9; i += 3)
        {
            Console.WriteLine($" {i / 3 + 1} | {board[i]} | {board[i + 1]} | {board[i + 2]} |");
            if (i < 6) Console.WriteLine("   +---+---+---+");
        }
        Console.WriteLine("   +---+---+---+");
    }

    private bool CheckWin(char player)
    {
        int[,] wins = { { 0, 1, 2 }, { 3, 4, 5 }, { 6, 7, 8 }, { 0, 3, 6 }, { 1, 4, 7 }, { 2, 5, 8 }, { 0, 4, 8 }, { 2, 4, 6 } };
        for (int i = 0; i < 8; i++)
        {
            if (board[wins[i, 0]] == player &&
                board[wins[i, 1]] == player &&
                board[wins[i, 2]] == player)
                return true;
        }
        return false;
    }

    private bool IsDraw()
    {
        return !board.Contains(' ');
    }

    private void ApplyEffects(PetParameters parameters, bool win, bool draw)
    {
        if (draw)
        {
            parameters.SetMood(parameters.GetMood() + 5);
            parameters.SetFatigue(parameters.GetFatigue() + 5);
            draws++;
        }
        else if (win)
        {
            parameters.SetMood(parameters.GetMood() + 20);
            parameters.SetHunger(parameters.GetHunger() + 10);
            wins++;
        }
        else
        {
            parameters.SetMood(parameters.GetMood() - 10);
            parameters.SetFatigue(parameters.GetFatigue() + 10);
            losses++;
        }
    }

    private void ShowStats()
    {
        Console.WriteLine("\n╔════════════════════════════════════════════════════════╗");
        Console.WriteLine("║                   СТАТИСТИКА ИГРЫ                      ║");
        Console.WriteLine("╠════════════════════════════════════════════════════════╣");
        Console.WriteLine($"║  Побед:     {wins,5}                                      ║");
        Console.WriteLine($"║  Поражений: {losses,5}                                      ║");
        Console.WriteLine($"║  Ничьих:    {draws,5}                                      ║");
        Console.WriteLine("╚════════════════════════════════════════════════════════╝");
    }

    public override bool Play(PetBase pet)
    {
        Console.WriteLine("\n********************************************************");
        Console.WriteLine("*               КРЕСТИКИ-НОЛИКИ                        *");
        Console.WriteLine("********************************************************");
        Console.WriteLine("Выберите символ:");
        Console.WriteLine("  1. Крестики (X) - ходите первым");
        Console.WriteLine("  2. Нолики (O) - ходит компьютер");
        Console.Write("Ваш выбор: ");

        int symbolChoice = int.Parse(Console.ReadLine() ?? "1");
        playerSymbol = symbolChoice == 2 ? 'O' : 'X';
        aiSymbol = playerSymbol == 'X' ? 'O' : 'X';

        Console.WriteLine($"\nВы играете за {playerSymbol}");
        PrintBoard();

        Random random = new Random();
        bool gameEnded = false;
        bool playerTurn = playerSymbol == 'X';
        bool playerWon = false;

        while (!gameEnded)
        {
            if (playerTurn)
            {
                Console.Write("\nВаш ход! Выберите клетку (1-9): ");
                if (!int.TryParse(Console.ReadLine(), out int choice))
                {
                    Console.WriteLine("Неверный ввод. Повторите.");
                    continue;
                }

                choice--;
                if (choice < 0 || choice > 8 || board[choice] != ' ')
                {
                    Console.WriteLine("Неверный выбор. Повторите.");
                    continue;
                }

                board[choice] = playerSymbol;
                PrintBoard();

                if (CheckWin(playerSymbol))
                {
                    Console.WriteLine("\n********************************************************");
                    Console.WriteLine("*                    ВЫ ВЫИГРАЛИ!                      *");
                    Console.WriteLine("********************************************************");
                    ApplyEffects(pet.GetParameters(), true, false);
                    gameEnded = true;
                    playerWon = true;
                }
                else if (IsDraw())
                {
                    Console.WriteLine("\n********************************************************");
                    Console.WriteLine("*                      НИЧЬЯ!                          *");
                    Console.WriteLine("********************************************************");
                    ApplyEffects(pet.GetParameters(), false, true);
                    gameEnded = true;
                }
                playerTurn = false;
            }
            else
            {
                Console.WriteLine("\nХод компьютера...");
                int aiChoice;
                do
                {
                    aiChoice = random.Next(0, 9);
                } while (board[aiChoice] != ' ');

                board[aiChoice] = aiSymbol;
                PrintBoard();

                if (CheckWin(aiSymbol))
                {
                    Console.WriteLine("\n********************************************************");
                    Console.WriteLine("*                   ВЫ ПРОИГРАЛИ!                      *");
                    Console.WriteLine("********************************************************");
                    ApplyEffects(pet.GetParameters(), false, false);
                    gameEnded = true;
                }
                else if (IsDraw())
                {
                    Console.WriteLine("\n********************************************************");
                    Console.WriteLine("*                      НИЧЬЯ!                          *");
                    Console.WriteLine("********************************************************");
                    ApplyEffects(pet.GetParameters(), false, true);
                    gameEnded = true;
                }
                playerTurn = true;
            }
        }

        ShowStats();
        Console.WriteLine("\nНажмите Enter для продолжения...");
        Console.ReadLine();

        return playerWon;
    }
}