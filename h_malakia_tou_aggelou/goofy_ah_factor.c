#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>

void print_uint128(__uint128_t value);
__uint128_t str_to_uint128(const char *str);
int string_check(const char *str);
int factorize_128(__uint128_t x);
int factorize(long long unsigned x);
__uint128_t gcd_128(__uint128_t num1, __uint128_t num2);
long long unsigned gcd(long long unsigned num1, long long unsigned num2);
bool prime_128(__uint128_t x);
bool prime(long long unsigned x);
long long unsigned trial_division(long long unsigned x);
__uint128_t quadratic_sieve_128(__uint128_t x);
long long unsigned quadratic_sieve(long long unsigned x);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <semiprime>\n", argv[0]);
        return 1;
    }

    int bit_range = string_check(argv[1]);
    if (bit_range == 0) {
        return 1;
    } else if (bit_range == 1) {
        long long unsigned semiprime = atoll(argv[1]);
        if (factorize(semiprime) == 1) return 1;
        else return 0;
    } else if (bit_range == 2) {
        __uint128_t semiprime = str_to_uint128(argv[1]);
        if (factorize_128(semiprime) == 1) return 1;
        else return 0;
    } else return 1; // just in case
    
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

long long unsigned quadratic_sieve(long long unsigned x) {
    x++;
    return 0;
}

// Function to factorize the semiprime using trial division
int factorize_128(__uint128_t x) {
    __uint128_t factor = quadratic_sieve_128(x);
    
    if (factor == x) {
        // If x is prime or no factor found (won't happen for semiprimes 'cause I said so)
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
