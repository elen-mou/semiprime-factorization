#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>

__uint128_t gcd(__uint128_t num1, __uint128_t num2) {
    if (num1 % num2 == 0) {
        return num2;
    } else {
        return gcd(num2, num1 % num2);
    }
}

// Function to check if a uint128-type number is prime
bool prime(__uint128_t x) {
    if (x <= 1) return false;
    if (x <= 3) return true;
    if (x % 2 == 0 || x % 3 == 0) return false;

    for (__uint128_t i = 5; i * i <= x; i += 6) {
        if (x % i == 0) return false;
        if (x % (i + 2) == 0) return false;
    }
    return true;
}

// Function to check if an int-type number is prime
bool int_prime(int x) {
    if (x <= 1) return false;
    if (x <= 3) return true;
    if (x % 2 == 0 || x % 3 == 0) return false;

    for (int i = 5; i * i <= x; i += 6) {
        if (x % i == 0) return false;
        if (x % (i + 2) == 0) return false;
    }
    return true;
}

// This function converts a string to a __uint128_t
__uint128_t str_to_uint128(const char *str) {
    __uint128_t result = 0;
    while (*str) {
        if (!isdigit(*str)) {
            fprintf(stderr, "Invalid character in input: %c\n", *str);
            exit(EXIT_FAILURE);
        }
        result = result * 10 + (*str - '0');
        str++;
    }
    return result;
}


// This function prints a __uint128_t type number
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

// This function checks if a number is within the range [0, 2^127]
int is_within_range(__uint128_t num) {
    __uint128_t max_value = ((__uint128_t)1 << 127); 
    return num <= max_value;  // Allow 2^127 as valid
}

// This function performs rial division function without unrolling
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

// Wheel Factorization - Skips numbers divisible by 2, 3, or 5
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

__uint128_t quadratic_sieve(__uint128_t x) {
    printf("Quadratic sieve\n");
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

    // Step 1
    int B = 53; // thought: we could initialize B with def instead,
                // so that it's easily changeable
    
    // Step 2
    int primes_arr[16]; // There are 16 primes before 53, including 53.
    
    int counter = 0;
    for (int i = 2; i <= B; i++) {
        if (int_prime(i)) {
            primes_arr[counter] = i; // If a number from 2-53 is prime, 
                                      // it is added to the array primes_arr
            counter ++;
        }
    }
    printf("AA\n");

    for (int i = counter; i <= 16; i++) {
        primes_arr[i] = 0; // the rest of the elements are initialized as 0 
                           // (I KNOW there's a better way with malloc probably)
    }
    /*
    printf("Size: %d\n", counter);
    for (int i = 0; i < counter; i++) {
        printf("%d\t", primes_arr[i]);
    }
    */

    // Step 3
    int calculated_arr[counter];
    for (int i = 0; i < counter; i++) {
        // find the square and do mod 2. The result is the i-th element
        // of the array calculated_arr
    }
    x++; // to avoid errors

    return 0;
}

// Function to factorize the semiprime using various methods, 
// depending on its size.
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

    if (prime(factor) && prime(q)) {  // Both factors must be prime
        // Prints factors in ascending order

        // Need to check the max range of factors
        if (factor < q) {
            printf("Factors: %llu %llu\n", factor, q);
        } else {
            printf("Factors: %llu %llu\n", q, factor);
        }
        return 0;  // Return 0 to indicate successful factorization
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

    // Convert the string argument to a __uint128_t
    __uint128_t semiprime = str_to_uint128(argv[1]);

    // Check if the number is within the range [0, 2^127]
    if (!is_within_range(semiprime)) {
        printf("Input out of range, valid semiprime range is [0, 2^127].\n");
        return 1;
    }

    // Test print
    printf("Input: ");
    print_uint128(semiprime);
    printf("\n");

    if (factorize(semiprime) == 1) return 1;
    else return 0;
}