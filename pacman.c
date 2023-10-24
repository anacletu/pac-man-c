#include <stdio.h>
#include <stdlib.h>
#include "pacman.h"
#include "map.h"

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

        char event;
        scanf(" %c", &event);
        if (event == 'w' || event == 'a' || event == 's' || event == 'd')
        {
            move(&m, &pacman, event);
        }
        else
        {
            printf("Use WASD to move around the map\n");
        }
    } while (!gameOver());

    freeMapMemory(&m);
    return 0;
}

void move(map *m, position *pacman, char event)
{
    m->map[pacman->x][pacman->y] = '.';

    switch (event) // Update the player's position on the map
    {
    case 'a':
        m->map[pacman->x][(pacman->y) - 1] = pacman->icon;
        pacman->y--;
        break;
    case 'w':
        m->map[(pacman->x) - 1][pacman->y] = pacman->icon;
        pacman->x--;
        break;
    case 's':
        m->map[(pacman->x) + 1][pacman->y] = pacman->icon;
        pacman->x++;
        break;
    case 'd':
        m->map[pacman->x][(pacman->y) + 1] = pacman->icon;
        pacman->y++;
        break;
    }
}

int gameOver() // Track if game is won / lost
{
    return 0;
}