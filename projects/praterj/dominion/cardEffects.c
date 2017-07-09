#include "cardEffects.h"
#include "dominion_helpers.h"
#include <stdio.h>

int cardEffect_Adventurer(int *drawntreasure, struct gameState *state,
                          int *currentPlayer, int *cardDrawn, int *temphand,
                          int *z) {
  while (*drawntreasure < 2) {
    if (state->deckCount[*currentPlayer] < 1) { // if the deck is empty we need
                                                // to shuffle discard and add
                                                // to deck
      shuffle(*currentPlayer, state);
    }
    drawCard(*currentPlayer, state);
    *cardDrawn =
        state->hand[*currentPlayer]
                   // [state->handCount[*currentPlayer] - 1]; // top card of hand is most recently drawn card.
                   // Error 1 : Remove index offset (-1)
                   [state->handCount[*currentPlayer]]; // top card of hand is most recently drawn card.
    if (*cardDrawn == copper || *cardDrawn == silver || *cardDrawn == gold)
      drawntreasure++;
    else {
      temphand[*z] = *cardDrawn;
      state->handCount[*currentPlayer]--; // this should just remove the top
                                          // card (the most recently drawn
                                          // one).
      (*z)++;
    }
  }
  while (*z - 1 >= 0) {
    state->discard[*currentPlayer][state->discardCount[*currentPlayer]++] =
        temphand[*z - 1]; // discard all cards in play that have been drawn
    *z = *z - 1;
  }
  return 0;
}

int cardEffect_Smithy(int *currentPlayer, struct gameState *state,
                      int *handPos) {
  int i;
  //+3 Cards
  for (i = 0; i < 3; i++) {
    drawCard(*currentPlayer, state);
  }

  // discard card from hand
  discardCard(*handPos, *currentPlayer, state, 0);

  return 0;
}

int cardEffect_CouncilRoom(int *currentPlayer, struct gameState *state,
                           int *handPos) {
  int i;
  //+4 Cards
  for (i = 0; i < 4; i++) {
    drawCard(*currentPlayer, state);
  }

  //+1 Buy
  state->numBuys++;

  // Each other player draws a card
  for (i = 0; i < state->numPlayers; i++) {
    if (i != *currentPlayer) {
      drawCard(i, state);
    }
  }

  // put played card in played card pile
  discardCard(*handPos, *currentPlayer, state, 0);

  return 0;
}

int cardEffect_Feast(int *currentPlayer, struct gameState *state, int *handPos,
                     int *temphand, int *choice1, int *x) {
  int i;
  // gain card with cost up to 5
  // Backup hand
  for (i = 0; i <= state->handCount[*currentPlayer]; i++) {
    temphand[i] = state->hand[*currentPlayer][i]; // Backup card
    state->hand[*currentPlayer][i] = -1;          // Set to nothing
  }
  // Backup hand

  // Update Coins for Buy
  updateCoins(*currentPlayer, state, 5);
  *x = 1;           // Condition to loop on
  while (*x == 1) { // Buy one card
    if (supplyCount(*choice1, state) <= 0) {
      if (DEBUG)
        printf("None of that card left, sorry!\n");

      if (DEBUG) {
        printf("Cards Left: %d\n", supplyCount(*choice1, state));
      }
    } else if (state->coins < getCost(*choice1)) {
      printf("That card is too expensive!\n");

      if (DEBUG) {
        printf("Coins: %d < %d\n", state->coins, getCost(*choice1));
      }
    } else {

      if (DEBUG) {
        printf("Deck Count: %d\n",
               state->handCount[*currentPlayer] +
                   state->deckCount[*currentPlayer] +
                   state->discardCount[*currentPlayer]);
      }

      gainCard(*choice1, state, 0, *currentPlayer); // Gain the card
      *x = 0;                                       // No more buying cards

      if (DEBUG) {
        printf("Deck Count: %d\n",
               state->handCount[*currentPlayer] +
                   state->deckCount[*currentPlayer] +
                   state->discardCount[*currentPlayer]);
      }
    }
  }

  // Reset Hand
  for (i = 0; i <= state->handCount[*currentPlayer]; i++) {
    state->hand[*currentPlayer][i] = temphand[i];
    temphand[i] = -1;
  }
  // Reset Hand

  return 0;
}

int cardEffect_Mine(int *currentPlayer, struct gameState *state, int *handPos,
                    int *choice1, int *choice2) {
  int i;
  int j = state->hand[*currentPlayer][*choice1]; // store card we will trash

  if (state->hand[*currentPlayer][*choice1] < copper ||
      state->hand[*currentPlayer][*choice1] > gold) {
    return -1;
  }

  if (*choice2 > treasure_map || *choice2 < curse) {
    return -1;
  }

  if ((getCost(state->hand[*currentPlayer][*choice1]) + 3) >
      getCost(*choice2)) {
    return -1;
  }

  gainCard(*choice2, state, 2, *currentPlayer);

  // discard card from hand
  discardCard(*handPos, *currentPlayer, state, 0);

  // discard trashed card
  for (i = 0; i < state->handCount[*currentPlayer]; i++) {
    if (state->hand[*currentPlayer][i] == j) {
      discardCard(i, *currentPlayer, state, 0);
      break;
    }
  }

  return 0;
}