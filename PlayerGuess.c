#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "PlayerGuess.h"

// Use to pick number in AnswerBase.
int RadnPicComputerkAnswer(void) {
    int RandomAnswer = 0;
    int max = 9876, min = 1023;
    char RandomAnswerArray[5] = {0};
    srand( time(NULL) );

    while (1) {
        RandomAnswer = rand() % (max - min + 1) + min;
        sprintf(RandomAnswerArray, "%d", RandomAnswer);    //Transfer CurAnwser to be a char[];

        if (RandomAnswerArray[0] != RandomAnswerArray[1] && RandomAnswerArray[0] != RandomAnswerArray[2] &&
            RandomAnswerArray[0] != RandomAnswerArray[3] && RandomAnswerArray[1] != RandomAnswerArray[2] &&
            RandomAnswerArray[1] != RandomAnswerArray[3] && RandomAnswerArray[2] != RandomAnswerArray[3] &&
            RandomAnswerArray[2] != RandomAnswerArray[4] && RandomAnswerArray[3] != RandomAnswerArray[4]) {
            break;
        }
    }

    printf("\nComputer's answer is \"%d\"\n", RandomAnswer);
    return RandomAnswer;
}

//Use to check correct key in ?A?B for answer.
int CheckPlayerAnswer(int Answer, int CurAnwser) {
    char CurAnwserArray[5] = {0}, AnwserArray[5] = {0};
    int j, k;
    int tempA = 0, tempB = 0;

    sprintf(CurAnwserArray, "%d", CurAnwser);    //Transfer CurAnwser to be a char[];
    sprintf(AnwserArray, "%d", Answer);    //Transfer Answer to be a char[];

    //Count player's answer is ?A?B.
    for (j = 0; j < 4; j++) {
        for (k = 0; k < 4; k++) {
            if (CurAnwserArray[j] == AnwserArray[k]) {
                if (j == k) {
                    tempA++;
                }
                else {
                    tempB++;
                }
            }
        }
    }

    printf("Your answer is %dA%dB.\n", tempA, tempB);

    int checkEqual=0;

    if (tempA == 4 && tempB == 0) {
        checkEqual = 1;
    }
    else {
        checkEqual = 0;
    }
    return checkEqual;
}

//Use to control whole player game's function.
int PlayerGuess(void) {
    static int FirstTimeUse = 1;
    static int ComputersAnswer = 0;
    int PlayersAnswer = 0;
    int RightAswr = 0;

    if (FirstTimeUse) {
        ComputersAnswer = RadnPicComputerkAnswer();
        FirstTimeUse = 0;
    }

    printf("Please key in your answer:");
    scanf("%d", &PlayersAnswer);

    RightAswr = CheckPlayerAnswer(ComputersAnswer, PlayersAnswer);

    return RightAswr;
}
