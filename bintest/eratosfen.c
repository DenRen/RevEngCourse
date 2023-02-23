#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

unsigned read_number() {
    const unsigned min_number = 2;
    const unsigned max_number = 200000000;

    unsigned number = 0;
    if (scanf("%u", &number) != 1) {
        fprintf(stderr, "Failed to read number\n");
        return -1u;
    }

    if (number < min_number || number > max_number) {
        fprintf(stderr, "Number is out of range [%u:%u]\n",
                min_number, max_number);
        return -1u;
    }

    return number;
}

unsigned num_primes_naive(unsigned number) {
    const unsigned buf_size = number - 1;
    unsigned* buf = (unsigned*) calloc(buf_size, sizeof(unsigned));
    if (buf == NULL) {
        perror("calloc");
        return -1;
    }

    for (unsigned i = 2; i <= number; ++i) {
        buf[i - 2] = i;
    }

    unsigned p = 2;
    while (1) {
        unsigned step = p == 2 ? p : 2 * p;
        for (unsigned i = p * p; i <= number; i += step) {
            buf[i - 2] = 0;
        }

        for (unsigned i = p + 1; i <= number; ++i) {
            p = buf[i - 2];
            if (p != 0) {
                break;
            }
        }

        if (p * p > number) {
            break;
        }
    }

    unsigned num_primes = 0;
    for (unsigned i = 0; i < buf_size; ++i) {
        if (buf[i] != 0) {
            ++num_primes;
        }
    }

    free(buf);
    return num_primes;
}

unsigned get_bit_in_byte(const uint8_t* buf, unsigned i) {
    const unsigned byte_index = i >> 3;
    const uint8_t bit_index = i & 0b111;

    uint8_t byte = buf[byte_index];
    return byte & ((uint8_t)1 << bit_index);
}

unsigned get_bit(const uint8_t* buf, unsigned i) {
    return get_bit_in_byte(buf, i) != 0;
}

void reset_bit(uint8_t* buf, unsigned i) {
    const unsigned byte_index = i >> 3;
    const uint8_t bit_index = i & 0b111;
    buf[byte_index] &= ~((uint8_t)1 << bit_index);
}

unsigned bit_size2byte_size(unsigned bit_size) {
    return bit_size / 8 + ((bit_size % 8) != 0);
}

unsigned num_primes(unsigned number) {
    const unsigned buf_size_bits = number - 1;
    const unsigned buf_size_bytes = bit_size2byte_size(buf_size_bits);
    uint8_t* buf = (uint8_t*) malloc(buf_size_bytes);
    if (buf == NULL) {
        perror("calloc");
        return -1u;
    }

    memset(buf, 0xff, buf_size_bytes);

    unsigned p = 2;
    while (1) {
        unsigned step = p == 2 ? p : 2 * p;
        for (unsigned i = p * p; i <= number; i += step) {
            reset_bit(buf, i - 2);

        }

        for (unsigned i = p - 1; i < buf_size_bits; ++i) {
            if (get_bit_in_byte(buf, i)) {
                p = i + 2;
                break;
            }
        }

        if (p * p > number) {
            break;
        }

    }

    unsigned num_primes = 0;
    for (unsigned i = 0; i < buf_size_bits; ++i) {
        if (get_bit_in_byte(buf, i)) {
            ++num_primes;
        }
    }

    free(buf);
    return num_primes;
}

int main() {
#if 0
    unsigned number = 2;
    for (; number < 20000; ++number) {
        const unsigned ref = num_primes_naive(number);
        const unsigned res = num_primes(number);
        if (res != ref) {
            printf("Error\nnumber: %u\nref: %u\nres: %u\n", number, ref, res);
            return -1;
        }
    }

    for (; number < 3000000; number *= 2) {
        const unsigned ref = num_primes_naive(number);
        const unsigned res = num_primes(number);
        if (res != ref) {
            printf("Error\nnumber: %u\nref: %u\nres: %u\n", number, ref, res);
            return -1;
        }
    }

#else
    unsigned number = read_number();
    printf("%u\n", num_primes(number));
#endif

    return 0;
}