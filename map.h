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

void move(map *m, position *pacman, char event);