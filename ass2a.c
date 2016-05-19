/* Christopher Mercuri, Student Number: 694657 */
/* COMP20005 Engineering Computation Assignment 2 */
/* C Programming is Fun! */
/* Main uses similar style to our lord and saviour Alastair Moffat */

#include <stdio.h>
#include <string.h>

#define MAXMAZE 100
#define WALL '#'
#define PATH '.'
#define CORR_PATH '+'
#define UNUSED '-'

typedef struct {
    char type;
} cell_t;

typedef struct {
    cell_t maze[MAXMAZE][MAXMAZE];  //array of string arrays to store maze
    int hassoln;                    //set to 0, and becomes 1 if solution found
    int row_count;                  //row counter
    int col_count;                  //column counter
} maze_t;

void read_maze(maze_t *maze);

int
main(int argc, char* argv[]) {
    maze_t m;
    
    read_maze(&m);
    
    return 0;
}

/* Function that sets all maze counters to 0 and then reads in the maze row by 
row and stores it while updating the number of rows/columns */

void
read_maze(maze_t *maze) {
    char read;
	/* Set all of the counters to 0 */
	maze->row_count = 0;
	maze->col_count = 0;
	maze->hassoln = 0;
	
    while ((scanf("%c", read)) != EOF) {
        if (read == WALL) {
            maze->maze[maze->row_count][maze->col_count]->type = WALL;
        } else if (read == PATH) {
            maze->maze[maze->row_count][maze->col_count]->type = PATH;
        } else if (read == '\n') {
            maze->row_count ++;
            maze->col_count = 0;
        }
        maze->col_count ++;
    }
    maze->col_count = len(maze->maze[0]);
}