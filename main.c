#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "actor.h"

int gameOver(position *ghost, position *pacman);

int main(void)
{
    ghost.icon = 'G';
    pacman.icon = '@';

    // Preparing map and defining initial position
    readMap(&m);
    findPosition(&m, &pacman);

    do // Loop until the game is over
    {
        printMap(&m); // Display the current game state
        trackKeyPress(&m, &pacman);
        moveGhost(&ghost, &m);
    } while (!gameOver(&ghost, &pacman));

    freeMapMemory(&m);
    return 0;
}

int gameOver(position *ghost, position *pacman) // Track if game is won / lost
{
    if (ghost->x == pacman->x && ghost->y == pacman->y)
    {
        printf("Game over!\n");
        return 1;
    }
    return 0;
}