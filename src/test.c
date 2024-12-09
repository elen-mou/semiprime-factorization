#include <stdio.h>
#include <stdlib.h>

/*
// Function to check if a number is prime
int int_prime(int n) {
    if (n <= 1) return 0;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int B = 61;  // You can set B to any desired value, e.g., 53
    int *primes_arr;  // Pointer to store prime numbers
    int counter = 0;

    // First, find the number of primes <= B to determine array size
    for (int i = 2; i <= B; i++) {
        if (int_prime(i)) {
            counter++;  // Count how many primes are there
        }
    }

    // Allocate memory dynamically for primes array
    primes_arr = (int*)malloc(counter * sizeof(int));
    if (primes_arr == NULL) {
        // Handle memory allocation failure
        printf("Memory allocation failed\n");
        return 1;
    }

    // Reset counter to 0 and fill the array with primes
    counter = 0;
    for (int i = 2; i <= B; i++) {
        if (int_prime(i)) {
            primes_arr[counter] = i;
            counter++;
        }
    }

    // Optional: print the prime numbers to verify
    printf("Counter: %d\n", counter);
    printf("Primes up to %d: ", B);

    for (int i = 0; i < counter; i++) {
        printf("%d ", primes_arr[i]);
    }
    printf("\n");

    /*
    // After primes are found, you can extend the array size to 16 and initialize the rest to 0
    primes_arr = realloc(primes_arr, 16 * sizeof(int)); // Reallocate for a fixed size array (16 elements)
    for (int i = counter; i < 16; i++) {
        primes_arr[i] = 0;  // Initialize remaining elements to 0
    }

    // Optional: Print array after reallocating to check the values
    printf("Array after realloc and zero initialization:\n");
    for (int i = 0; i < 16; i++) {
        printf("%d ", primes_arr[i]);
    }
    printf("\n");

    // Don't forget to free the allocated memory
    free(primes_arr);

    return 0;
}
*/

__uint128_t prod_first_factors(__uint128_t n) {
    for (__uint128_t i = 2; i <= )
}