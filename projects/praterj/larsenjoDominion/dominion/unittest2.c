/*
 * unittest2.c
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{

/*
int supplyCount(int card, struct gameState *state) 
  return state->supplyCount[card];
*/
  
struct gameState* g = malloc(sizeof(struct gameState));
printf("********Testing supplyCount()********\n");

g->supplyCount[estate] = 1;
g->supplyCount[mine] = 2;
g->supplyCount[minion] = 500;
g->supplyCount[treasure_map] = -1;
g->supplyCount[treasure_map+2] = 1;

if(supplyCount(estate, g) == 1)
    printf("Test 1 passed\n");
else
    printf("Test 1 failed\n");

if(supplyCount(mine, g) == 2)
    printf("Test 2 passed\n");
else
    printf("Test 2 failed\n");

if(supplyCount(minion, g) == 500)
    printf("Test 3 passed\n");
else
    printf("Test 3 failed\n");

if(supplyCount(treasure_map, g) == -1)
    printf("Test 4 passed\n");
else
    printf("Test 4 failed\n");

if(supplyCount(treasure_map+2, g) == 1)
    printf("Test 5 passed\n");
else
    printf("Test 5 failed\n");

printf("********supplyCount() tests complete********\n\n");
}//end main
