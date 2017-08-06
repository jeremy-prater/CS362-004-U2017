////////////////////////////////////////////////////////////////////////
//
// Unit Test 2 - Dominion
//
// Test function : int discardCard(int handPos, int currentPlayer, struct gameState *state, int trashFlag)
//
// int handPos = hand Position
// int currentPlayer - Player ID
// struct gameState * state - Pointer to game state
// int trashflag - If < 1, then add to played pile
//
// Return value Always 0
//

#include "../dominion.h"
#include "../dominion_helpers.h"
#include "unittest.h"

static int testPlayer = 0;

static void clearHand(struct gameState * testState)
{
    memset (testState, 0, sizeof (struct gameState));
}

static void addHand(struct gameState * testState, int card)
{
    int handPos = testState->handCount[testPlayer];
    testState->hand[testPlayer][handPos] = card;
    testState->handCount[testPlayer]++;
}

void test_discardCard()
{
    LogStart ("Unit Test: discardCard");
    /////////////////////////////
    //
    // Initalize a gameState for testing.
    //

    struct gameState testState;
    int testPassed = 0;

    /////////////////////////////
    //
    // Test 1 : 1 card in hand
    //
    // Result : No cards left in hand.
    //
    clearHand(&testState);
    addHand(&testState, great_hall);
    discardCard(0, testPlayer, &testState, 1);
    testPassed |= AssertEq (0, testState.handCount[testPlayer], "Test 1 : One card in hand, remove[0]");

    /////////////////////////////
    //
    // Test 1 : 2 cards in hand, remove [0]
    //
    // Result : Card in [1] is now in [0]
    //
    clearHand(&testState);
    addHand(&testState, great_hall);
    addHand(&testState, baron);
    discardCard(0, testPlayer, &testState, 1);
    testPassed |= AssertEq (1, testState.handCount[testPlayer], "Test 2 : Two cards in hand, remove hand[0]");
    testPassed |= AssertEq (baron, testState.hand[testPlayer][0], "Test 2 : baron is in hand[0]");

    /////////////////////////////
    //
    // Test 3 : 2 cards in hand, remove [1]
    //
    // Result : Card in [0] is now in [0]
    //
    clearHand(&testState);
    addHand(&testState, great_hall);
    addHand(&testState, baron);
    discardCard(1, testPlayer, &testState, 1);
    testPassed |= AssertEq (1, testState.handCount[testPlayer], "Test 3 : 2 cards in hand, remove hand[1]");
    testPassed |= AssertEq (great_hall, testState.hand[testPlayer][0], "Test 3 : great_hall is in hand[0]");

    /////////////////////////////
    //
    // Test 4 : 2 cards in hand, play [1]
    //
    // Result : Card in [0] is now in [0]
    //
    clearHand(&testState);
    addHand(&testState, great_hall);
    addHand(&testState, baron);
    discardCard(1, testPlayer, &testState, 0);
    testPassed |= AssertEq (1, testState.handCount[testPlayer], "Test 4 : 2 cards in hand, played hand[1]");
    testPassed |= AssertEq (great_hall, testState.hand[testPlayer][0], "Test 4 : great_hall is in hand[0]");
    testPassed |= AssertEq (1, testState.playedCardCount, "Test 4 : 1 card in played cards");
    testPassed |= AssertEq (baron, testState.playedCards[0], "Test 4 : baron is in playedCards[0]");

   
    AssertEq (0, testPassed, "Unit Test: discardCard\n");
}
