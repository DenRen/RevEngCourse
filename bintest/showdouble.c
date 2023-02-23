#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

union all_floats
{
    float fl;
    double dl;
    long double ldl;
};

union float_repr {
    union all_floats val;
    uint8_t bytes[sizeof(union all_floats)];
};

const char* type_name_check(const char* type_name, const char* name) {
    if (!strncmp(type_name, name, strlen(name))) {
        return type_name + strlen(name) + 1;
    }
    
    return NULL;
}

int read_float(const char* type_name, union float_repr* repr, unsigned* num_bytes) {
    const char* val_str = NULL;
    if ((val_str = type_name_check(type_name, "float"))) {
        if (sscanf(val_str, "%f", &repr->val.fl) != 1) {
            fprintf(stderr, "Failed to read float from \"%s\"\n", val_str);
            return -1;
        }
        *num_bytes = sizeof(repr->val.fl);
    } else if ((val_str = type_name_check(type_name, "double"))) {
        if (sscanf(val_str, "%lf", &repr->val.dl) != 1) {
            fprintf(stderr, "Failed to read double from \"%s\"\n", val_str);
            return -1;
        }
        *num_bytes = sizeof(repr->val.dl);
    } else if ((val_str = type_name_check(type_name, "long double"))) {
        if (sscanf(val_str, "%Lf", &repr->val.ldl) != 1) {
            fprintf(stderr, "Failed to read long double from \"%s\"\n", val_str);
            return -1;
        }
        *num_bytes = sizeof(repr->val.ldl);
    } else {
        return -1;
    }

    return 0;
}

unsigned get_bit_from_byte(uint8_t byte, unsigned i) {
    const uint8_t mask = ((uint8_t)1 << i);
    return (byte & mask) != 0;
}

void print_byte(uint8_t byte) {
    for (unsigned i = 0; i < 8; ++i) {
        putchar('0' + get_bit_from_byte(byte, 7 - i));

        if (i == 3) {
            putchar(' ');
        }
    }
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
    
    union float_repr repr = {};
    unsigned num_bytes = 0;
    if (read_float(type_name, &repr, &num_bytes) == -1) {
        fprintf(stderr, "Failed to detect type: \"%s\"\n", type_name);
        free(type_name);
        return -1;
    }

    print_byte(repr.bytes[num_bytes - 1]);
    for (unsigned i_byte = 1; i_byte < num_bytes; ++i_byte) {
        putchar(' ');
        print_byte(repr.bytes[num_bytes - 1 - i_byte]);
    }
    putchar('\n');

    free(type_name);
    return 0;
}