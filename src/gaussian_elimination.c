#include <stdio.h>
#include <stdlib.h>

#define MAX_ROWS 100
#define MAX_COLS 100

// This function performs Gaussian elimination .
// Note: mod 2 is the operation of this Gaussian elimination.
void gaussian_elimination_mod2(int matrix[MAX_ROWS][MAX_COLS], int rows, int cols) {
    // Starts performing Gaussian elimination
    for (int col = 0; col < cols; col++) {
        // Finds a row with a 1 in the current column
        if (matrix[col][col] == 0) {
            for (int row = col + 1; row < rows; row++) {
                if (matrix[row][col] == 1) {
                    // Swap rows
                    for (int k = 0; k < cols; k++) {
                        int temp = matrix[col][k];
                        matrix[col][k] = matrix[row][k];
                        matrix[row][k] = temp;
                    }
                    break;
                }
            }
        }

        // Eliminate all rows below this row
        for (int row = col + 1; row < rows; row++) {
            if (matrix[row][col] == 1) {
                // Add (XOR) the current row to the row to eliminate the value
                for (int k = 0; k < cols; k++) {
                    matrix[row][k] = (matrix[row][k] + matrix[col][k]) % 2;  // XOR operation mod 2
                }
            }
        }
    }

    printf("Reduced Matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    // Example matrix representing the prime factorization mod 2 of some quadratic residues
    // Each row corresponds to a quadratic residue modulo N in terms of prime factorization mod 2
    // The columns represent the exponents of primes in the factorization.

    // Example matrix (3 quadratic residues)
    // [1, 1, 0] -> x1^2 = 2^1 * 3^1
    // [0, 1, 1] -> x2^2 = 3^1 * 7^1
    // [1, 0, 1] -> x3^2 = 2^1 * 7^1
    int matrix[MAX_ROWS][MAX_COLS] = {
        {1, 1, 0}, // x1^2 mod N
        {0, 1, 1}, // x2^2 mod N
        {1, 0, 1}  // x3^2 mod N
    };
    
    int rows = 3; // Number of quadratic residues
    int cols = 3; // Number of primes in the factor base
    
    // Perform Gaussian elimination modulo 2
    gaussian_elimination_mod2(matrix, rows, cols);
    
    return 0;
}
