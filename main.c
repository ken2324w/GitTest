#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "ComputerGuess.h"
#include "PlayerGuess.h"


int Anwswer = 0;


int main()
{
    int PlayerWin = 0;
    int ComputerWin = 0;
    printf("Please enter your answer to prevent key in wrong ?A?B\n");
    scanf("%d", &Anwswer);
    //int ComputerAndUser = 1;    //1 is computer's turn, -1 is user's turn.
    int PlayRound = 0;

    while (1) {
        PlayRound++;    //Count how many round this game's duration.

        printf("\nComputer's turn.\n");
        ComputerWin = ComputerGuess();
        if (ComputerWin) {
            printf("Winner is Computer by %d times!!!\n", PlayRound);
            break;
        }

        printf("\nYour turn.\n");
        PlayerWin = PlayerGuess();
        if (PlayerWin) {
            printf("Winner is User by %d times!!!\n", PlayRound);
            break;
        }

        //ComputerAndUser *= (-1);

    }

    return 0;
}


