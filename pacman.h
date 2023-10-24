// function declarations
void readMap();
void allocateMapMemory();
void printMap();
void move(char event);
int gameOver();
void freeMapMemory();

// struct for handling map
typedef struct
{
    int num_rows;
    int num_cols;
    char **map;
} map;