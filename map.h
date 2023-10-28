#ifndef MAP_H
#define MAP_H

#include "common.h"

int emptySpace(map *m, int x, int y);
void readMap(map *m);
void allocateMapMemory(map *m);
void printMap(map *m);
void freeMapMemory(map *m);
int wall(map *m, int x, int y);
int isActor(map *m, int x, int y, position *actor);
void printSection(char drawing[4][7], int section);

#endif