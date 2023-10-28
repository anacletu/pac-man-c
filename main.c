#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "actor.h"

int gameOver(position *ghost, position *pacman, position *treasure);

int main(void)
{
    ghost.icon = 'G';
    pacman.icon = '@';
    treasure.icon = 'x';

    // Preparing map and defining initial position
    readMap(&m);
    findPosition(&m, &pacman);
    findPosition(&m, &treasure);

    do // Loop until the game is over
    {
        printMap(&m); // Display the current game state
        trackKeyPress(&m, &pacman);
        moveGhost(&ghost, &m);
    } while (!gameOver(&ghost, &pacman, &treasure));

    freeMapMemory(&m);
    return 0;
}

int gameOver(position *ghost, position *pacman, position *treasure) // Track if game is won / lost
{
    if (ghost->x == pacman->x && ghost->y == pacman->y)
    {
        printf("\nGame over!\n\n");
        return 1;
    }
    if (pacman->x == treasure->x && pacman->y == treasure->y)
    {
        printf("\nYou won!\n\n");
        return 1;
    }
    return 0;
}