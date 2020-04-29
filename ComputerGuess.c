#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "ComputerGuess.h"

#ifndef COMPUTERGUESS_C
#define COMPUTERGUESS_C


int ComputerGuess(void) {
    static int AnswerBase[10000] = {0};    //This database is to save posible number, by 1 or 0.
    static int CurAnwser = 0;    //Record computer's answer.
    static int CurAnsCnt = 0;    //
    static int ComputerGuessTime = 0;    //Record how many time computer get the answer.

    //Create a database for posible answer.
    static int OneTimeUse = 1;
    //This function only could use one time.
    if (OneTimeUse) {
        BuildAnswerBase(AnswerBase);
        OneTimeUse = 0;
    }

    CurAnwser = RadnPickAnswer(AnswerBase);    //Get a random number from AnswerBase
    printf("The answer is %d?\n", CurAnwser);

    //Filter the imposible answer in AndswerBase.
    int A = 0, B = 0;

    do {
        printf("A=");
        scanf("%d", &A);
        printf("B=");
        scanf("%d", &B);
        if (!CheckAB(Anwswer, CurAnwser, A, B)) {    //Avoid player key in wrong AB.
            printf("Key in wrong ?A?B, pleach re-enter\n");
        }
    } while(!CheckAB(Anwswer, CurAnwser, A, B));

    if (A == 4) {
        ComputerGuessTime++;
        //printf("\nComputer got the answer by %d times!!!\n", ComputerGuessTime);
        return  1;
    }

    CurAnsCnt = FilterImposible(AnswerBase, A, B, CurAnwser);
    //Avoid player key in wrong number an result in delete the real answer.
    if (CurAnsCnt == 0 && (A+B) < 4) {
        printf("You're cheating!!!");
        return  1;
    }

    ComputerGuessTime++;

    return 0;
}


void BuildAnswerBase(int *AnswerBase) {
    int i;
    //int dataNum = 0;
    int D1 = 0, D2 = 0, D3 = 0, D4 = 0;

    for (i =  1023; i <= 9876; i++){    //Pick posible anwser and set flag 1.
        D1 = i / 1000;
        D2 = (i / 100) % 10;
        D3 = (i / 10) % 10;
        D4 = i % 10;
        if (D1 > 0 && D1 != D2 && D1 != D3 && D1 != D4 &&
            D2 != D3 && D2 != D4 && D3 != D4) {
            AnswerBase[i] = 1;
            //dataNum++;
        }
    }

    //printf("Data bumber is %d\n", dataNum);
}

// Use to pick number in AnswerBase.
int RadnPickAnswer(int *AnswerBase) {
    int i = 0;
    int max = 9876, min = 1023;
    srand( time(NULL) );

    do {
        i = rand() % (max - min + 1) + min;
    } while(!AnswerBase[i]);

//    for (i=1023; i <= 9876; i++) {
//        if (AnswerBase[i] == 1) break;
//    }

    return i;
}

int FilterImposible(int *AnswerBase, int A, int B, int CurAnwser) {
    AnswerBase[CurAnwser] = 0;    //Filter the number already guessed.

    char CurAnwserArray[5] = {0}, TempAnwserArray[5] = {0};
    int i, j, k;
    int tempA = 0, tempB = 0;    //To save each temp ?A?B, it compare with CurAnwser.


    sprintf(CurAnwserArray, "%d", CurAnwser);    //Transfer CurAnwser to be a char[];

    //Filter imposible answer on currently posible answer.
    for (i = 1023; i <= 9876 ; i++) {
        sprintf(TempAnwserArray, "%d", i);    //Transfer TempAnwserArray to be a char[];
        tempA = 0;
        tempB = 0;

        if (AnswerBase[i]) {
            //When 0A0B, which number same with any number in CurAnwser isn't posible answer.
            if (A == 0 && B == 0) {
                for (j = 0; j < 4; j++) {
                    for (k = 0; k < 4; k++) {
                        if (CurAnwserArray[j] == TempAnwserArray[k]) {
                            AnswerBase[i] = 0;
                        }
                    }
                }
            }
            //Filter similar number for CurAnwser,
            //if compare with CurAnwser then A+B greater than 1
            //when A+B=1.
            if ((A + B) == 1) {
                tempA = 0;
                tempB = 0;
                for (j = 0; j < 4; j++) {
                    for (k = 0; k < 4; k++) {
                        if (CurAnwserArray[j] == TempAnwserArray[k]) {
                            if (j == k) {
                                tempA++;
                            }
                            else {
                                tempB++;
                            }
                        }
                    }
                }

                //If tempAB != AB, then this number is not a posible answer.
                if ((tempA + tempB) > 1) {
                    AnswerBase[i] = 0;
                }
            }
            //Filter similar number for CurAnwser,
            //if compare with CurAnwser then A+B greater than 2
            //when A+B=2.
            if ((A + B) == 2) {
                tempA = 0;
                tempB = 0;
                for (j = 0; j < 4; j++) {
                    for (k = 0; k < 4; k++) {
                        if (CurAnwserArray[j] == TempAnwserArray[k]) {
                            if (j == k) {
                                tempA++;
                            }
                            else {
                                tempB++;
                            }
                        }
                    }
                }

                //If tempAB != AB, then this number is not a posible answer.
                if ((tempA + tempB) > 2) {
                    AnswerBase[i] = 0;
                }
            }
            if (A == 3) {
                //Compare CurAnwser's every digit with TempAnwserArray
                //then check AB should be 3A0B.
                tempA = 0;
                for (j = 0; j < 4; j++) {
                    for (k = 0; k < 4; k++) {
                        if (CurAnwserArray[j] == TempAnwserArray[k]) {
                            if (j == k) {
                                tempA++;
                            }
                        }
                    }
                }

                //If tempA < A, then this number is not a posible answer.
                if (tempA < A) {
                    AnswerBase[i] = 0;
                }
            }
            //Filter the number which same number count less than 3 with CurAnwser.
            if ((A + B) == 3) {
                int SameCont = 0;

                //Count how many number same with CurAnwser.
                for (j = 0; j < 4; j++) {
                    for (k = 0; k < 4; k++) {
                        if (CurAnwserArray[j] == TempAnwserArray[k]) {
                            SameCont++;
                        }
                    }
                }
                //
                if (SameCont < 3) {
                    AnswerBase[i] = 0;
                }
            }
            //When A+B=4 then filter the number without any number in CurAnwser.
            if ((A + B) == 4) {
                int DiffCont = 0;
                for (j = 0; j < 4; j++) {
                    DiffCont = 0;
                    for (k = 0; k < 4; k++) {
                        if (CurAnwserArray[j] != TempAnwserArray[k]) {
                            DiffCont++;
                        }
                        if (DiffCont == 4) {
                            AnswerBase[i] = 0;
                        }
                    }
                }
            }
            if (AnswerBase[i]) {
                //Compare CurAnwser with TempAnwserArray which is ?A?B.
                //If TempAnwserArray has different ?A?B with CurAnwser then filter that number.
                tempA = 0;
                tempB = 0;
                for (j = 0; j < 4; j++) {
                    for (k = 0; k < 4; k++) {
                        if (CurAnwserArray[j] == TempAnwserArray[k]) {
                            if (j == k) {
                                tempA++;
                            }
                            else {
                                tempB++;
                            }
                        }
                    }
                }

                //If tempAB != AB, then this number is not a posible answer.
                if (tempA != A && tempB != B) {
                    AnswerBase[i] = 0;
                }
            }
        }
    }

    int CurAnsCnt = 0;
    for(i = 1023; i <= 9876 ; i++) {
        if (AnswerBase[i]) CurAnsCnt++;
    }
    //printf("7563=%d\n", AnswerBase[7563]);
    printf("Current posible answer is %d\n", CurAnsCnt);


    return CurAnsCnt;
}

//Use to check correct key in ?A?B for answer.
int CheckAB(int Answer, int CurAnwser, int A, int B) {
    char CurAnwserArray[5] = {0}, AnwserArray[5] = {0};
    int j, k;
    int tempA = 0, tempB = 0;

    sprintf(CurAnwserArray, "%d", CurAnwser);    //Transfer CurAnwser to be a char[];
    sprintf(AnwserArray, "%d", Answer);    //Transfer Answer to be a char[];

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

    int checkEqual=0;
    //If tempAB != AB, then this number is not a posible answer.
    if (tempA != A && tempB != B) {
        checkEqual = 0;
    }
    else if (tempA == A && tempB == B) {
        checkEqual = 1;
    }
    return checkEqual;
}

#endif // COMPUTERGUESS_C
