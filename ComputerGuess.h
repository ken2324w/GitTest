#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#ifndef COMPUTERGUESS_H
#define COMPUTERGUESS_H

void BuildAnswerBase(int *AnswerBase);
int RadnPickAnswer(int *AnswerBase);
int FilterImposible(int *AnswerBase, int A, int B, int CurAnwser);
int CheckAB(int Answer, int CurAnwser, int A, int B);
int ComputerGuess(void);

extern int Anwswer;

#endif // COMPUTERGUESS_H
