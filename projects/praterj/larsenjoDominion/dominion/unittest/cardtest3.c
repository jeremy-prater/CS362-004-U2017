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

static void addDeck(struct gameState * testState, int card, int player)
{
    int deckPos = testState->deckCount[player];
    testState->deck[player][deckPos] = card;
    testState->deckCount[player]++;
}

void test_cardCouncilRoom()
{
    LogStart ("Unit Test: test_cardCouncilRoom");

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
    addHand(&testState, adventurer);
    addHand(&testState, council_room);

    int cardIndex;
    for (cardIndex = 0; cardIndex < 4; cardIndex++)
    {
        addDeck(&testState, cardIndex, testPlayer);
        addDeck(&testState, cardIndex, testPlayer + 1);
        addDeck(&testState, cardIndex, testPlayer + 2);
    }

    testState.numPlayers = 3;
    int handPos = 1;

    int oldBuys = testState.numBuys;

    cardEffect_CouncilRoom(&testPlayer, &testState, &handPos);

    testPassed |= AssertEq (oldBuys + 1, testState.numBuys, "Test 1 : numBuys++");
    testPassed |= AssertEq (5, testState.handCount[testPlayer], "Test 1 : handCount == 5");
    testPassed |= AssertEq (adventurer, testState.hand[testPlayer][0], "Test 1 : hand[0] == adventurer");
    testPassed |= AssertEq (0, testState.hand[testPlayer][1], "Test 1 : hand[1] == 0");
    testPassed |= AssertEq (3, testState.hand[testPlayer][2], "Test 1 : hand[2] == 3");
    testPassed |= AssertEq (2, testState.hand[testPlayer][3], "Test 1 : hand[3] == 2");
    testPassed |= AssertEq (1, testState.hand[testPlayer][4], "Test 1 : hand[4] == 1");

    
    testPassed |= AssertEq (1, testState.handCount[testPlayer+1], "Test 1 : handCount[player1] == 1");
    testPassed |= AssertEq (3, testState.hand[testPlayer+1][0], "Test 1 : hand[player1][0] == 3");

    testPassed |= AssertEq (1, testState.handCount[testPlayer+2], "Test 1 : handCount[player2] == 1");
    testPassed |= AssertEq (3, testState.hand[testPlayer+2][0], "Test 1 : hand[player2][0] == 3");
    
    AssertEq (0, testPassed, "Unit Test: test_cardCouncilRoom\n");
}
