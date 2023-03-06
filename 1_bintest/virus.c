#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

unsigned get_bit_in_byte(const uint8_t* buf, unsigned i) {
    const unsigned byte_index = i >> 3;
    const uint8_t bit_index = i & 0b111;

    const uint8_t byte = buf[byte_index];
    const uint8_t mask = ((uint8_t)1 << bit_index);
    return byte & mask;
}

unsigned get_bit(const uint8_t* buf, unsigned i) {
    return get_bit_in_byte(buf, i) != 0;
}

void reset_bit(uint8_t* buf, unsigned i) {
    const unsigned byte_index = i >> 3;
    const uint8_t bit_index = i & 0b111;
    const uint8_t mask = ~((uint8_t)1 << bit_index);
    buf[byte_index] &= mask;
}

void set_bit(uint8_t* buf, unsigned i) {
    const unsigned byte_index = i >> 3;
    const uint8_t bit_index = i & 0b111;
    const uint8_t mask = ((uint8_t)1 << bit_index);
    buf[byte_index] |= mask;
}

unsigned bit_size2byte_size(unsigned bit_size) {
    return bit_size / 8 + ((bit_size % 8) != 0);
}

int main() {
    unsigned v = 0, n = 0;
    if (scanf("%u %u", &v, &n) != 2) {
        perror("scanf");
        return -1;
    }

    const unsigned buf_size_bits = n;
    const unsigned buf_size_bytes = bit_size2byte_size(buf_size_bits);
    uint8_t* buf = (uint8_t*) calloc(buf_size_bytes, 1);
    if (buf == NULL) {
        perror("calloc");
        return -1u;
    }

    for (unsigned i = 0; i < v; ++i) {
        unsigned X = 0;
        if (scanf("%u", &X) != 1) {
            perror("read X");
            free(buf);
            return -1;
        }

        unsigned step = X - 1;
        for (unsigned j = X; j < n; j += step) {
            set_bit(buf, j);
            ++step;
        }
    }

    unsigned num_virused = 0;
    for (unsigned i = 0; i < n; ++i) {
        num_virused += get_bit(buf, i);
    }
    printf("%u\n", num_virused);

    free(buf);
    return 0;
}