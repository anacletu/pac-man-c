#include <stdio.h>
#include <stdlib.h>
#include "pacman.h"

void readMap();
void allocateMapMemory();
void printMap();
void move(char event);
int gameOver();
void freeMapMemory();

// declaring global variables
int num_rows = 1; // accounting for first row
int num_cols = 0;
char **map;

int main(void)
{
    readMap();

    do
    {
        printMap();

        char event;
        scanf(" %c", &event);
        if (event == 'w' || event == 'a' || event == 's' || event == 'd')
        {
            move(event);
        }
        else
        {
            printf("Use WASD to move around the map\n");
        }

    } while (!gameOver());

    void freeMapMemory();
    return 0;
}

void readMap()
{
    FILE *map_source = fopen("map.txt", "r");
    if (map_source == NULL)
    {
        printf("Couldn't open map file\n");
        exit(1);
    }

    int c;
    while ((c = fgetc(map_source)) != EOF)
    {
        if (c == '\n')
        {
            num_rows++;
            num_cols = 0; // reset columns for each new row
        }
        else
        {
            num_cols++; // last iteration won't be reset due to EOF
        }
    }
    fseek(map_source, 0, SEEK_SET); // reset the file pointer to the beginning of the source file

    allocateMapMemory();

    for (int i = 0; i < num_rows; i++)
    {
        fscanf(map_source, "%s", map[i]);
    }

    fclose(map_source);
}

void allocateMapMemory()
{
    map = calloc(sizeof(char *), num_rows);
    if (map == NULL)
    {
        printf("Memory allocation failed\n");
        exit(2);
    }

    for (int i = 0; i < num_rows; i++)
    {
        map[i] = calloc(sizeof(char), num_cols + 1);
        if (map[i] == NULL)
        {
            printf("Memory allocation failed\n");
            exit(2);
        }
    }
}

void printMap()
{
    for (int i = 0; i < num_rows; i++)
    {
        printf("%s\n", map[i]);
    }
}

void move(char event)
{
    int x = -1;
    int y = -1;

    for (int i = 0; i < num_rows; i++) // finding pacman position
    {
        for (int j = 0; j < num_cols; j++)
        {
            if (map[i][j] == '@')
            {
                x = i;
                y = j;
                break;
            }
        }
    }

    switch (event) // simulating controller
    {
    case 'a':
        map[x][y - 1] = '@';
        break;
    case 'w':
        map[x - 1][y] = '@';
        break;
    case 's':
        map[x + 1][y] = '@';
        break;
    case 'd':
        map[x][y + 1] = '@';
        break;
    }

    map[x][y] = '.';
}

int gameOver()
{
    return 0;
}

void freeMapMemory()
{
    for (int i = 0; i < num_rows; i++)
    {
        free(map[i]);
    }
    free(map);
}