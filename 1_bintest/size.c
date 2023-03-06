#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define MANTISSA_SIZE(func_prefix, type_name)   \
unsigned mantissa_size_##func_prefix() {        \
    type_name val = 1;                          \
                                                \
    type_name addit = 0.5;                      \
    unsigned i = 0;                             \
    while ((val + addit) != val) {              \
        addit /= 2;                             \
        ++i;                                    \
    }                                           \
    return i;                                   \
}

MANTISSA_SIZE(float, float)
MANTISSA_SIZE(double, double)
MANTISSA_SIZE(long_double, long double)

unsigned mantissa_size_from_type_name(const char* type_name) {
    unsigned mantissa_size = -1u;
    if (!strcmp(type_name, "float")) {
        mantissa_size = mantissa_size_float();
    } else if (!strcmp(type_name, "double")) {
        mantissa_size = mantissa_size_double();
    } else if (!strcmp(type_name, "long double")) {
        mantissa_size = mantissa_size_long_double();
    }

    return mantissa_size;
}

int main() {
    char* type_name = NULL;
    size_t size = 0;
    if (getline(&type_name, &size, stdin) == -1 || strlen(type_name) == 1) {
        fprintf(stderr, "Failed to read type name\n");

        if (size) {
            free(type_name);
        }

        return -1;
    }

    type_name[strlen(type_name) - 1] = '\0';

    const unsigned mantissa_size = mantissa_size_from_type_name(type_name);
    if (mantissa_size == -1u) {
        fprintf(stderr, "Failed to detect type: \"%s\"\n", type_name);
        free(type_name);
        return -1;
    }

    printf("%u\n", mantissa_size);
    free(type_name);

    return 0;
}