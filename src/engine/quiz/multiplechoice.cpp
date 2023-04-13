#include <algorithm>  // for std::random_shuffle
#include <cstdlib>    // for std::rand and std::srand
#include <ctime>      // for std::time
#include <iostream>
#include <string>

#include "quiz.h"

MultiChoiceQs::MultiChoiceQs(int size, std::string qa[][2]) {
    this->size = size;
    this->questions = new std::string[size];
    this->answers = new std::string[size];

    for (int i = 0; i < size; i++) {
        this->questions[i] = qa[i][0];
        this->answers[i] = qa[i][1];
    }
}

MultiChoiceQs::~MultiChoiceQs() {
    delete[] questions;
    delete[] answers;
}

void MultiChoiceQs::setQuestion(int index, std::string value) {
    questions[index] = value;
}

void MultiChoiceQs::setAnswer(int index, std::string value) {
    answers[index] = value;
}

void MultiChoiceQs::setItem(int index, std::string question, std::string answer) {
    questions[index] = question;
    answers[index] = answer;
}

void MultiChoiceQs::removeItem(int index) {
    for (int i = index; i < size - 1; i++) {
        questions[i] = questions[i + 1];
        answers[i] = answers[i + 1];
    }
    size--;
}

std::string MultiChoiceQs::getQuestion(int index) const {
    return questions[index];
}

std::string MultiChoiceQs::getAnswer(int index) const {
    return answers[index];
}

int MultiChoiceQs::getSize() const {
    return size;
}

void MultiChoiceQs::shuffleItems() const {
    std::srand(std::time(nullptr));
    for (int i = 0; i < size; i++) {
        int j = std::rand() % (size - i) + i;
        std::swap(questions[i], questions[j]);
        std::swap(answers[i], answers[j]);
    }
}

void MultiChoiceQs::generateChoices(int index, int num) {
    // Generate choices for the question at index
    // Assume num choices per question (including the correct answer)
    // Randomly choose num-1 incorrect answers from other questions
    int otherIndex;
    choices = new std::string[num];  // dynamically allocate memory for the choices array
    std::string answer = answers[index];

    for (int i = 0; i < num; i++) {
        if (i == 0) {
            choices[i] = answer;  // first choice is always the correct answer
        } else {
            // randomly choose an index from the other questions
            do {
                otherIndex = std::rand() % size;
            } while (otherIndex == index);

            // choose an answer from the other question
            choices[i] = answers[otherIndex];
        }
    }

    // shuffle the choices
    std::random_shuffle(choices, choices + num);

    // store the index of the correct answer
    for (int i = 0; i < num; i++) {
        if (choices[i] == answer) {
            correctIndex = i;
            break;
        }
    }
}

std::string MultiChoiceQs::printQuestion(int index, bool print) const {
    if (print) {
        std::cout << questions[index] << std::endl;
        for (int i = 0; i < 4; i++) {
            std::cout << (char)('A' + i) << ". " << choices[i] << std::endl;
        }
    }
    return questions[index];  // return the question as a string
}

bool MultiChoiceQs::checkAnswer(std::string answer) const {
    return answer == choices[correctIndex];
}

void MultiChoiceQs::askQuestion(int index) {
    std::string answer;
    printQuestion(index, true);
    std::cout << "Enter your answer: ";
    std::cin >> answer;
    answer = toupper(answer[0]);  // convert the answer to uppercase
    if (checkAnswer(choices[answer[0] - 'A'])) {
        std::cout << "Correct!" << std::endl;
    } else {
        std::cout << "Incorrect. The correct answer is " << choices[correctIndex] << std::endl;
    }
}