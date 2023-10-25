#include <stdio.h>
#include <stdlib.h>
#include "declarations.h"

int keyValidation(char key_pressed) // Check if user typed the expected keys
{
    if (key_pressed != 'w' &&
        key_pressed != 'a' &&
        key_pressed != 's' &&
        key_pressed != 'd')
    {
        printf("Use WASD to move around the map\n\n");
        return 0;
    }
    return 1;
}

void moveActor(map *m, position *actor, int x, int y)
{
    m->map[x][y] = actor->icon;
    m->map[actor->x][actor->y] = '.';
    actor->x = x;
    actor->y = y;
}

void trackKeyPress(map *m, position *pacman) // Control the moviment of the actor
{
    char event;
    scanf(" %c", &event);
    if (!keyValidation(event)) // Call validation function
        return;

    int x_axis = pacman->x;
    int y_axis = pacman->y;

    switch (event) // Update the player's position on the map
    {
    case 'a':
        y_axis--;
        break;
    case 'w':
        x_axis--;
        break;
    case 's':
        x_axis++;
        break;
    case 'd':
        y_axis++;
        break;
    }

    if (wall(m, x_axis, y_axis))
        return;

    if (!emptySpace(m, x_axis, y_axis))
        return;

    moveActor(m, pacman, x_axis, y_axis);
}