#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define SAND 1
#define VOID 0

void setSand(int** matrix,int posX,int posY){

matrix[posX][posY] = SAND;
}


void unsetSand(int** matrix,int posX,int posY){

matrix[posX][posY] = VOID;
}

void updateSand(int** matrix, int x, int y){

if (y > 0) {
        // Check if the sand can move directly downward
        if (matrix[x][y-1] == VOID) { // go bottom
            unsetSand(matrix, x, y);
            setSand(matrix, x, y-1);
        } 
        // Check if the sand can move downward to the left
        else if (x > 0 && matrix[x-1][y-1] == VOID) { // go left
            unsetSand(matrix, x, y);
            setSand(matrix, x-1, y-1);
        }
        // Check if the sand can move downward to the right
        else if (x < 500-1 && matrix[x+1][y-1] == VOID) { // go right
            unsetSand(matrix, x, y);
            setSand(matrix, x+1, y-1);
        }
    }
}
