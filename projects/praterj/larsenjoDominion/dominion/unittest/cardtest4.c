////////////////////////////////////////////////////////////////////////
//
// Card Test 3 - Dominion - cardEffect_CouncilRoom
//
// Test function : int cardEffect_CouncilRoom(int *currentPlayer, struct gameState *state, int *handPos)
//
// int * currentPlayer - Player ID
// struct gameState * state - Pointer to game state
// int * handPos - hand position to discard
//

#include "../dominion.h"
#include "../dominion_helpers.h"
#include "unittest.h"

static int testPlayer = 0;

static void clearState(struct gameState * testState)
{
    memset (testState, 0, sizeof (struct gameState));
}

static void addHand(struct gameState * testState, int card)
{
    int handPos = testState->handCount[testPlayer];
    testState->hand[testPlayer][handPos] = card;
    testState->handCount[testPlayer]++;
}

static void addSupply(struct gameState * testState, int card)
{
    testState->supplyCount[card]++;
}

void test_cardFeast()
{
    LogStart ("Unit Test: test_cardFeast");

    /////////////////////////////
    //
    // Initalize a gameState for testing.
    //

    struct gameState testState;
    int testPassed = 0;

    /////////////////////////////
    //
    // Test 1 : Add 4 cards to deck, add 3 cards to hand, execute adventurer
    //
    clearState (&testState);
    addHand(&testState, copper);
    //addSupply(&testState, duchy);
    addSupply(&testState, province);
 
    int handPos = 1;

    int cardDuchy = duchy;
    int cardProvince = province;

    // These should be internal to cardEffect_Feast
    int tempHand[MAX_HAND];
    int x = 0;

    //cardEffect_Feast(&testPlayer, &testState, &handPos, tempHand, &cardProvince, &x);

    testPassed |= AssertEq (5, testState.coins, "Test 1 : coins == 5");
    testPassed |= AssertEq (1, testState.handCount[testPlayer], "Test 1 : handCount[player] == 1");
    testPassed |= AssertEq (copper, testState.hand[testPlayer][0], "Test 1 : hand[player][0] == copper");

    //cardEffect_Feast(&testPlayer, &testState, &handPos, tempHand, &cardDuchy, &x);

    testPassed |= AssertEq (1, testState.handCount[testPlayer], "Test 2 : handCount[player] == 1");
    testPassed |= AssertEq (copper, testState.hand[testPlayer][0], "Test 2 : hand[player][0] == copper");
    
    addSupply(&testState, duchy);

    //cardEffect_Feast(&testPlayer, &testState, &handPos, tempHand, &cardDuchy, &x);

    testPassed |= AssertEq (2, testState.handCount[testPlayer], "Test 3 : handCount[player] == 2");
    testPassed |= AssertEq (copper, testState.hand[testPlayer][0], "Test 3 : hand[player][0] == copper");
    testPassed |= AssertEq (duchy, testState.hand[testPlayer][1], "Test 3 : hand[player][1] == duchy");

    AssertEq (0, testPassed, "Unit Test: test_cardFeast\n");
}
