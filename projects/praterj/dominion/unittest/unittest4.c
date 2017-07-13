////////////////////////////////////////////////////////////////////////
//
// Unit Test 3 - Dominion
//
// Test function : int gainCard(int supplyPos, struct gameState *state, int toFlag, int player)
//
// int supplyPos - enum of chosen card
// int player - Player ID
// struct gameState * state - Pointer to game state
// int toFlag - 0 : add to discard
// int toFlag - 1 : add to deck
// int toFlag - 2 : add to hand
//
// Return value -1 if pile is empty or card is not in game, 0 on success
//