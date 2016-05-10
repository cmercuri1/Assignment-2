#include <stdio.h>

#define MAXMAZE 100
#define WALL #
#define PATH .
#define COR_PATH +
#define UNUSED -

typedef char maze_row[MAXMAZE+1];

typedef struct {
    maze_row maze[MAXMAZE];
    int hassoln = 0;
    int row_count = 0;
    int col_count = 0;
} maze_t;

maze_t read_maze(maze_t maze);

int
main(int argc, char* argv) {
    
    return 0;
}

maze_t
read_maze(maze_t &maze) {
    while scanf("%c", &maze.maze[row_count]) {
        maxe.row_count ++;
    maze.col_count = size(maze.maze[0]);
    
}