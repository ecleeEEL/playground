#include <stdlib.h>
#include <iostream>
#include <string.h>


int ** allocmatrix(int rows, int columns) {
    int ** returnmatrix =  (int **) malloc(sizeof(int *) * rows);

    for (int i = 0; i < rows; i++ ) {

        returnmatrix[i] = (int*)  malloc(sizeof (int ) * columns);
        memset(returnmatrix[i], 0, columns *sizeof(int));
    }
    return returnmatrix;

}



int main () {
    int rows = 5;
    int columns = 3;
    int ** matrix = allocmatrix(rows,columns);

    matrix[2][1] = 4;

    for (int i = 0; i < rows; i ++ ) {
        int * row = matrix[i];
        std::cout << "Row " << i << ":" << std::endl;
        std::cout << "*** ";
        for (int j = 0; j < columns; j++) {
            std::cout << row[j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}