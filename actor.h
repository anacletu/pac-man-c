#ifndef ACTOR_H
#define ACTOR_H

#include "common.h"

void findPosition(map *m, position *actor);
int keyValidation(char key_pressed);
void trackKeyPress(map *m, position *pacman);
void moveActor(map *m, position *actor, int x, int y);
void findGhost(position *ghost, map *m);
void ghostAI(position *ghost, map *m);

#endif