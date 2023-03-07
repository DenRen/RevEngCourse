#include <stdint.h>
#include <stdio.h>

typedef uint8_t byte;
typedef uint16_t word;
typedef word adr;

byte mem[1u << 16];

#ifdef MY

byte b_read (adr a);            // читает из "старой памяти" mem байт с "адресом" a.
void b_write(adr a, byte val);  // пишет значение val в "старую память" mem в байт с "адресом" a.
word w_read (adr a);            // читает из "старой памяти" mem слово с "адресом" a.
void w_write(adr a, word val);  // пишет значение val в "старую память" mem в слово с "адресом" a.

void load_file();
void mem_dump(adr start, word n);

int main() {
    load_file();
    mem_dump(0x40, 15*2);
    mem_dump(0x200, 15*2);
}

#endif

byte b_read(adr a) {
    return mem[a];
}

void b_write(adr a, byte val) {
    mem[a] = val;
}

word w_read(adr a) {
    return *(word*) &mem[a & ~1u];
}

void w_write(adr a, word val) {
    *(word*) &mem[a & ~1u] = val;
}

static byte read_byte(int* perr) {
    byte byte = 0;
    const int res = scanf("%hhx", &byte);
    if (res == EOF || res == 0) {
        *perr = 1;
    }
    return byte;
}

static word read_word(int* perr) {
    word word = 0;
    const int res = scanf("%hx", &word);
    if (res == EOF || res == 0) {
        *perr = 1;
    }
    return word;
}

void load_file() {
    int err = 0;
    int* perr = &err;

    while (1) {
        adr addr = read_word(perr);
        if (err) {
            return;
        }

        word num_bytes = read_word(perr);
        if (err) {
            return;
        }

        for (word i_byte = 0; i_byte < num_bytes; ++i_byte) {
            b_write(addr + i_byte, read_byte(perr));
            if (err) {
                return;
            }
        }
    }
}

void mem_dump(adr start, word n) {
    for (word i_byte = 0; i_byte < n; i_byte += 2) {
        word addr = start + i_byte;
        word val = w_read(addr);
        printf("%06ho : %06ho\n", addr, val);
    }
}
