#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "map.h"

char wall_art[4][7] = { // ASCII Art from Maurício Aniche (https://github.com/mauricioaniche)
    {"......"},
    {"......"},
    {"......"},
    {"......"}};

char ghots_art[4][7] = {
    {" .-.  "},
    {"| OO| "},
    {"|   | "},
    {"'^^^' "}};

char pacman_art[4][7] = {
    {" .--. "},
    {"/ _.-'"},
    {"\\  '-."},
    {" '--' "}};

char treasure_art[4][7] = {
    {"  /\\  "},
    {" <  > "},
    {"  \\/  "},
    {"      "}};

char empty_space[4][7] = {
    {"      "},
    {"      "},
    {"      "},
    {"      "}};

void readMap(map *m) // Reads the map data from a file and allocates memory for the map.
{
    FILE *map_source = fopen("map.txt", "r"); // Attempt to open the map file for reading
    if (map_source == NULL)
    {
        printf("%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    int c;
    m->num_rows = 1; // Accounting for first row
    m->num_cols = 0;
    while ((c = fgetc(map_source)) != EOF)
    {
        if (ferror(map_source))
        {
            printf("I/O error reading file.\n");
            exit(EXIT_FAILURE);
        }
        else if (c == '\n')
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
        printf("%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < m->num_rows; i++)
    {
        m->map[i] = calloc(sizeof(char), m->num_cols + 1);
        if (m->map[i] == NULL)
        {
            printf("%s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
    }
}

void printMap(map *m) // Display map on terminal
{
    for (int i = 0; i < m->num_rows; i++)
    {

        for (int section = 0; section < 4; section++)
        {
            for (int j = 0; j < m->num_cols; j++)
            {

                switch (m->map[i][j])
                {
                case 'G':
                    printSection(ghots_art, section);
                    break;
                case '@':
                    printSection(pacman_art, section);
                    break;
                case 'x':
                    printSection(treasure_art, section);
                    break;
                case '|':
                case '-':
                    printSection(wall_art, section);
                    break;
                case '.':
                    printSection(empty_space, section);
                    break;
                }
            }
            printf("\n");
        }
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

int emptySpace(map *m, int x, int y)
{
    return (m->map[x][y] != '.') ? 0 : 1;
}

int isActor(map *m, int x, int y, position *actor)
{
    return (m->map[x][y] == actor->icon) ? 1 : 0;
}

void freeMapMemory(map *m) // Free allocated memory for the map
{
    for (int i = 0; i < m->num_rows; i++)
    {
        free(m->map[i]);
    }
    free(m->map);
}

void printSection(char drawing[4][7], int section)
{
    printf("%s", drawing[section]);
}
