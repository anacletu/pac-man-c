#include <stdio.h>
#include <stdlib.h>
#include "declarations.h"

int main(void)
{
    // Declaring the structs
    map m;
    position pacman;

    // Preparing map and defining initial position
    readMap(&m);
    findPosition(&m, &pacman);

    do // Loop until the game is over
    {
        printMap(&m); // Display the current game state
        trackKeyPress(&m, &pacman);

    } while (!gameOver());

    freeMapMemory(&m);
    return 0;
}

int gameOver() // Track if game is won / lost
{
    return 0;
}