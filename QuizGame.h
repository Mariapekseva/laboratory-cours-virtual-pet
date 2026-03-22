#pragma once
#include "MiniGame.h"
#include <vector>
#include <string>
#include <map>
#include "PetBase.h"

struct Question {
    std::string text;
    std::vector<std::string> options;
    int correct;
    std::string category;
};

class QuizGame : public MiniGame {
private:
    std::vector<Question> questions;
    std::vector<Question> allQuestions;
    int difficulty;
    int correctAnswers;

    void loadQuestions();
    void selectQuestions();

public:
    QuizGame(std::map<std::string, int> e);
    bool play(PetBase& pet) override;
    void showResults() const;
};