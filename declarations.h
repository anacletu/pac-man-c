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

void readMap(map *m);
void allocateMapMemory(map *m);
void printMap(map *m);
void freeMapMemory(map *m);
void findPosition(map *m, position *pacman);
int wall(map *m, int x, int y);
int emptySpace(map *m, int x, int y);
int keyValidation(char key_pressed);
void trackKeyPress(map *m, position *pacman);
void moveActor(map *m, position *actor, int x, int y);
int gameOver();
