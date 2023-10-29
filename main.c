#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "actor.h"

int gameOver(map *m, position *ghost, position *pacman, position *treasure);
void gameOverArt();

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
    } while (!gameOver(&m, &ghost, &pacman, &treasure));

    freeMapMemory(&m);
    return 0;
}

int gameOver(map *m, position *ghost, position *pacman, position *treasure) // Track if game is won / lost
{
    if (m->map[pacman->x][pacman->y] == ghost->icon)
    {
        gameOverArt();
        return 1;
    }
    if (pacman->x == treasure->x && pacman->y == treasure->y)
    {
        printf("\nYou won!\n\n");
        return 1;
    }
    return 0;
}

void gameOverArt()
{
    char *gameOverArt[] = {
        "_____",
        "|  __ \\",
        "| |  \\/ __ _ _ __ ___   ___    _____   _____ _ __",
        "| | __ / _` | '_ ` _ \\ / _ \\  / _ \\ \\ / / _ \\ '__|",
        "| | \\ \\ (_| | | | | | |  __/ | (_) \\ V /  __/ |",
        " \\____/\\__,_|_| |_| |_|\\___|  \\___/ \\_/ \\___|_|",
        "\0",
    };

    for (int i = 0; i < 7; i++)
    {
        printf("%s\n", gameOverArt[i]);
    }
    printf("\n");
}