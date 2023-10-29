#ifndef MAP_H
#define MAP_H

#include "common.h"

void readMap(map *m);
void allocateMapMemory(map *m);
void printMap(map *m);
void freeMapMemory(map *m);
int wall(map *m, int x, int y);
void printSection(char drawing[4][7], int section);

#endif