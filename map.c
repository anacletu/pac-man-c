#include <stdio.h>
#include <stdlib.h>
#include "map.h"

void readMap(map *m) // Reads the map data from a file and allocates memory for the map.
{
    FILE *map_source = fopen("map.txt", "r"); // Attempt to open the map file for reading
    if (map_source == NULL)
    {
        printf("Couldn't open map file\n");
        exit(1);
    }

    int c;
    m->num_rows = 1; // Accounting for first row
    m->num_cols = 0;
    while ((c = fgetc(map_source)) != EOF)
    {
        if (c == '\n')
        {
            m->num_rows++;
            m->num_cols = 0; // Reset columns for each new row
        }
        else
        {
            m->num_cols++; // Last iteration won't be reset due to EOF
        }
    }
    fseek(map_source, 0, SEEK_SET); // Reset the file pointer to the beginning of the source file

    allocateMapMemory(m);

    for (int i = 0; i < m->num_rows; i++)
    {
        fscanf(map_source, "%s", m->map[i]);
    }

    fclose(map_source); // Close the map file after reading
}

void allocateMapMemory(map *m) // Allocate memory for the 2D map array
{
    m->map = calloc(sizeof(char *), m->num_rows);
    if (m->map == NULL) // Check for memory allocation errors
    {
        printf("Memory allocation failed\n");
        exit(2);
    }

    for (int i = 0; i < m->num_rows; i++)
    {
        m->map[i] = calloc(sizeof(char), m->num_cols + 1);
        if (m->map[i] == NULL)
        {
            printf("Memory allocation failed\n");
            exit(2);
        }
    }
}

void printMap(map *m) // Display map on terminal
{
    for (int i = 0; i < m->num_rows; i++)
    {
        printf("%s\n", m->map[i]);
    }
}

int wall(map *m, int x, int y)
{
    if (x >= m->num_rows)
        return 1;
    if (y >= m->num_cols)
        return 1;
    return 0;
}

int emptySpace(map *m, position *pacman, int x, int y)
{
    return (m->map[x][y] != '.' && m->map[x][y] != pacman->icon) ? 0 : 1;
}

void freeMapMemory(map *m) // Free allocated memory for the map
{
    for (int i = 0; i < m->num_rows; i++)
    {
        free(m->map[i]);
    }
    free(m->map);
}