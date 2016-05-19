/* Christopher Mercuri, Student Number: 694657 */
/* COMP20005 Engineering Computation Assignment 2 */
/* C Programming is Fun! */
/* Main uses similar style to our lord and saviour Alastair Moffat */

#include <stdio.h>
#include <string.h>

/* Constants and Maze identifiers */

#define MAXMAZE 100
#define WALL '#'
#define PATH '.'
#define CORR_PATH '+'
#define UNUSED '-'

/* Structure definitions */

typedef struct {
    char type;						//cell type
    int cost;						//cost to reach cell, if viable
} cell_t;

typedef struct {
    cell_t maze[MAXMAZE][MAXMAZE];  //array of cells
    int hassoln;                    //set to 0, and becomes 1 if solution found
    int row_count;                  //row counter
    int col_count;                  //column counter
    int cost_count;					//smallest cost counter
} maze_t;

/* Function Prototypes */

void read_maze(maze_t *maze);
void print_stage1(maze_t *maze);
void assign_reachability(maze_t *maze);
void print_stage2(maze_t *maze);
void print_stage3(maze_t *maze);

int
main(int argc, char* argv[]) {
    maze_t m;
    
    read_maze(&m);
    print_stage1(&m);
    assign_reachability(&m);
    print_stage2(&m);
    print_stage3(&m);
    
    return 0;
}

/* Function that sets all maze counters to 0 and then reads in the maze row by 
row and stores it while updating the number of rows/columns */

void
read_maze(maze_t *maze) {
    char read[MAXMAZE+1];
    int col = 0, i;
    
	/* Set all of the counters to 0 */
	maze->row_count = 0;
	maze->col_count = 0;
	maze->hassoln = 0;
	maze->cost_count = 0;
	
    while ((scanf("%c", read)) != EOF) {
    	for(i=0; i < strlen(read); i ++) {
			if (read[i] == WALL) {
				maze->maze[maze->row_count][maze->col_count].type = WALL;
				maze->col_count ++;
			} else if (read[i] == PATH) {
				maze->maze[maze->row_count][maze->col_count].type = PATH;
				maze->col_count ++;
			} else if (read[i] == '\n') {
				maze->row_count ++;
				col = maze->col_count;
				maze->col_count = 0;
			}
        }
    }
    maze->row_count ++;
    maze->col_count = col;
}

/* Function that prints out the stored array in the format of Stage 1 */

void
print_stage1(maze_t *maze) {
	int i, j;
	
	/* Print the stage intro stuff */
	printf("Stage 1\n");
	printf("=======\n");
	printf("maze has %d rows and %d columns\n", maze->row_count, 
		maze->col_count);
	
	/* Read through the maze character by character and print 2x the 
	character */
	for(i=0; i<=(maze->row_count); i++) {
		for(j=0; j<(maze->col_count); j++) {
			if (maze->maze[i][j].type == WALL) {
				printf("##");
			} else if (maze->maze[i][j].type == PATH) {
				printf("..");
			}
			if (j == (maze->col_count-1)) {
				printf("\n");
			}
		}
	}
}

/* Function that reads throught the array and alters the path characters if
they are reachable from the top */

void
assign_reachability(maze_t *maze) {
	int i, j;
	int changes = 1;
	int cost;
	
	for(j=0; j<(maze->col_count); j++) {
	    if (maze->maze[0][j].type == PATH) {
	        maze->maze[0][j].type = CORR_PATH;
	    }
	}
	while (changes != 0) {
		changes = 0;
		cost = 0;
		for(i=0; i<(maze->row_count); i++) {
			for(j=0; j<(maze->col_count); j++) {
				if ((maze->maze[i][j].type == PATH) || 
					(maze->maze[i][j].type == UNUSED)) {
					if (maze->maze[i-1][j].type == CORR_PATH){
						maze->maze[i][j].type = CORR_PATH;
						changes ++;
						if (cost < maze->maze[i][j].cost) {
							maze->maze[i][j].cost = cost;
						}
						cost ++;
					} else if (maze->maze[i+1][j].type == CORR_PATH){
						maze->maze[i][j].type = CORR_PATH;
						changes ++;
						if (cost < maze->maze[i][j].cost) {
							maze->maze[i][j].cost = cost;
						}
						cost ++;
					} else if (maze->maze[i][j-1].type == CORR_PATH){
						maze->maze[i][j].type = CORR_PATH;
						changes ++;
						if (cost < maze->maze[i][j].cost) {
							maze->maze[i][j].cost = cost;
						}
						cost ++;
					} else if (maze->maze[i][j+1].type == CORR_PATH){
						maze->maze[i][j].type = CORR_PATH;
						changes ++;
						if (cost < maze->maze[i][j].cost) {
							maze->maze[i][j].cost = cost;
						}
						cost ++;
					} else {
						maze->maze[i][j].type = UNUSED;
					}
				}
			}
		}
	}
	for(j=0; j<(maze->col_count); j++) {
	    if (maze->maze[0][j].type == CORR_PATH) {
	        maze->hassoln = 1;
	    }
	}
	
}

/* Function prints out maze as per the format of stage 2 */

void
print_stage2(maze_t *maze) {
	int i, j;
	
	/* Print the stage intro stuff */
	printf("Stage 2\n");
	printf("=======\n");

	if (maze->hassoln) {
	    printf("maze has a solution\n");
	} else {
	    printf("maze does not have a solution\n");
	}
	
	/* Read through the maze character by character and print 2x the 
	character */
	for(i=0; i<(maze->row_count); i++) {
		for(j=0; j<(maze->col_count); j++) {
			if (maze->maze[i][j].type == WALL) {
				printf("##");
			} else if (maze->maze[i][j].type == CORR_PATH) {
				printf("++");
			} else if (maze->maze[i][j].type == UNUSED) {
				printf("--");
			}
			if (j == (maze->col_count-1)) {
				printf("\n");
			}
		}
	}
}

void
print_stage3(maze_t *maze) {
	int i, j;
	
	/* Print the stage intro stuff */
	printf("Stage 3\n");
	printf("=======\n");

	if (maze->hassoln) {
	    printf("maze has a solution with a cost %d\n", maze->cost_count);
	} else {
	    printf("maze does not have a solution\n");
	}
	
	/* Read through the maze character by character and print 2x the 
	character */
	for(i=0; i<(maze->row_count); i++) {
		for(j=0; j<(maze->col_count); j++) {
			if (maze->maze[i][j].type == WALL) {
				printf("##");
			} else if (maze->maze[i][j].type == CORR_PATH) {
				if (maze->maze[i][j].cost%2 == 0) {
					printf("%02d", maze->maze[i][j].cost);
				} else {
					printf("++");
				}
			} else if (maze->maze[i][j].type == UNUSED) {
				printf("--");
			}
			if (j == (maze->col_count-1)) {
				printf("\n");
			}
		}
	}
}