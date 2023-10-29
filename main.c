#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "actor.h"

void openingArt();
int gameOver(map *m, position *ghost, position *pacman, position *treasure);
void gameOverArt();
void victoryArt();

int main(void)
{
    // Declaring icon for the actors (struct in common.h)
    ghost.icon = 'G';
    pacman.icon = '@';
    treasure.icon = 'x';

    // Preparing map and defining initial position
    readMap(&m);
    findPosition(&m, &pacman);
    findPosition(&m, &treasure);

    openingArt();

    do // Loop until the game is over
    {
        printMap(&m); // Display the current game state
        trackKeyPress(&m, &pacman);
        if (!gameOver(&m, &ghost, &pacman, &treasure))
            findGhost(&ghost, &m);
    } while (!gameOver(&m, &ghost, &pacman, &treasure));

    freeMapMemory(&m); // Free map memory when done
    return 0;
}

void openingArt()
{
    printf("\n***********************************\n");
    printf(" Use WASD keys to move the PacMan\n");
    printf("Reach the star and avoid the ghosts\n");
    printf("***********************************\n\n");
}

int gameOver(map *m, position *ghost, position *pacman, position *treasure) // Track if game is won / lost
{
    if (m->map[pacman->x][pacman->y] == ghost->icon)
    {
        printMap(m);
        gameOverArt();
        return 1;
    }
    if (pacman->x == treasure->x && pacman->y == treasure->y)
    {
        printMap(m);
        victoryArt();
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
        "\0", // NULL to mark the end of the array
    };

    // Loop through the array to print the game over art
    for (int i = 0; i < 7; i++)
    {
        printf("%s\n", gameOverArt[i]);
    }
    printf("\n");
}

void victoryArt()
{
    char *victory[] = {
        "__   __                                _ ",
        "\\ \\ / /                               | |",
        " \\ V /___  _   _  __      _____  _ __ | |",
        "  \\ // _ \\| | | | \\ \\ / \\/ / _ \\| '_ \\| |",
        "  | | (_) | |_| |  \\ V  V / (_) | | | |_|",
        "  \\_/\\___/ \\__,_|   \\_/\\_/ \\___/|_| |_(_)",
        "\0", // NULL to mark the end of the array
    };

    // Loop through the array to print the victory art
    for (int i = 0; i < 7; i++)
    {
        printf("%s\n", victory[i]);
    }
    printf("\n");
}