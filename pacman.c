#include <stdio.h>
#include <stdlib.h>
#include "pacman.h"

map m; // Global struct for handling the game map

int main(void)
{
    readMap();

    do // Loop until the game is over
    {
        printMap(); // Display the current game state

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

void readMap() // Reads the map data from a file and allocates memory for the map.
{
    FILE *map_source = fopen("map.txt", "r"); // Attempt to open the map file for reading
    if (map_source == NULL)
    {
        printf("Couldn't open map file\n");
        exit(1);
    }

    int c;
    m.num_rows = 1; // Accounting for first row
    m.num_cols = 0;
    while ((c = fgetc(map_source)) != EOF)
    {
        if (c == '\n')
        {
            m.num_rows++;
            m.num_cols = 0; // Reset columns for each new row
        }
        else
        {
            m.num_cols++; // Last iteration won't be reset due to EOF
        }
    }
    fseek(map_source, 0, SEEK_SET); // Reset the file pointer to the beginning of the source file

    allocateMapMemory();

    for (int i = 0; i < m.num_rows; i++)
    {
        fscanf(map_source, "%s", m.map[i]);
    }

    fclose(map_source); // Close the map file after reading
}

void allocateMapMemory() // Allocate memory for the 2D map array
{
    m.map = calloc(sizeof(char *), m.num_rows);
    if (m.map == NULL) // Check for memory allocation errors
    {
        printf("Memory allocation failed\n");
        exit(2);
    }

    for (int i = 0; i < m.num_rows; i++)
    {
        m.map[i] = calloc(sizeof(char), m.num_cols + 1);
        if (m.map[i] == NULL)
        {
            printf("Memory allocation failed\n");
            exit(2);
        }
    }
}

void printMap() // Display map on terminal
{
    for (int i = 0; i < m.num_rows; i++)
    {
        printf("%s\n", m.map[i]);
    }
}

void move(char event)
{
    int x = -1;
    int y = -1;

    for (int i = 0; i < m.num_rows; i++) // Finding pacman position
    {
        for (int j = 0; j < m.num_cols; j++)
        {
            if (m.map[i][j] == '@')
            {
                x = i;
                y = j;
                break;
            }
        }
    }

    switch (event) // Update the player's position on the map
    {
    case 'a':
        m.map[x][y - 1] = '@';
        break;
    case 'w':
        m.map[x - 1][y] = '@';
        break;
    case 's':
        m.map[x + 1][y] = '@';
        break;
    case 'd':
        m.map[x][y + 1] = '@';
        break;
    }

    m.map[x][y] = '.';
}

int gameOver() // Track if game is won / lost
{
    return 0;
}

void freeMapMemory() // Free allocated memory for the map
{
    for (int i = 0; i < m.num_rows; i++)
    {
        free(m.map[i]);
    }
    free(m.map);
}