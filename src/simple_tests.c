#include <stdio.h>
#include <math.h>

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

int is_prime(int n) {
    if (n <= 1) return 0;
    if (n <= 3) return 1;
    if (n % 2 == 0 || n % 3 == 0) return 0;

    for (int i = 5; i * i <= n; i+=6) {
        if (n % i == 0) return 0;
        if (n % (i + 2) == 0) return 0;
    }
    return 1;
}

int prod_first_factors(int B) {
    int flag = 1;
    for (int i = 2; i * i <= B; i++) {
        //printf("Number: %d\n", i);
        if (is_prime(i)) {
            //printf("Prime: %d\n", i);
            //printf("Prime: %d\n", n%i == 0);
            if (B%i == 0) {
                printf("Mod: ");
                print_uint128(n%i);
                printf("\n");
                int a = (int)pow(i, 2) % n;
                printf("Calc val: %d\n", a);
                flag = 0;
            }
        }
    }
    if (flag == 0) return 0;
    else return 1;

}

int main() {
    //int N = 2;
    //__uint128_t b = 93;
    int b = 53;
    //int a = (int)pow(3, 2) % b;
    //printf("%d\n", a);
    if (prod_first_factors(b) == 0) return 0;
    else return 1;
}