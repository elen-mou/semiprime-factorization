#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// This function finds the greatest common divisor of two __uint128_t-type numbers.
__uint128_t gcd(__uint128_t num1, __uint128_t num2) {
    if (num1 % num2 == 0) {
        return num2;
    } else {
        return gcd(num2, num1 % num2);
    }
}

// This function checks if an int-type number is prime.
int is_prime(int n) {
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

// This function prints a __uint128_t-type number.
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

// This function performs trial division function without unrolling
// what's unrolling?
__uint128_t trial_division(__uint128_t x) {
    printf("Trial division\n");
    // Check small primes first
    if (x % 2 == 0) return 2;
    if (x % 3 == 0) return 3;
    
    // Standard trial division loop
    for (__uint128_t i = 5; i * i <= x; i += 6) {
        if (x % i == 0) return i;
        if (x % (i + 2) == 0) return i + 2;
    }
    return x;  // If no factor is found, return x itself (meaning it's prime)
}

// This function performs the Wheel Factorization method - 
// Skips numbers divisible by 2, 3, or 5.
__uint128_t wheel_factorization(__uint128_t x) {
    printf("Wheel factorization\n");
    // Small primes to form the wheel (2, 3, 5)
    __uint128_t wheel[] = {2, 3, 5};  // Wheel for skipping multiples of 2, 3, and 5
    __uint128_t i = 7; // Start with 7 as it's not divisible by 2, 3, or 5

    // Check divisibility by 2, 3, or 5
    for (int j = 0; j < 3; j++) {
        if (x % wheel[j] == 0) {
            return wheel[j];  // Return the factor if divisible by 2, 3, or 5
        }
    }

    // Begin trial division loop using the wheel (skipping multiples of 2, 3, and 5)
    while (i * i <= x) {  // We only need to check up to sqrt(x)
        // Skip numbers divisible by 2, 3, or 5
        int skip = 0; // skip = 0 until ... (acts as a flag)
        for (int j = 0; j < 3; j++) {
            if (i % wheel[j] == 0) {
                skip = 1; 
                break;
            }
        }
        
        if (!skip && x % i == 0) {
            return i;  // Found a factor
        }
        
        i += 2; // Skip even numbers (since all even numbers are divisible by 2)
    }

    // If no factor is found, return the number itself (it's prime)
    return x;
}

// This function checks if the number x is B-smooth .
int is_bsmooth(__uint128_t x, int *primes_arr, int prime_count) {
    for (int i = 0; i < prime_count; i++) {
        while (x % primes_arr[i] == 0) {
            x /= primes_arr[i];
        }
        if (x == 1) {
            return 1;  // early termination if x is reduced to 1
        }
    }
    return (x == 1);  // if x is successfully reduced to 1, it's B-smooth
}

// This function performs Gaussian elimination over Z2 (mod 2).
void gaussian_elimination(int **matr, int m, int n) {
    for (int i = 0; i < m; i++) {
        int pivot_row = i;
        // Find a row with a 1 in column i
        for (int j = i + 1; j < m; j++) {
            if (matr[j][i] == 1) {
                pivot_row = j;
                break;
            }
        }

        // Swap the rows if necessary
        if (pivot_row != i) {
            for (int j = 0; j < n; j++) {
                int temp = matr[i][j];
                matr[i][j] = matr[pivot_row][j];
                matr[pivot_row][j] = temp;
            }
        }

        // Eliminate all entries below the pivot
        for (int j = i + 1; j < m; j++) {
            if (matr[j][i] == 1) {
                for (int k = i; k < n; k++) {
                    matr[j][k] ^= matr[i][k];  // XOR to eliminate the entry
                }
            }
        }
    }

    // Backward substitution to find the solution
    int *result_vector = (int*)malloc(m * sizeof(int));

    if (result_vector == NULL) {
        printf("Memory allocation failed\n");
    } else {
        for (int i = m - 1; i >= 0; i--) {
            result_vector[i] = matr[i][n - 1];
            for (int j = i + 1; j < m; j++) {
                if (matr[i][j] == 1) {
                    result_vector[i] ^= result_vector[j];  // XOR to solve
                }
            }
        }
    }
}

// This function performs the Quadratic Sieve Factorization method
__uint128_t quadratic_sieve(__uint128_t N) {
    printf("Quadratic sieve\n"); // test print
    /*
    For numbers with aprox. 20 to 40 digits, the best value for B
    in order to find B-smooth numbers is about 30 to 50. So the 
    numbers we can try for B are: {29, 31, 37, 41, 43, 47, 53}.
    B-smooth numbers must only have factors that are less than or equal to
    the primes preceding B (meaning they are one of the following numbers:
    {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53}). In the beginning, we 
    could select B = 51 and slowly drop its value while checking if there 
    is a significant difference in the algorithm's accuracy every time we do so.


    STEPS OF THE QUADRATIC SIEVE ALGORITHM
    
    Supposing N is the number we want to factorize:
    1. Select B (for the first time we try to run the algorithm, B shall be 53)

    2. Find all primes less than or equal to B and put them in a list (because 
       we're not allowed to have a pre-generated list of primes). B-smooth 
       numbers must only have factors that are less than or equal to this 
       list of numbers.

    3. Calculate the square of every item on the list and store the modulo when
       dividing by N in another list.

    4. For each number on the list created in step 3, check if it is B-smooth 
       (this procedure requires factorization, but, as the numbers on the list 
       are quite small, trial division is enough - but, for every number where 
       a factor is found two times or more - e.g. 12 = 2^2 * 3, each factor only
       counts once and will be checked once). If it is B-smooth, it is added in a
       list.

    5. Linear algebra fancy stuff

    6. The solution vectors show the factors.
    */

    // Step 1: Initializing B as 53, according to which the primes list will be formed.
    int B = 53;
    
    // Step 2: Finding all primes up to B and storing them in an array.
    // There are 16 primes before 53, including 53.
    // BUT WE DONT KNOW THATTTT - SO MALLOC
    
    int primes_arr_counter = 0;
    for (int i = 2; i <= B; i++) { // Starting from 2 because 0, 1 are not primes
        if (is_prime(i)) {
            primes_arr_counter ++; // If a number from 2-53 is prime, 
                        // the value of counter is increased by 1.
        }
    }

    // Allocate memory dynamically for primes array
    int *primes_arr = (int*)malloc(primes_arr_counter * sizeof(int));

    if (primes_arr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    // Reset counter to 0 and fill the array with primes
    primes_arr_counter = 0;
    for (int i = 2; i <= B; i++) {
        if (is_prime(i)) {
            primes_arr[primes_arr_counter] = i;
            primes_arr_counter++;
        }
    }

    
    // Step 3: Calculating x^2 mod N for each x in the range [2, N]
    int bsmooth_counter = 0;

    int *bsmooth_arr = (int*)malloc(primes_arr_counter * sizeof(int));
    
    if (primes_arr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    // Setting a reasonable limit for x based on the size of N.
    __uint128_t max_x = 10000; 
    for (__uint128_t x = 2; x < N && x < max_x; x++) {
        __uint128_t squared_mod = (x * x) % N;
        printf("x: %llu, x^2 mod N: %llu\n", (unsigned long long)x, (unsigned long long)squared_mod);
        
        if (bsmooth_counter > primes_arr_counter) {
            break;
        }

        // Add logic to check if squared_mod is B-smooth and then store it in bsmooth_arr
        if (is_bsmooth(squared_mod, primes_arr, primes_arr_counter)) {
            bsmooth_arr[bsmooth_counter++] = squared_mod;
        }
    }


    // Check for x = -1!!!
    // For each number x from 2 to B, we're checking if x^2 mod N,
    // where N is the number we want to factorize, is B-smooth or not.
    // If it is, it is added in the dynamic array bsmooth[].

    /*
    for (int x = 2; x <= B; x++) {
        printf("Factors of %d:" (sqrt(x) % N));
    }
    */

    // Step 4: Setting up a matrix for linear algebra steps:
    // Building the matrix of quadratic residues modulo N.
    // Each row corresponds to an x^2 mod N value, and each column 
    // corresponds to a prime in the factor base.


    // Creating the matrix which holds the parity of the exponents of the factors mod 2.
    // It has m rows and n columns, where:
    int m = bsmooth_counter;
    int n = primes_arr_counter;
    
    int **matrix = (int **)malloc(m * sizeof(int *));  // allocating rows
    if (matrix == NULL) {
        printf("Memory allocation failed for matrix rows\n");
        return 1;
    }

    // Allocating columns for each row
    for (int i = 0; i < m; i++) {
        matrix[i] = (int *)malloc(n * sizeof(int));  // allocating columns (primes count)
        if (matrix[i] == NULL) {
            printf("Memory allocation failed for matrix columns\n");
            return 1;
        }
    }

    // Step 5: Performing Gaussian elimination on the matrix to find dependencies.
    // This algorithm will help find dependencies between rows
    // that give us potential factors.
    gaussian_elimination(matrix, m, n);

    if (is_prime_uint128(factor) && is_prime_uint128(q)) {  // Both factors must be prime
        // Prints factors in ascending order

        // Need to check the max range of factors
        if (factor < q) {
            printf("Factors: %llu %llu\n", factor, q);
        } else {
            printf("Factors: %llu %llu\n", q, factor);
        }
        return 0;  // Return 0 to indicate successful factorization
    } else {
        printf("crying\n");
    }


    free(primes_arr);
    free(bsmooth_arr);
    printf("End of Quadratic Sieve.\n");
    return 0;
}

// This function factorizes a given semiprime 
// using various methods, depending on its size.
int factorize(__uint128_t x) {
    unsigned long long factor = 0; // Initialized so as not to get a warning
    if (x <= pow(10,6)) {
        factor = trial_division(x); // finds a factor using trial division
    } else if (x <= pow(10,8)) {            
        factor = wheel_factorization(x); // finds a factor using wheel factorization
    }
    else if (x <= pow(10,20)) {
        factor = quadratic_sieve(x); // // finds a factor using the quadratic sieve method
    }

    if (factor == x) {
        // If x is prime or no factor found (shouldn't happen for semiprimes)
        printf("This number is not a semiprime.\n");
        return 1;
    }

    unsigned long long q = x / factor;  // Calculate the second factor

    if (is_prime_uint128(factor) && is_prime_uint128(q)) {  // Both factors must be prime
        // Prints factors in ascending order

        // Need to check the max range of factors
        if (factor < q) {
            printf("Factors: %llu %llu\n", factor, q);
        } else {
            printf("Factors: %llu %llu\n", q, factor);
        }
        return 0;  // Return 0 to indicate successful factorization
    }
    printf("here!\n");
    printf("This number is not a semiprime.\n");
    return 1;  // Return 1 if factorization fails, thus indicating
               // that the number is not a semiprime
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <semiprime>\n", argv[0]); 
        return 1;
    }

    // Converting the string argument to a __uint128_t
    __uint128_t semiprime = str_to_uint128(argv[1]);

    // Checking if the number is within the range [0, 2^127]
    if (!is_within_range(semiprime)) {
        printf("Input out of range, valid semiprime range is [0, 2^127].\n");
        return 1;
    }

    if (factorize(semiprime) == 1) return 1;
    else return 0;
}