/*
 * unittest4.c
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
int isGameOver(struct gameState *state) 
{
  int i;
  int j;
	
  //if stack of Province cards is empty, the game ends
  if (state->supplyCount[province] == 0)
    {
      return 1;
    }

  //if three supply pile are at 0, the game ends
  j = 0;
  for (i = 0; i < 25; i++)
    {
      if (state->supplyCount[i] == 0)
	{
	  j++;
	}
    } 
  if ( j >= 3)
    { 
      return 1;
    }

  return 0;
}
*/
  
struct gameState* g = malloc(sizeof(struct gameState));
printf("********Testing isGameOver()********\n");

//set province cards to empty
g->supplyCount[province] = 0;
if( isGameOver(g) == 1 )
    printf("Test 1 passed\n");
else
    printf("Does not recognize empyt stack of province cards\n");

//set all supply piles to non-empty
int i;
for(i = 0; i < 25; i++)
    g->supplyCount[i] = 1;
if( isGameOver(g) == 0 )
    printf("Test 2 passed\n");
else
    printf("Not correctly counting supply piles\n");

//change 3 supply piles to empty
g->supplyCount[1] = 0;
g->supplyCount[15] = 0;
g->supplyCount[20] = 0;
if( isGameOver(g) == 1 )
    printf("Test 3 passed\n");
else
    printf("Not correctly recognizing empty supply piles\n");

printf("********isGameOver() tests complete********\n\n");
}//end main



