#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <string.h>
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
                return; // No need to continue searching
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
    if (m->map[x][y] != ghost.icon)
    {
        m->map[x][y] = actor->icon;
        m->map[actor->x][actor->y] = '.';
        actor->x = x;
        actor->y = y;
    }
    else
    {
        m->map[actor->x][actor->y] = '.';
        actor->x = x;
        actor->y = y;
    }
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

    moveActor(m, pacman, x_axis, y_axis);
}

void findGhost(position *ghost, map *m)
{
    map *m_copy = malloc(sizeof(map));
    if (m_copy == NULL)
    {
        printf("%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    memcpy(m_copy, m, sizeof(map)); // Creating a copy of the map in order not to move the same ghost twice (when y+1)

    for (int i = 0; i < m->num_rows; i++)
    {
        for (int j = 0; j < m->num_cols; j++)
        {
            if (m_copy->map[i][j] == ghost->icon)
            {
                ghost->x = i;
                ghost->y = j;
                ghostAI(ghost, m);
            }
        }
    }
    free(m_copy);
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

    if (!wall(m, x_axis, y_axis) &&
        (m->map[x_axis][y_axis] != treasure.icon) &&
        (m->map[x_axis][y_axis] != ghost->icon))
        moveActor(m, ghost, x_axis, y_axis);
}