#include "games.h"

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include <cctype>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

// CONFIG
std::string cards[13] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
int maxCards = 10;

// VARIABLES
std::string answer;
std::string DealerCards[10], PlayerCards[10];
int PcardCounter, DcardCounter;
int PcardIndex, DcardIndex;
int PcardValue, DcardValue;
int PcardSum, DcardSum;
int A_OneS, A_ElevenS;
int DA_OneS, DA_ElevenS;
bool Ace, dAce, stand;
bool restart;
int playerMoney = 1000, bet, prize;

// PROTOTYPES
void PcardConverter();
void DcardConverter();

void title();
void DisplayCards();
bool exitPromptHandler(bool, bool);

/**
 * @brief Start Blackjack game
 *
 * @return Error status (int)
 */
int blackjack() {
    while (true) {
        title();
        restart = exitPromptHandler(false, false);
        goto PromptCheck;

    Start:
        title();
        std::cout << "Current money: " << playerMoney << std::endl;
        if (playerMoney == 0) {
            std::cout << "You are now unable to play. Bye!\n";
            return 0;
        }
        std::cout << "How much do you want to bet? ";
        std::cin >> bet;

        if (bet > playerMoney) {
            std::cout << "You don't have that much money.";
            clrscr();
        } else {
            playerMoney -= bet;

            std::cout << "\nThe Dealer is dealing";
            for (int i = 1; i <= 3; i++) {
                std::cout.flush();
                Sleep(1000);
                std::cout << ".";
            }
            clrscr();
            title();

            srand(time(0));

            int randomCard;
            A_OneS = 0, A_ElevenS = 0;
            DA_OneS = 0, DA_ElevenS = 0;
            PcardSum = 0, DcardSum = 0;
            PcardCounter = 2, DcardCounter = 2;
            Ace = false, dAce = false;

            for (DcardIndex = 0; DcardIndex < DcardCounter; DcardIndex++) {
                randomCard = rand() % 13;
                DealerCards[DcardIndex] = cards[randomCard];
                if (dAce == false) {
                    DcardValue = 0;
                    DcardConverter();
                    DcardSum += DcardValue;
                    if (DealerCards[DcardIndex] == "A") {
                        dAce = true;
                        DA_OneS = DcardSum + 1;
                        DA_ElevenS = DcardSum + 11;
                    }
                } else {
                    if (DealerCards[DcardIndex] == "A") {
                        DA_ElevenS = DA_OneS + 11;
                        DA_OneS += 1;
                    } else {
                        DcardValue = 0;
                        DcardConverter();
                        DA_OneS += DcardValue;
                        DA_ElevenS += DcardValue;
                    }
                }
            }
            for (PcardIndex = 0; PcardIndex < PcardCounter; PcardIndex++) {
                randomCard = rand() % 13;
                PlayerCards[PcardIndex] = cards[randomCard];
                if (Ace == false) {
                    PcardValue = 0;
                    PcardConverter();
                    PcardSum += PcardValue;
                    if (PlayerCards[PcardIndex] == "A") {
                        Ace = true;
                        A_OneS = PcardSum + 1;
                        A_ElevenS = PcardSum + 11;
                    }
                } else {
                    if (PlayerCards[PcardIndex] == "A") {
                        A_ElevenS = A_OneS + 11;
                        A_OneS += 1;
                    } else {
                        PcardValue = 0;
                        PcardConverter();
                        A_OneS += PcardValue;
                        A_ElevenS += PcardValue;
                    }
                }
            }

            // std::cout << "\n\n";
            DisplayCards();

            /////* Auto Win Checker */////
            if (PlayerCards[0] == "A" && (PlayerCards[1] == "10" || PlayerCards[1] == "J" || PlayerCards[1] == "Q" || PlayerCards[1] == "K") || PlayerCards[1] == "A" && (PlayerCards[0] == "10" || PlayerCards[0] == "J" || PlayerCards[0] == "Q" || PlayerCards[0] == "K")) {
                prize = bet * 1.5;
                playerMoney += prize;
                std::cout << "\n\nBLACKJACK! You won " << prize << "! You now have " << playerMoney << "\n\n";

                restart = exitPromptHandler(true, true);
                goto PromptCheck;
            }

        /////* Hit or Stand */////
        HITorSTAND:
            answer = stringPrompt("Hit or Stand? ", true);

            if (answer == "hit") {
                PcardCounter++;
                randomCard = rand() % 13;
                PlayerCards[PcardIndex] = cards[randomCard];
                if (Ace == false) {
                    PcardValue = 0;
                    PcardConverter();
                    PcardSum += PcardValue;
                    if (PlayerCards[PcardIndex] == "A") {
                        Ace = true;
                        A_OneS = PcardSum + 1;
                        A_ElevenS = PcardSum + 11;
                    }
                } else {
                    if (PlayerCards[PcardIndex] == "A") {
                        A_ElevenS = A_OneS + 11;
                        A_OneS += 1;
                    } else {
                        PcardValue = 0;
                        PcardConverter();
                        A_OneS += PcardValue;
                        A_ElevenS += PcardValue;
                    }
                }

                PcardIndex++;

                clrscr();
                title();
                DisplayCards();

                ///// WIN or LOSE Checker /////
                if (Ace == false) {
                    if (PcardSum == 21) {
                        prize = bet * 1.5;
                        playerMoney += prize;
                        std::cout << "BLACKJACK! You won " << prize << "! You now have " << playerMoney << "\n\n";

                        restart = exitPromptHandler(true, true);
                        goto PromptCheck;
                    } else if (PcardSum > 21) {
                        std::cout << "Your cards are greater than 21. You lose!\n\n";

                        restart = exitPromptHandler(false, true);
                        goto PromptCheck;
                    }
                } else  // Ace == true
                {
                    if (A_OneS == 21 || A_ElevenS == 21) {
                        prize = bet * 1.5;
                        playerMoney += prize;
                        std::cout << "BLACKJACK! You won " << prize << "! You now have " << playerMoney << "\n\n";

                        restart = exitPromptHandler(true, true);
                        goto PromptCheck;
                    } else if (A_OneS > 21) {
                        std::cout << "Your cards are greater than 21. You lose!\n\n";

                        restart = exitPromptHandler(false, true);
                        goto PromptCheck;
                    }
                }

                goto HITorSTAND;
            } else if (answer == "stand") {
                stand = true;
                clrscr();
                title();
                DisplayCards();

            STAND:
                if (dAce == false) {
                    if (DcardSum >= 17) {
                        // Dealer Auto Win or Lose
                        if (DcardSum == 21) {
                            std::cout << "BLACKJACK for the Dealer! You lose.\n";

                            restart = exitPromptHandler(false, true);
                            goto PromptCheck;
                        } else if (DcardSum > 21) {
                            prize = bet * 1.5;
                            playerMoney += prize;
                            std::cout << "The Dealer is busted. You win!\n";
                            std::cout << "You won " << prize << "! You now have " << playerMoney << "\n\n";

                            restart = exitPromptHandler(true, true);
                            goto PromptCheck;
                        } else if (Ace == false) {
                            if (PcardSum > DcardSum) {
                                prize = bet * 1.5;
                                playerMoney += prize;
                                std::cout << "You beat the Dealer. You win!\n";
                                std::cout << "You won " << prize << "! You now have " << playerMoney << "\n\n";

                                restart = exitPromptHandler(true, true);
                                goto PromptCheck;
                            } else if (PcardSum < DcardSum) {
                                std::cout << "The Dealer beat you. You lose!\n";

                                restart = exitPromptHandler(false, true);
                                goto PromptCheck;
                            } else {
                                playerMoney += bet;
                                std::cout << "It's a tie! Your bet is returned to you.\n";

                                restart = exitPromptHandler(false, true);
                                goto PromptCheck;
                            }
                        } else if (Ace == true) {
                            if (A_ElevenS < 22 && A_ElevenS > DcardSum) {
                                prize = bet * 1.5;
                                playerMoney += prize;
                                std::cout << "You beat the Dealer. You win!\n";
                                std::cout << "You won " << prize << "! You now have " << playerMoney << "\n\n";

                                restart = exitPromptHandler(true, true);
                                goto PromptCheck;
                            } else if (A_OneS < 22 && A_OneS > DcardSum) {
                                prize = bet * 1.5;
                                playerMoney += prize;
                                std::cout << "You beat the Dealer. You win!\n";
                                std::cout << "You won " << prize << "! You now have " << playerMoney << "\n\n";

                                restart = exitPromptHandler(true, true);
                                goto PromptCheck;
                            } else if (A_ElevenS < 22 && A_ElevenS < DcardSum) {
                                std::cout << "The Dealer beat you. You lose!\n";

                                restart = exitPromptHandler(false, true);
                                goto PromptCheck;
                            } else if (A_OneS < 22 && A_OneS < DcardSum) {
                                std::cout << "The Dealer beat you. You lose!\n";

                                restart = exitPromptHandler(false, true);
                                goto PromptCheck;
                            } else if (A_ElevenS < 22 && A_ElevenS == DcardSum) {
                                playerMoney += bet;
                                std::cout << "It's a tie! Your bet is returned to you.\n";

                                restart = exitPromptHandler(false, true);
                                goto PromptCheck;
                            } else if (A_OneS < 22 && A_OneS == DcardSum) {
                                playerMoney += bet;
                                std::cout << "It's a tie! Your bet is returned to you.\n";

                                restart = exitPromptHandler(false, true);
                                goto PromptCheck;
                            }
                        }
                    } else  // DcardSum < 17
                    {
                        DcardCounter++;
                        randomCard = rand() % 13;
                        DealerCards[DcardIndex] = cards[randomCard];
                        DcardValue = 0;
                        DcardConverter();
                        DcardSum += DcardValue;
                        if (DealerCards[DcardIndex] == "A") {
                            dAce = true;
                            DA_OneS = DcardSum + 1;
                            DA_ElevenS = DcardSum + 11;
                        }

                        DcardIndex++;
                        clrscr();
                        title();
                        DisplayCards();
                        goto STAND;
                    }
                } else  // dAce == true
                {
                    if (DA_OneS >= 17 || DA_ElevenS >= 17) {
                        // Dealer Auto Win or Lose
                        if (DA_OneS == 21 || DA_ElevenS == 21) {
                            std::cout << "BLACKJACK for the Dealer! You lose.\n";

                            restart = exitPromptHandler(false, true);
                            goto PromptCheck;
                        } else if (DA_OneS > 21) {
                            prize = bet * 1.5;
                            playerMoney += prize;
                            std::cout << "The Dealer is busted. You win!\n";
                            std::cout << "You won " << prize << "! You now have " << playerMoney << "\n\n";

                            restart = exitPromptHandler(true, true);
                            goto PromptCheck;
                        } else if (Ace == false) {
                            if (DA_ElevenS < 22 && PcardSum > DA_ElevenS) {
                                prize = bet * 1.5;
                                playerMoney += prize;
                                std::cout << "You beat the Dealer. You win!\n";
                                std::cout << "You won " << prize << "! You now have " << playerMoney << "\n\n";

                                restart = exitPromptHandler(true, true);
                                goto PromptCheck;
                            } else if (DA_ElevenS < 22 && PcardSum < DA_ElevenS) {
                                std::cout << "The Dealer beat you. You lose!\n";

                                restart = exitPromptHandler(false, true);
                                goto PromptCheck;
                            } else if (DA_ElevenS < 22 && PcardSum == DA_ElevenS) {
                                playerMoney += bet;
                                std::cout << "It's a tie! Your bet is returned to you.\n";

                                restart = exitPromptHandler(false, true);
                                goto PromptCheck;
                            } else if (DA_OneS < 22 && PcardSum > DA_OneS) {
                                prize = bet * 1.5;
                                playerMoney += prize;
                                std::cout << "You beat the Dealer. You win!\n";
                                std::cout << "You won " << prize << "! You now have " << playerMoney << "\n\n";

                                restart = exitPromptHandler(true, true);
                                goto PromptCheck;
                            } else if (DA_OneS < 22 && PcardSum < DA_OneS) {
                                std::cout << "The Dealer beat you. You lose!\n";

                                restart = exitPromptHandler(false, true);
                                goto PromptCheck;
                            } else if (DA_OneS < 22 && PcardSum == DA_OneS) {
                                playerMoney += bet;
                                std::cout << "It's a tie! Your bet is returned to you.\n";

                                restart = exitPromptHandler(false, true);
                                goto PromptCheck;
                            }
                        } else if (Ace == true) {
                            if (DA_ElevenS < 22 && A_ElevenS < 22 && A_ElevenS > DA_ElevenS) {
                                prize = bet * 1.5;
                                playerMoney += prize;
                                std::cout << "You beat the Dealer. You win!\n";
                                std::cout << "You won " << prize << "! You now have " << playerMoney << "\n\n";

                                restart = exitPromptHandler(true, true);
                                goto PromptCheck;
                            } else if (DA_ElevenS < 22 && A_ElevenS < 22 && A_ElevenS < DA_ElevenS) {
                                std::cout << "The Dealer beat you. You lose!\n";

                                restart = exitPromptHandler(false, true);
                                goto PromptCheck;
                            } else if (DA_ElevenS < 22 && A_ElevenS < 22 && A_ElevenS == DA_ElevenS) {
                                playerMoney += bet;
                                std::cout << "It's a tie! Your bet is returned to you.\n";

                                restart = exitPromptHandler(false, true);
                                goto PromptCheck;
                            }
                            if (DA_ElevenS < 22 && A_OneS < 22 && A_OneS > DA_ElevenS) {
                                prize = bet * 1.5;
                                playerMoney += prize;
                                std::cout << "You beat the Dealer. You win!\n";
                                std::cout << "You won " << prize << "! You now have " << playerMoney << "\n\n";

                                restart = exitPromptHandler(true, true);
                                goto PromptCheck;
                            } else if (DA_ElevenS < 22 && A_OneS < 22 && A_OneS < DA_ElevenS) {
                                std::cout << "The Dealer beat you. You lose!\n";

                                restart = exitPromptHandler(false, true);
                                goto PromptCheck;
                            } else if (DA_ElevenS < 22 && A_OneS < 22 && A_OneS == DA_ElevenS) {
                                playerMoney += bet;
                                std::cout << "It's a tie! Your bet is returned to you.\n";

                                restart = exitPromptHandler(false, true);
                                goto PromptCheck;
                            }
                            if (DA_OneS < 22 && A_ElevenS < 22 && A_ElevenS > DA_OneS) {
                                prize = bet * 1.5;
                                playerMoney += prize;
                                std::cout << "You beat the Dealer. You win!\n";
                                std::cout << "You won " << prize << "! You now have " << playerMoney << "\n\n";

                                restart = exitPromptHandler(true, true);
                                goto PromptCheck;
                            } else if (DA_OneS < 22 && A_ElevenS < 22 && A_ElevenS < DA_OneS) {
                                std::cout << "The Dealer beat you. You lose!\n";

                                restart = exitPromptHandler(false, true);
                                goto PromptCheck;
                            } else if (DA_OneS < 22 && A_ElevenS < 22 && A_ElevenS == DA_OneS) {
                                playerMoney += bet;
                                std::cout << "It's a tie! Your bet is returned to you.\n";

                                restart = exitPromptHandler(false, true);
                                goto PromptCheck;
                            }
                            if (DA_OneS < 22 && A_OneS < 22 && A_OneS > DA_OneS) {
                                prize = bet * 1.5;
                                playerMoney += prize;
                                std::cout << "You beat the Dealer. You win!\n";
                                std::cout << "You won " << prize << "! You now have " << playerMoney << "\n\n";

                                restart = exitPromptHandler(true, true);
                                goto PromptCheck;
                            } else if (DA_OneS < 22 && A_OneS < 22 && A_OneS < DA_OneS) {
                                std::cout << "The Dealer beat you. You lose!\n";

                                restart = exitPromptHandler(false, true);
                                goto PromptCheck;
                            } else if (DA_OneS < 22 && A_OneS < 22 && A_OneS == DA_OneS) {
                                playerMoney += bet;
                                std::cout << "It's a tie! Your bet is returned to you.\n";

                                restart = exitPromptHandler(false, true);
                                goto PromptCheck;
                            }
                        }
                    } else  // DA_OneS < 17 || DA_ElevenS < 17
                    {
                        DcardCounter++;
                        randomCard = rand() % 13;
                        DealerCards[DcardIndex] = cards[randomCard];
                        if (DealerCards[DcardIndex] == "A") {
                            DA_ElevenS = DA_OneS + 11;
                            DA_OneS += 1;
                        } else {
                            DcardValue = 0;
                            DcardConverter();
                            DA_OneS += DcardValue;
                            DA_ElevenS += DcardValue;
                        }

                        DcardIndex++;
                        clrscr();
                        title();
                        DisplayCards();
                        goto STAND;
                    }
                }
            } else {
                std::cout << "I didn't catch that. ";
                goto HITorSTAND;
            }
        }
    }

PromptCheck:
    if (restart) {
        stand = false;
        clrscr();
        goto Start;
    } else {
        std::cout << "\nBye!";
        return 0;
    }
}

// SYSTEM FUNCTIONS

void title() {
    std::cout << "----------------------------" << std::endl;
    std::cout << "    Welcome to Blackjack    " << std::endl;
    std::cout << "----------------------------" << std::endl
              << std::endl;
}

// Use this for restart / exit  check only
bool exitPromptHandler(bool win, bool gameEnded) {
    std::string message;
    if (gameEnded)
        switch (win) {
            case true:
                message = "Do you like to play again? ";
                break;
            case false:
                message = "Would you like to try again? ";
                break;
        }
    else
        message = "Would you like to play? ";

    answer = stringPrompt(message, true);

    const std::string arrTrue[] = {"yes", "y", "naur", "yeah", "yep"};  // Responses for true
    const std::string arrFalse[] = {"no", "n", "naur", "nah", "nope"};  // Responses for false
    const int numArrTrue = sizeof(arrTrue) / sizeof(arrTrue[0]);        // Number of elements in array
    const int numArrFalse = sizeof(arrFalse) / sizeof(arrFalse[0]);     // Number of elements in array

    if (numArrTrue == numArrFalse) {
        for (int i = 0; i < numArrTrue; i++)  // Computing shortcut
            if (answer == arrTrue[i])
                return true;
            else if (answer == arrFalse[i])
                return false;
    } else {
        for (int i = 0; i < numArrTrue; i++)  // Long version
            if (answer == arrTrue[i])
                return true;

        for (int i = 0; i < numArrFalse; i++)
            if (answer == arrFalse[i])
                return false;
    }

    message = "I didn't catch that. " + message;
    return exitPromptHandler(win, gameEnded);
}

// GAME FUNCTIONS

void DisplayCards() {
    std::cout << "Dealer's cards:\n\n";
    if (stand == false) {
        std::cout << "|" << DealerCards[0] << "| |?|\n\n";
    } else {
        for (int m = 0; m < DcardCounter; m++) {
            std::cout << "|" << DealerCards[m] << "| ";
        }
        std::cout << "\n\n";
    }

    std::cout << "Dealer's card count: ";
    if (stand == false) {
        std::cout << DcardSum - DcardValue << "+\n\n";
    } else {
        if (dAce == false) {
            std::cout << DcardSum << "\n\n";
        } else {
            std::cout << DA_OneS;
            if (DA_ElevenS <= 21) {
                std::cout << " or " << DA_ElevenS << "\n\n";
            } else {
                std::cout << "\n\n";
            }
        }
    }

    std::cout << "Your cards:\n\n";
    for (int n = 0; n < PcardCounter; n++) {
        std::cout << "|" << PlayerCards[n] << "| ";
    }
    std::cout << "\n\n";

    std::cout << "Your card count: ";
    if (Ace == false) {
        std::cout << PcardSum << "\n\n";
    } else {
        std::cout << A_OneS;
        if (A_ElevenS <= 21) {
            std::cout << " or " << A_ElevenS << "\n\n";
        } else {
            std::cout << "\n\n";
        }
    }
}

void PcardConverter() {
    if (PlayerCards[PcardIndex] == "2") {
        PcardValue = 2;
    } else if (PlayerCards[PcardIndex] == "3") {
        PcardValue = 3;
    } else if (PlayerCards[PcardIndex] == "4") {
        PcardValue = 4;
    } else if (PlayerCards[PcardIndex] == "5") {
        PcardValue = 5;
    } else if (PlayerCards[PcardIndex] == "6") {
        PcardValue = 6;
    } else if (PlayerCards[PcardIndex] == "7") {
        PcardValue = 7;
    } else if (PlayerCards[PcardIndex] == "8") {
        PcardValue = 8;
    } else if (PlayerCards[PcardIndex] == "9") {
        PcardValue = 9;
    } else if (PlayerCards[PcardIndex] == "10" || PlayerCards[PcardIndex] == "J" || PlayerCards[PcardIndex] == "Q" || PlayerCards[PcardIndex] == "K") {
        PcardValue = 10;
    }
}

void DcardConverter() {
    if (DealerCards[DcardIndex] == "2") {
        DcardValue = 2;
    } else if (DealerCards[DcardIndex] == "3") {
        DcardValue = 3;
    } else if (DealerCards[DcardIndex] == "4") {
        DcardValue = 4;
    } else if (DealerCards[DcardIndex] == "5") {
        DcardValue = 5;
    } else if (DealerCards[DcardIndex] == "6") {
        DcardValue = 6;
    } else if (DealerCards[DcardIndex] == "7") {
        DcardValue = 7;
    } else if (DealerCards[DcardIndex] == "8") {
        DcardValue = 8;
    } else if (DealerCards[DcardIndex] == "9") {
        DcardValue = 9;
    } else if (DealerCards[DcardIndex] == "10" || DealerCards[DcardIndex] == "J" || DealerCards[DcardIndex] == "Q" || DealerCards[DcardIndex] == "K") {
        DcardValue = 10;
    }
}