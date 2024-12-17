#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>



// This function checks if an int-type number is prime.
int is_prime(int n) {
    printf("is_prime: Checking if %d is prime.\n", n);
    if (n <= 1) return 0;
    if (n <= 3) return 1;
    if (n % 2 == 0 || n % 3 == 0) return 0;

    for (int i = 5; i * i <= n; i+=6) {
        if (n % i == 0 || n % (i + 2) == 0) return 0;
    }
    return 1;
}
// This function checks if a __uint128_t-type number is prime.
int is_prime_uint128(__uint128_t n) {
    if (n <= 1) return 0;
    if (n <= 3) return 1;
    if (n % 2 == 0 || n % 3 == 0) return 0;

    for (__uint128_t i = 5; i * i <= n; i += 6) {
        if (n % i == 0) return 0;
        if (n % (i + 2) == 0) return 0;
    }
    return 1;
}
// This function converts a string to a __uint128_t-type number.
__uint128_t str_to_uint128(const char *c) {
    __uint128_t result = 0;
    while (*c) {
        if (!isdigit(*c)) {
            fprintf(stderr, "Invalid character in input: %c\n", *c);
            exit(EXIT_FAILURE);
        }
        result = result * 10 + (*c - '0');
        c++;
    }
    return result;
}

void print_uint128(__uint128_t value) {
    if (value == 0) {
        printf("0");
        return;
    }

    char buffer[40] = {0}; // Enough to hold 39 digits of a 128-bit integer
    int i = 38;
    while (value > 0) {
        buffer[i--] = '0' + (value % 10);
        value /= 10;
    }
    printf("%s", &buffer[i + 1]);
}
// This function checks if a __uint128_t-number is within the range [0, 2^127].
int is_within_range(__uint128_t num) {
    __uint128_t max_value = ((__uint128_t)1 << 127); 
    return num <= max_value;  // Allow 2^127 as valid
}

// This function finds the greatest common divisor of two __uint128_t-type numbers.
__uint128_t gcd(__uint128_t num1, __uint128_t num2) {
    if (num2 == 0) {
        printf("gcd: num2 is 0, returning num1: ");
        print_uint128(num1);
        printf("\n");
        return num1;
    }
    printf("gcd: num1: ");
    print_uint128(num1);
    printf(", num2: ");
    print_uint128(num2);
    printf("\n");
    return gcd(num2, num1 % num2);
}

// This function checks if x is smooth with respect to primes in the array.
int is_bsmooth(__uint128_t x, int *primes_arr, int prime_count) {
    printf("is_bsmooth: Checking if %llu is smooth with respect to primes.\n", (unsigned long long)x);
    for (int i = 0; i < prime_count; i++) {
        while (x % primes_arr[i] == 0) {
            x /= primes_arr[i];
        }
        if (x == 1) {
            return 1;  // x is smooth
        }
    }
    return (x == 1);  // If x becomes 1 after all divisions, it's smooth
}

// This function performs trial division without unrolling.
__uint128_t trial_division(__uint128_t x) {
    printf("trial_division: Starting trial division for %llu.\n", (unsigned long long)x);

    if (x % 2 == 0) return 2;
    if (x % 3 == 0) return 3;
    
    for (__uint128_t i = 5; i * i <= x; i += 6) {
        if (x % i == 0) return i;
        if (x % (i + 2) == 0) return i + 2;
    }
    return x;  // If no factor is found, return x itself (meaning it's prime)
}

// This function performs the Wheel Factorization method.
__uint128_t wheel_factorization(__uint128_t x) {
    printf("wheel_factorization: Starting wheel factorization for %llu.\n", (unsigned long long)x);

    __uint128_t wheel[] = {2, 3, 5}; 
    __uint128_t i = 7; 

    for (int j = 0; j < 3; j++) {
        if (x % wheel[j] == 0) {
            return wheel[j]; 
        }
    }

    while (i * i <= x) {
        int skip = 0; 
        for (int j = 0; j < 3; j++) {
            if (i % wheel[j] == 0) {
                skip = 1; 
                break;
            }
        }
        
        if (!skip && x % i == 0) {
            return i; 
        }
        
        i += 2; 
    }

    return x;
}

// Gaussian elimination (simplified).
void gaussian_elimination(int **matr, int m, int n) {
    printf("gaussian_elimination: Starting Gaussian elimination.\n");

    for (int i = 0; i < m; i++) {
        int pivot_row = i;
        for (int j = i + 1; j < m; j++) {
            if (matr[j][i] == 1) {
                pivot_row = j;
                break;
            }
        }

        if (pivot_row != i) {
            for (int j = 0; j < n; j++) {
                int temp = matr[i][j];
                matr[i][j] = matr[pivot_row][j];
                matr[pivot_row][j] = temp;
            }
        }

        for (int j = i + 1; j < m; j++) {
            if (matr[j][i] == 1) {
                for (int k = i; k < n; k++) {
                    matr[j][k] ^= matr[i][k];  
                }
            }
        }
    }

    int *result_vector = (int*)malloc(m * sizeof(int));

    if (result_vector == NULL) {
        printf("Memory allocation failed\n");
        free(result_vector);
    } else {
        for (int i = m - 1; i >= 0; i--) {
            result_vector[i] = matr[i][n - 1];
            for (int j = i + 1; j < m; j++) {
                if (matr[i][j] == 1) {
                    result_vector[i] ^= result_vector[j];  
                }
            }
        }
    }
}

// Quadratic sieve (basic version).
__uint128_t quadratic_sieve(__uint128_t N) {
    printf("quadratic_sieve: Starting quadratic sieve for N = ");
    print_uint128(N);
    printf("\n");

    int B = 53;
    
    int primes_arr_counter = 0;
    for (int i = 2; i <= B; i++) { 
        if (is_prime(i)) {
            primes_arr_counter++;
        }
    }

    int *primes_arr = (int*)malloc(primes_arr_counter * sizeof(int));
    if (primes_arr == NULL) {
        printf("Memory allocation failed\n");
        free(primes_arr);
        return 1;
    }

    primes_arr_counter = 0;
    for (int i = 2; i <= B; i++) {
        if (is_prime(i)) {
            primes_arr[primes_arr_counter] = i;
            primes_arr_counter++;
        }
    }

    int bsmooth_counter = 0;
    int *bsmooth_arr = (int*)malloc(primes_arr_counter * sizeof(int));
    
    if (bsmooth_arr == NULL) {
        printf("Memory allocation failed\n");
        free(bsmooth_arr);
        free(primes_arr);
        return 1;
    }

    __uint128_t max_x = 500; 
    for (__uint128_t x = 2; x < N && x < max_x; x++) {
        __uint128_t squared_mod = (x * x) % N;

        if (bsmooth_counter > primes_arr_counter) {
            break;
        }

        if (is_bsmooth(squared_mod, primes_arr, primes_arr_counter)) {
            bsmooth_arr[bsmooth_counter++] = squared_mod;
        }
    }

    int m = bsmooth_counter;
    int n = primes_arr_counter;
    
    int **matrix = (int **)malloc(m * sizeof(int *));
    if (matrix == NULL) {
        printf("Memory allocation failed for matrix rows\n");
        free(matrix);
        free(primes_arr);
        free(bsmooth_arr);
        return 1;
    }

    for (int i = 0; i < m; i++) {
        matrix[i] = (int *)malloc(n * sizeof(int));  
        if (matrix[i] == NULL) {
            printf("Memory allocation failed for matrix columns\n");
            free(matrix);
            free(primes_arr);
            free(bsmooth_arr);
            return 1;
        }
    }

    // Fill the matrix with appropriate values
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = 0;
        }
    }

    return 0;
}

// Factorization function
int factorize(__uint128_t x) {
    printf("factorize: Starting factorization for %llu.\n", (unsigned long long)x);
    
    __uint128_t factor = 0; // Initialized so as not to get a warning
    if (x <= pow(10,6)) {
        printf("factorize: Using trial division\n");
        factor = trial_division(x); // finds a factor using trial division
    } else if (x <= pow(10,8)) {            
        printf("factorize: Using wheel factorization\n");
        factor = wheel_factorization(x); // finds a factor using wheel factorization
    }
    else if (x <= pow(10,20)) {
        printf("factorize: Using quadratic sieve\n");
        factor = quadratic_sieve(x); // finds a factor using the quadratic sieve method
    }

    if (factor == x) {
        // If x is prime or no factor found (shouldn't happen for semiprimes)
        printf("This number is not a semiprime.\n");
        return 1;
    }

    __uint128_t q = x / factor;  // Calculate the second factor

    if (is_prime_uint128(factor) && is_prime_uint128(q)) {  // Both factors must be prime
        // Prints factors in ascending order
        printf("Factors found: %llu and %llu\n", (unsigned long long)factor, (unsigned long long)q);
        return 0;
    }
    printf("This number is not a semiprime.\n");
    return 1;  // Return 1 if factorization fails, thus indicating
               // that the number is not a semiprime
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <semiprime>\n", argv[0]); 
        return 1;
    }

    __uint128_t semiprime = str_to_uint128(argv[1]);

    // Checking if the number is within the range [0, 2^127]
    if (!is_within_range(semiprime)) {
        printf("Input out of range, valid semiprime range is [0, 2^127].\n");
        return 1;
    }

    if (factorize(semiprime) == 1) return 1;
    else return 0;
}
