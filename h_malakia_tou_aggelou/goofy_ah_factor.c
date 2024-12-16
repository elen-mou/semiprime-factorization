#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>

void print_uint128(__uint128_t value); // print variables of type uint128 (works for signed to)
__uint128_t str_to_uint128(const char *str); // convert a string to a uint128 variable (also checks for letters in the string)
int string_check(const char *str); // checks the string to determine if it is invalid (empty or exceeds limit [0,2^127]), a number that can fit into 64 bits or one that can fit in 128 bits
int factorize_128(__uint128_t x); // starts the factorising process for factor of type uint128
int factorize(long long unsigned x); // starts the factorising process for factor of type long long unsigned
__uint128_t gcd_128(__uint128_t num1, __uint128_t num2); // Greatest Common Divisor for uint128
long long unsigned gcd(long long unsigned num1, long long unsigned num2); // Greatest Common Divisor for long long unsigned
bool prime_128(__uint128_t x); // checks if number is prime (128 bit version)
bool prime(long long unsigned x); // checks if number is prime (64 bit version)
long long unsigned trial_division(long long unsigned x); // Trial Division method to factorize numbers within range [0, 10^6]
long long unsigned wheel_factorization(long long unsigned x); // Wheel Factorisation method to factorize numbers within range [10^6 + 1, 10^8]
__uint128_t quadratic_sieve_128(__uint128_t x); // Quadratic Sieve Method to factorize numbers withtin range [2^63, 2^127]
long long unsigned quadratic_sieve(long long unsigned x); // Quadratic Sieve Method to factorize numbers withtin range [10^8 + 1, 2^63 - 1] (up to limit of llu)

int main(int argc, char *argv[]) {
    // check if user did not provide only 1 input
    if (argc != 2) {
        printf("Usage: %s <semiprime>\n", argv[0]); //argv[0] => name of executable program
        return 1;
    }

    int bit_range = string_check(argv[1]); //store the value of the string_check function (0,1 or 2)
    if (bit_range == 0) { // 0 for invalid input
        return 1;
    } else if (bit_range == 1) { // 1 for semipime that fits into long long unsigned
        long long unsigned semiprime = atoll(argv[1]); // convert string into llu
        if (factorize(semiprime) == 1) return 1; // failed to factorize
        else return 0; // factorisation successful
    } else if (bit_range == 2) { // 2 for semipime that fits into uint128 and not long long unsigned
        __uint128_t semiprime = str_to_uint128(argv[1]); // convert string into uint128
        if (factorize_128(semiprime) == 1) return 1; // failed to factorize
        else return 0; // factorisation successful
    } else return 1; // just in case anything goes wrong (0% chance)
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
    printf("%s\n", &buffer[i + 1]);
}

__uint128_t str_to_uint128(const char *str) {
    __uint128_t result = 0;
    while (*str) {
        if (!isdigit(*str)) {
            return 1;
        }
        result = result * 10 + (*str - '0');
        str++;
    }
    return result;
}

int string_check(const char *str) {
    // Check if the input string is valid (only digits)
    int len = strlen(str);
    if (len == 0) {
        return 0; // Invalid: empty string
    }
    // Use str_to_uint128 to convert the string to a number
    __uint128_t num = str_to_uint128(str);
    // Check if the number exceeds the range [0, 2^127]
    if (num > ((__uint128_t)1 << 127)) {
        return 0; // Invalid: exceeds 2^127
    }
    
    // Check if the number fits within the 64-bit unsigned integer range
    if (num <= UINT64_MAX) {
        return 1; // Fits in long long unsigned (64-bit)
    } else {
        return 2; // Fits in __uint128_t (128-bit)
    }
}

__uint128_t gcd_128(__uint128_t num1, __uint128_t num2) {
    if (num1 % num2 == 0) {
        return num2;
    } else {
        return gcd_128(num2, num1 % num2);
    }
}

long long unsigned gcd(long long unsigned num1, long long unsigned num2) {
    if (num1 % num2 == 0) {
        return num2;
    } else {
        return gcd(num2, num1 % num2);
    }
}

bool prime_128(__uint128_t x) {
    if (x <= 1) return false;
    if (x <= 3) return true;
    if (x % 2 == 0 || x % 3 == 0) return false;

    for (__uint128_t i = 5; i * i <= x; i += 6) {
        if (x % i == 0) return false;
        if (x % (i + 2) == 0) return false;
    }
    return true;
}

bool prime(long long unsigned x) {
    if (x <= 1) return false;
    if (x <= 3) return true;
    if (x % 2 == 0 || x % 3 == 0) return false;

    for (__uint128_t i = 5; i * i <= x; i += 6) {
        if (x % i == 0) return false;
        if (x % (i + 2) == 0) return false;
    }
    return true;
}

long long unsigned trial_division(long long unsigned x) {
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

// Wheel Factorization - Skips numbers divisible by 2, 3, or 5
long long unsigned wheel_factorization(long long unsigned x) {
    // Small primes to form the wheel (2, 3, 5)
    long long unsigned wheel[] = {2, 3, 5};  // Wheel for skipping multiples of 2, 3, and 5
    long long unsigned i = 7; // Start with 7 as it's not divisible by 2, 3, or 5

    // Check divisibility by 2, 3, or 5
    for (int j = 0; j < 3; j++) {
        if (x % wheel[j] == 0) {
            return wheel[j];  // Return the factor if divisible by 2, 3, or 5
        }
    }

    // Begin trial division loop using the wheel (skipping multiples of 2, 3, and 5)
    while (i * i <= x) {  // We only need to check up to sqrt(x)
        // Skip numbers divisible by 2, 3, or 5
        bool skip = false;
        for (int j = 0; j < 3; j++) {
            if (i % wheel[j] == 0) {
                skip = true;
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

__uint128_t quadratic_sieve_128(__uint128_t x) {
    x++;
    return 0;
}

// Function to perform Gaussian elimination over GF(2)
int gaussian_elimination(int** matrix, int num_rows, int num_cols, int* solution_vector) {
    // Initialize solution vector
    for (int i = 0; i < num_cols; i++) {
        solution_vector[i] = 0;  // Start with all zeros
    }

    int row = 0;  // Track the current row
    for (int col = 0; col < num_cols; col++) {
        // Find the row with a 1 in the current column
        int pivot_row = -1;
        for (int i = row; i < num_rows; i++) {
            if (matrix[i][col] == 1) {
                pivot_row = i;
                break;
            }
        }

        if (pivot_row == -1) {
            continue; // No 1 found in this column, skip to next column
        }

        // Swap rows to move pivot_row to the current row
        if (pivot_row != row) {
            for (int j = 0; j < num_cols; j++) {
                int temp = matrix[row][j];
                matrix[row][j] = matrix[pivot_row][j];
                matrix[pivot_row][j] = temp;
            }
        }

        // Eliminate all 1s below the pivot row in the current column
        for (int i = row + 1; i < num_rows; i++) {
            if (matrix[i][col] == 1) {
                for (int j = 0; j < num_cols; j++) {
                    matrix[i][j] ^= matrix[row][j];  // XOR operation mod 2 (elimination)
                }
            }
        }

        // Move to the next row
        row++;
    }

    // Back substitution (to fill in the solution_vector)
    for (int i = num_rows - 1; i >= 0; i--) {
        // If the row has a leading 1, assign the corresponding value in the solution_vector
        if (matrix[i][i] == 1) {
            solution_vector[i] = 1;
            // Eliminate the 1 in the current column for all rows above
            for (int j = i - 1; j >= 0; j--) {
                if (matrix[j][i] == 1) {
                    matrix[j][i] ^= matrix[i][i];  // XOR to eliminate
                }
            }
        }
    }

    return 0;  // Successfully completed Gaussian elimination
}


// Function to construct the matrix of exponent vectors
int** build_exponent_matrix(long long unsigned* q_values, int num_candidates, int* factor_base, int fb_size, int** exponent_vectors) {
    // Suppress unused parameter warnings
    (void)q_values;
    (void)factor_base;

    // Allocate memory for the matrix
    int** matrix = malloc(num_candidates * sizeof(int*));
    if (!matrix) {
        fprintf(stderr, "Memory allocation failed for exponent matrix\n");
        exit(1);
    }

    // Allocate memory for each row of the matrix
    for (int i = 0; i < num_candidates; i++) {
        matrix[i] = malloc(fb_size * sizeof(int));
        if (!matrix[i]) {
            fprintf(stderr, "Memory allocation failed for row %d in matrix\n", i);
            exit(1);
        }

        // Copy exponent vectors into the matrix
        for (int j = 0; j < fb_size; j++) {
            matrix[i][j] = exponent_vectors[i][j];  // Modulo 2 exponents
        }
    }

    return matrix;
}

// Debug print for factor_qx function
void factor_qx(long long unsigned qx, int* factor_base, int fb_size, int* exponent_vector) {
    printf("Factoring %llu: ", qx);
    for (int i = 0; i < fb_size; i++) {
        long long unsigned p = factor_base[i];
        int exponent = 0;
        while (qx % p == 0) {
            qx /= p;
            exponent++;
        }
        exponent_vector[i] = exponent % 2;
        printf("%d ", exponent_vector[i]);
    }
    printf("\n");
}

// Function to perform the sieve step
void sieve(long long unsigned* q_values, int num_candidates, int* factor_base, int fb_size) {
    // Create an array to store the exponent vectors for each Q(x)
    int** exponent_vectors = malloc(num_candidates * sizeof(int*));
    if (!exponent_vectors) {
        fprintf(stderr, "Memory allocation failed for exponent vectors\n");
        exit(1);
    }

    for (int i = 0; i < num_candidates; i++) {
        exponent_vectors[i] = malloc(fb_size * sizeof(int));
        if (!exponent_vectors[i]) {
            fprintf(stderr, "Memory allocation failed for exponent vector %d\n", i);
            exit(1);
        }
    }

    // Factor each Q(x) and update the exponent vectors
    for (int i = 0; i < num_candidates; i++) {
        factor_qx(q_values[i], factor_base, fb_size, exponent_vectors[i]);
    }

    // At this point, exponent_vectors contains the factorization of each Q(x) modulo 2
    // Print the exponent vectors for verification (optional)
    for (int i = 0; i < num_candidates; i++) {
        printf("Exponent vector for Q(x) = %llu: ", q_values[i]);
        for (int j = 0; j < fb_size; j++) {
            printf("%d ", exponent_vectors[i][j]);
        }
        printf("\n");
    }

    // Free memory
    for (int i = 0; i < num_candidates; i++) {
        free(exponent_vectors[i]);
    }
    free(exponent_vectors);
}

// Modular Exponentiation
long long unsigned mod_exp(long long unsigned base, long long unsigned exp, long long unsigned mod) {
    long long unsigned result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) result = (result * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

// Dynamic Smoothness Bound Calculation
long long unsigned dynamic_smoothness_bound(long long unsigned n) {
    long double ln_n = log(n);         // Natural log (ln(n))
    long double ln_ln_n = log(ln_n);  // Natural log of ln(n)
    long long unsigned B = (long long unsigned)exp(sqrt(ln_n * ln_ln_n) / 2.0); // Quadratic Sieve heuristic
    return B;
}

// Factor Base Generation
int* factor_base_generation(long long unsigned n, int B, int* size) {
    int* factor_base = malloc(B * sizeof(int));
    if (!factor_base) {
        fprintf(stderr, "Memory allocation failed for factor base\n");
        exit(1);
    }

    int count = 0;
    for (int p = 2; p <= B; p++) {
        if (prime(p)) {  // Check if p is prime
            // Check if p is a quadratic residue modulo n
            long long unsigned residue = mod_exp(n % p, (p - 1) / 2, p);
            if (residue == 1) {  // Quadratic residue
                factor_base[count++] = p;
            }
        }
    }

    *size = count;  // Update size with the count of primes in the factor base
    return factor_base;
}

// Quadratic Sieve Function
long long unsigned quadratic_sieve(long long unsigned x) {
    // Step 1: Calculate Smoothness Bound
    long long unsigned B = dynamic_smoothness_bound(x);
    printf("Smoothness bound (B): %llu\n", B);

    // Step 2: Generate Factor Base
    int fb_size;
    int* factor_base = factor_base_generation(x, B, &fb_size);
    printf("Factor base generated with %d primes.\n", fb_size);

    // Step 3: Generate Candidates and Q(x) Values
    long long unsigned sqrt_x = (long long unsigned)sqrtl((long double)x); // Initial sqrt of x
    int range = 10 * fb_size; // Number of candidates (adjustable)
    long long unsigned* candidates = malloc(range * sizeof(long long unsigned));
    long long unsigned* q_values = malloc(range * sizeof(long long unsigned));

    for (int k = 0; k < range; k++) {
        candidates[k] = sqrt_x + k;              // Generate x-values
        q_values[k] = candidates[k] * candidates[k] - x; // Compute Q(x) = x^2 - x
    }

    // Step 4: Perform sieve step
    sieve(q_values, range, factor_base, fb_size);

    // Step 5: Build exponent matrix
    int** exponent_vectors = malloc(range * sizeof(int*));
    for (int i = 0; i < range; i++) {
        exponent_vectors[i] = malloc(fb_size * sizeof(int));
    }
    exponent_vectors = build_exponent_matrix(q_values, range, factor_base, fb_size, exponent_vectors);

    // Step 6: Perform Gaussian Elimination on the exponent matrix
    int* solution_vector = malloc(range * sizeof(int));
    if (!solution_vector) {
        fprintf(stderr, "Memory allocation failed for solution vector\n");
        exit(1);
    }
    gaussian_elimination(exponent_vectors, range, fb_size, solution_vector);

    // Print the solution vector (optional for debugging)
    printf("Solution vector (dependencies):\n");
    for (int i = 0; i < range; i++) {
        printf("%d ", solution_vector[i]);
    }
    printf("\n");

    // Step 7: Identify the Q(x) values contributing to the dependency
    // The solution vector contains 1's at positions where the dependency exists
    long long unsigned product = 1;
    for (int i = 0; i < range; i++) {
        if (solution_vector[i] == 1) {
            product *= q_values[i];
        }
    }
    // Free allocated memory
    free(factor_base);
    free(candidates);
    free(q_values);
    free(solution_vector);
    for (int i = 0; i < range; i++) {
        free(exponent_vectors[i]);
    }
    free(exponent_vectors);

    // Step 8: Compute the GCD of the product with n
    long long unsigned factor = gcd(product, x);  // This gives a factor of x
    if (factor > 1 && factor < x) {
        printf("Non-trivial factor found: %llu\n", factor);
        return factor;
    } else {
        printf("No non-trivial factor found\n");
        return 1;  // No factor found
    }
}

// Function to factorize the semiprime using trial division
int factorize_128(__uint128_t x) {
    __uint128_t factor = quadratic_sieve_128(x);
    
    if (factor == x) {
        // If x is prime or no factor found (woan't happen for semiprimes 'cause I said so)
        return 1;
    }

    __uint128_t q = x / factor;  // Calculate the second factor

    if (prime(factor) && prime(q)) {  // Both factors must be prime
        // Print factors in ascending order

        // Need to check the max range of factors
        if (factor < q) {
            printf("Factors: ");
            print_uint128(factor);
            printf(" ");
            print_uint128(q);
            printf("\n");
        } else {
            printf("Factors: ");
            print_uint128(factor);
            printf(" ");
            print_uint128(q);
            printf("\n");
        }
        return 0;  // Return 0 to indicate successful factorization
    }
    return 1;  // Return 1 if factorization fails (this shouldn't happen for semiprimes)
}

int factorize(long long unsigned x) {
    long long unsigned factor;
    if (x <= pow(10,6)) {
        factor = trial_division(x); // Find a factor using trial division
    } else if (x <= pow(10,8)) {            
        factor = wheel_factorization(x);
    } else {
        factor = quadratic_sieve(x);
    }
    
    if (factor == x) {
        // If x is prime or no factor found (won't happen for semiprimes 'cause I said so)
        return 1;
    }

    long long unsigned q = x / factor;  // Calculate the second factor

    if (prime(factor) && prime(q)) {  // Both factors must be prime
        
        // Print factors in ascending order
        if (factor < q) {
            printf("Factors: %llu %llu\n", factor, q);
        } else {
            printf("Factors: %llu %llu\n", q, factor);
        }
        return 0;  // Return 0 to indicate successful factorization
    }
    return 1;  // Return 1 if factorization fails
}
