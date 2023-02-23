#include <stdio.h>
#include <stdint.h>

uint8_t get_bit(uint8_t value, uint8_t index) {
    return (value & ((uint8_t)1 << index)) != 0;
}

int main() {
    int8_t number = 0;
    if (scanf("%hhi", &number) != 1) {
        fprintf(stderr, "Failed to read number\n");
        return -1;
    }

    for (unsigned i = 0; i < 8; ++i) {
        printf("%hhu", get_bit(number, 7 - i));
    }
    putchar('\n');

    return 0;
}