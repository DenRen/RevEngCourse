#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

unsigned gcd(unsigned a, unsigned b) {
    unsigned temp = 0;
    while (b != 0) {
        temp = a % b;

        a = b;
        b = temp;
    }

    return a;
}

void fill_A(unsigned* A, unsigned n) {
    for (unsigned i = 0; i < n; ++i) {
        const unsigned row = i * n;
        A[row + i] = i + 1;

        for (unsigned j = i + 1; j < n; ++j) {
            A[row + j] = A[i + n * j] = gcd(i + 1, j + 1);
        }
    }
}

void fill_B(unsigned* B, unsigned n) {
    for (unsigned i = 0; i < n; ++i) {
        const unsigned row = i * n;
        B[row + i] = n - i + 1;

        for (unsigned j = i + 1; j < n; ++j) {
            B[row + j] = B[i + n * j] = gcd(n - i + 1, n - j + 1);
        }
    }
}

void print_qm(unsigned* M, unsigned n) {
    unsigned pos = 0;
    for (unsigned i = 0; i < n; ++i) {
        for (unsigned j = 0; j < n; ++j) {
            printf("%u ", M[pos++]);
        }
        putchar('\n');
    }
}

unsigned calc_num_div_mul(unsigned* A, unsigned* B, unsigned n, unsigned d) {
    unsigned num_div = 0;

    for (unsigned i = 0; i < n; ++i) {
        const unsigned row_A = i * n;
        for (unsigned j = 0; j < n; ++j) {
            const unsigned row_B = j * n;

            unsigned res = 0;
            for (unsigned k = 0; k < n; ++k) {
                res += A[row_A + k] * B[row_B + k];
            }

            num_div += ((res % d) == 0);
        }
    }

    return num_div;
}

int main() {
    unsigned n = 0, d = 0;
    if (scanf("%u %u", &n, &d) != 2) {
        return -1;
    }

    if (n == 0) {
        printf("0\n");
        return 0;
    } else if (d == 1) {
        printf("%u\n", n * n);
        return 0;
    }

    unsigned* A = calloc(n * n, sizeof(unsigned));
    unsigned* B = calloc(n * n, sizeof(unsigned));

    fill_A(A, n);
    fill_B(B, n);

    // print_qm(A, n);
    // putchar('\n');
    // print_qm(B, n);

    unsigned num_div = calc_num_div_mul(A, B, n, d);
    printf("%u\n", num_div);

    free(A);
    free(B);
}