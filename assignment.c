#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // Initialize random number generator
    srand(time(NULL));
    int minrand = 1;
    int maxrand = 100;

    // Check if the correct number of arguments is provided
    if (argc != 3) {
        printf("Incorrect usage. You provided %d arguments. The correct number of arguments is 2\n", argc - 1);
        return 1; 
    }

    // Check if arguments are integers and greater than 0
    for (int i = 1; i < 3; i++) {
        for (char *p = argv[i]; *p != '\0'; p++) {
            if (*p < '0' || *p > '9') {
                printf("Incorrect usage. The parameters you provided are not positive integers\n");
                return 1;
            }
        }
    }

    // Convert arguments to integers
    int rows = atoi(argv[1]);
    int cols = atoi(argv[2]);

    if (rows <= 0 || cols <= 0) {
        printf("Incorrect usage. The parameters you provided are not positive integers\n");
        return 1;
    }

    // Allocate memory for the matrix
    int **matrix = malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        matrix[i] = malloc(cols * sizeof(int));
    }

    // Fill the matrix with random numbers between 1 and 100
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = rand() % maxrand + minrand;
        }
    }

    // Write the matrix to a file
    FILE *file = fopen("matrix.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fprintf(file, "%d", matrix[i][j]);
            if (j < cols - 1) {
                fprintf(file, " ");
            }
        }
        fprintf(file, "\n");
    }

    fclose(file);

    printf("Matrix written to matrix.txt successfully.\n");

    // Free allocated memory
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}
