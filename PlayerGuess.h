#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#ifndef PLAYERGUESS_H
#define PLAYERGUESS_H

int RadnPicComputerkAnswer(void);
int CheckPlayerAnswer(int Answer, int CurAnwser);
int PlayerGuess(void);

#endif // PLAYERGUESS_H
