#include "dominion.h"

int cardEffect_Adventurer(int *drawntreasure, struct gameState *state,
                          int *currentPlayer, int *cardDrawn, int *temphand,
                          int *z);

int cardEffect_Smithy(int *currentPlayer, struct gameState *state,
                      int *handPos);

int cardEffect_Feast(int *currentPlayer, struct gameState *state, int *handPos,
                     int *temphand, int *choice1, int *x);

int cardEffect_CouncilRoom(int *currentPlayer, struct gameState *state,
                           int *handPos);

int cardEffect_Mine(int *currentPlayer, struct gameState *state, int *handPos,
                    int *choice1, int *choice2);