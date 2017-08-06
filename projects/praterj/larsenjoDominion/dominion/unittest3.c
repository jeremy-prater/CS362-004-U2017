/*
 * unittest3.c
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
printf("********Testing getCost()********\n");

//holds all the card costs
int arr[27] = {0, 2, 5, 8, 0, 3, 6, 6, 5, 4, 4, 5, 4, 4, 3, 4, 3, 5, 3, 5, 3, 4, 2, 5, 4, 4, 4};

int i;

for(i = 0; i < 27; i++)
{
    if(getCost(i) == arr[i])
        printf("Test %d passed\n", i+1);
    else
        printf("Test %d failed\n", i+1);
}

i++;

//check the default result of -1
if(getCost(30) == -1)
    printf("Test %d passed\n", i+1);
else
    printf("Test %d failed\n", i+1);


printf("********getCost() tests complete********\n\n");
}//end main
