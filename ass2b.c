/* Christopher Mercuri, Student Number: 694657 */
/* COMP20005 Engineering Computation Assignment 2 */
/* C Programming is Fun! */

#include <stdio.h>
#include <string.h>

#define MAXMAZE 100
#define WALL '#'
#define PATH '.'
#define CORR_PATH '+'
#define UNUSED '-'

typedef char maze_row[MAXMAZE+1]; // string array to store a maze row

typedef struct {
    maze_row maze[MAXMAZE]; //array of string arrays to store maze
    int hassoln; //set to 0, and becomes 1 if solution found
    int row_count; //row counter
    int col_count; //column counter
} maze_t;

void read_maze(maze_t *maze);
void print_stage1(maze_t *maze);
void assign_reachability(maze_t *maze);
int is_deadend(maze_t *maze, int i, int j);
void valid_path(maze_t *maze, int *i, int *j);
void print_stage2(maze_t *maze);

int
main(int argc, char* argv[]) {
    maze_t m;
    
    read_maze(&m);
    print_stage1(&m);
    assign_reachability(&m);
    print_stage2(&m);
    
    return 0;
}

/* Function that sets all maze counters to 0 and then reads in the maze row by 
row and stores it while updating the number of rows/columns */

void
read_maze(maze_t *maze) {
	/* Set all of the counters to 0 */
	maze->row_count = 0;
	maze->col_count = 0;
	maze->hassoln = 0;
	
    while ((scanf("%s", maze->maze[maze->row_count])) != EOF) {
        maze->row_count ++;
    }
    maze->col_count = strlen(maze->maze[0]);
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
	for(i=0; i<(maze->row_count); i++) {
		for(j=0; j<(maze->col_count); j++) {
			if (maze->maze[i][j] == WALL) {
				printf("##");
			} else if (maze->maze[i][j] == PATH) {
				printf("..");
			}
			if (j == (maze->col_count-1)) {
				printf("\n");
			}
		}
	}
	printf("\n");
}

/* Function that reads throught the array and alters the path characters if
they are reachable from the top */

void
assign_reachability(maze_t *maze) {
	int i, j, start;
	
	for(start=0; start<(maze->col_count); start++) {
	    if (maze->maze[0][start] == PATH) {
	        maze->maze[0][start] = CORR_PATH;
	        j = start;
	        i = 1;
            while ((i < maze->row_count) && (i >= 0) && 
                (j <= maze->col_count) && (j >= 0) &&
                (!is_deadend(maze, i, j))) {
                maze->maze[i][j] = CORR_PATH;
                valid_path(maze, &i, &j);
            }
            if ((i == (maze->row_count-1)) && (maze->maze[i][j] = CORR_PATH)) {
                maze->hassoln = 1;
            }
	    }
	}
	for(i=0; i<(maze->row_count); i++) {
	    for(j=0; j<(maze->col_count); j++) {
	        if (maze->maze[i][j] == PATH) {
	            if (maze->maze[i-1][j] == CORR_PATH){
                    maze->maze[i][j] = CORR_PATH;
                } else if (maze->maze[i+1][j] == CORR_PATH){
                    maze->maze[i][j] = CORR_PATH;
                } else if (maze->maze[i][j-1] == CORR_PATH){
                    maze->maze[i][j] = CORR_PATH;
                } else if (maze->maze[i][j+1] == CORR_PATH){
                    maze->maze[i][j] = CORR_PATH;
                } else {
                    maze->maze[i][j] = UNUSED;
                }
	        }
	    }
	}
	
}

int
is_deadend(maze_t *maze, int i, int j) {
    int count = 0;
    if ((maze->maze[i-1][j] == PATH) || (maze->maze[i-1][j] == CORR_PATH)){
        count++;
    }
    if ((maze->maze[i+1][j] == PATH) || (maze->maze[i+1][j] == CORR_PATH)){
        count++;
    }
    if ((maze->maze[i][j-1] == PATH) || (maze->maze[i][j-1] == CORR_PATH)){
        count++;
    }
    if ((maze->maze[i][j+1] == PATH) || (maze->maze[i][j+1] == CORR_PATH)){
        count++;
    }
    if (count > 1) {
        return 0;
    }
    return 1;
}

void
valid_path(maze_t *maze, int *i, int *j) {
    if (maze->maze[*i-1][*j] == PATH){
        *i -= 1;
    } else if (maze->maze[*i+1][*j] == PATH){
        *i += 1;
    } else if (maze->maze[*i][*j-1] == PATH){
        *j -= 1;
    } else if (maze->maze[*i][*j+1] == PATH){
        *j += 1;
    }
}

/* Function that determines if there is a solution to the maze and prints it 
out as per the format of stage 2 */

void
print_stage2(maze_t *maze) {
	int i, j;
	
	/* Print the stage intro stuff */
	printf("Stage 2\n");
	printf("=======\n");

	for(j=0; j<(maze->col_count); j++) {
	    if (maze->maze[(maze->row_count)-1][j] == CORR_PATH) {
	        maze->hassoln = 1;
	    }
	}
	
	if (maze->hassoln) {
	    printf("maze has a solution\n");
	} else {
	    printf("maze does not have a solution\n");
	}
	
	/* Read through the maze character by character and print 2x the 
	character */
	for(i=0; i<(maze->row_count); i++) {
		for(j=0; j<(maze->col_count); j++) {
			if (maze->maze[i][j] == WALL) {
				printf("##");
			} else if (maze->maze[i][j] == CORR_PATH) {
				printf("++");
			} else if (maze->maze[i][j] == UNUSED) {
				printf("--");
			}
			if (j == (maze->col_count-1)) {
				printf("\n");
			}
		}
	}
	printf("\n");
}