#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "actor.h"
#include "map.h"

void findPosition(map *m, position *actor)
{
    actor->x = -1;
    actor->y = -1;

    for (int i = 0; i < m->num_rows; i++) // Finding pacman position
    {
        for (int j = 0; j < m->num_cols; j++)
        {
            if (m->map[i][j] == actor->icon)
            {
                actor->x = i;
                actor->y = j;
                break;
            }
        }
    }
}

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

    if (wall(m, x_axis, y_axis) ||
        (!emptySpace(m, x_axis, y_axis) && !isActor(m, x_axis, y_axis, &treasure)))
        return;

    moveActor(m, pacman, x_axis, y_axis);
}

void moveGhost(position *ghost, map *m)
{
    ghost->x = -1;
    ghost->y = -1;

    for (int i = 0; i < m->num_rows; i++)
    {
        for (int j = 0; j < m->num_cols; j++)
        {
            if (m->map[i][j] == ghost->icon)
            {
                ghost->x = i;
                ghost->y = j;
                ghostAI(ghost, m);
            }
        }
    }
}

void ghostAI(position *ghost, map *m)
{
    int x_axis = ghost->x;
    int y_axis = ghost->y;

    // Initialize the random number generator
    srand(time(NULL));
    // Generate random integers between -1 and 1
    int random_num = rand() % 4;

    switch (random_num)
    {
    case 0:
        y_axis--;
        break;
    case 1:
        x_axis--;
        break;
    case 2:
        x_axis++;
        break;
    case 3:
        y_axis++;
        break;
    }

    if ((!wall(m, x_axis, y_axis) && emptySpace(m, x_axis, y_axis)) ||
        isActor(m, x_axis, y_axis, &pacman))
    {
        moveActor(m, ghost, x_axis, y_axis);
    }
}