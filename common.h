#ifndef COMMON_H
#define COMMON_H

typedef struct
{
    int num_rows;
    int num_cols;
    char **map;
} map;

typedef struct
{
    char icon;
    int x;
    int y;
} position;

// Declaring the structs
map m;
position pacman;
position ghost;

#endif