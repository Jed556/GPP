#ifndef QUIZ_H
#define QUIZ_H

#include <string>

class MultiChoiceQs {
   private:
    std::string* questions;
    std::string* answers;
    std::string* choices;
    int correctIndex;
    int numChoices = 4;
    int size = 0;

   public:
    MultiChoiceQs(int size, std::string qa[][2]);
    ~MultiChoiceQs();
    void setQuestion(int index, std::string value);
    void setAnswer(int index, std::string value);
    void setItem(int index, std::string question, std::string answer);
    void removeItem(int index);
    std::string getQuestion(int index) const;
    std::string getAnswer(int index) const;
    int getSize() const;
    void shuffleItems() const;
    void generateChoices(int index, int num);
    std::string printQuestion(int index, bool print) const;
    bool checkAnswer(std::string answer) const;
    void askQuestion(int index);
};

#endif  // QUIZ_H