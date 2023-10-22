#include <stdio.h>
#include <stdlib.h>
#include "pacman.h"

int main(void)
{
    // opening the source file of the map
    FILE *map_source = fopen("map.txt", "r");
    if (map_source == NULL)
    {
        printf("Couldn't open map file\n");
        exit(1);
    }

    // defining map matrix
    int num_rows, num_cols;
    countMapSize(map_source, &num_rows, &num_cols);

    // drawing map on screen
    createMaze(num_rows, num_cols, map_source);

    // closing source file after printing
    fclose(map_source);

    return 0;
}

void countMapSize(FILE *map_source, int *num_rows, int *num_cols)
{
    *num_rows = 1; // accounting for first row
    *num_cols = 0;
    int c;

    while ((c = fgetc(map_source)) != EOF)
    {
        if (c == '\n')
        {
            (*num_rows)++;
            *num_cols = 0; // reset columns for each new row
        }
        else
        {
            (num_cols)++; // last iteration won't be reset due to EOF
        }
    }
    fseek(map_source, 0, SEEK_SET); // reset the file pointer to the beginning of the source file
}

void createMaze(int rows, int cols, FILE *map_source) // drawing the map on the terminal
{
    char map[rows][cols + 1];

    for (int i = 0; i < rows; i++)
    {
        fscanf(map_source, "%s", map[i]);
        printf("%s\n", map[i]);
    }
}