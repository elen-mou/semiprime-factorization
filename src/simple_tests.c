#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAX_PRIMES 100  // Maximum primes in the factor base (adjust as needed)
#define MAX_ROWS 100    // Maximum rows in the matrix
#define MAX_COLS 100    // Maximum columns in the matrix

// Declare the function prototypes
int is_prime(int n);
__uint128_t str_to_uint128(const char *c);
int is_bsmooth(__uint128_t x, int *primes_arr, int prime_count);
void gaussian_elimination(int matrix[MAX_ROWS][MAX_COLS], int rows, int cols);

// This function finds primes up to a certain number (Sieve of Eratosthenes)
void find_primes_up_to(int limit, int *primes_arr, int *prime_count) {
    for (int i = 2; i <= limit; i++) {
        if (is_prime(i)) {
            primes_arr[*prime_count] = i;
            (*prime_count)++;
        }
    }
}

// Function to check if a number is prime (you already have this function)
// int is_prime(int n) {


// Convert string to __uint128_t (you already have this function)
// __uint128_t str_to_uint128(const char *c) {

/*
int prod_first_factors(__uint128_tv n) {
    for (unsigned long long i = 2; i * i <= n; i++) {
        if (is_prime(i) && n%i == 0) {
            for i 
        }
    }

}
*/
//  This function checks if the number x is B-smooth 
int is_bsmooth(__uint128_t x, int *primes_arr, int prime_count) {
    for (int i = 0; i < prime_count; i++) {
        while (x % primes_arr[i] == 0) {
            x /= primes_arr[i];
        }
        if (x == 1) {
            return 1;  // Early termination if x is reduced to 1
        }
    }
    return (x == 1);  // If x is reduced to 1, it's B-smooth
}

// Function for Gaussian elimination (for matrix operations)
void gaussian_elimination(int matrix[MAX_ROWS][MAX_COLS], int rows, int cols) {
    // This function should perform Gaussian elimination to reduce the matrix
    // and find dependencies (nontrivial factors) based on the quadratic residues.
    // Implement Gaussian elimination here...
}

// Quadratic Sieve algorithm
__uint128_t quadratic_sieve(__uint128_t N) {
    printf("Quadratic Sieve Start\n");

    // Step 1: Choose a B bound (initial choice of B = 53, as per your code)
    int B = 53; 
    printf("Chosen B = %d\n", B);

    // Step 2: Find all primes up to B and store them in an array
    int primes_arr[MAX_PRIMES];
    int prime_count = 0;
    find_primes_up_to(B, primes_arr, &prime_count);

    // Step 3: Calculate x^2 mod N for each x in the range [2, N]
    __uint128_t bsmooth_arr[MAX_ROWS]; // Array to store B-smooth numbers
    int bsmooth_counter = 0;
    
    for (__uint128_t x = 2; x < N; x++) {
        __uint128_t squared_mod = (x * x) % N;
        printf("x: %llu, x^2 mod N: %llu\n", (unsigned long long)x, (unsigned long long)squared_mod);
        
        // Check if x^2 mod N is B-smooth and add it to the bsmooth_arr if true
        if (is_bsmooth(squared_mod, primes_arr, prime_count)) {
            bsmooth_arr[bsmooth_counter++] = squared_mod;
        }
    }

    // Step 4: Setting up a matrix for linear algebra steps
    // Build the matrix of quadratic residues modulo N
    // Each row corresponds to an x^2 mod N value, and each column 
    // corresponds to a prime in the factor base.
    int matrix[MAX_ROWS][MAX_COLS] = {0};
    int rows = bsmooth_counter;
    int cols = prime_count;

    // Populate the matrix (this is a simplified example)
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (bsmooth_arr[i] % primes_arr[j] == 0) {
                matrix[i][j] = 1;  // Marking a '1' for prime divisibility
            }
        }
    }

    // Step 5: Perform Gaussian elimination on the matrix to find dependencies
    // Gaussian elimination will help find dependencies between rows
    // that give us potential factors.
    gaussian_elimination(matrix, rows, cols);

    // Step 6: Return the factors found (this part will depend on the results from Gaussian elimination)
    printf("Quadratic Sieve End\n");

    // You can return factors here once you've implemented Gaussian elimination and found dependencies.
    return 0;  // Placeholder for now
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <semiprime>\n", argv[0]);
        return 1;
    }

    // Convert the input number to __uint128_t
    __uint128_t semiprime = str_to_uint128(argv[1]);

    // Call the quadratic sieve on the number
    __uint128_t factor = quadratic_sieve(semiprime);

    // Output the result
    printf("Factor: %llu\n", (unsigned long long)factor);
    return 0;
}
