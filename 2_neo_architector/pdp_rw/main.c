#include <stdint.h>

typedef uint8_t byte;
typedef uint16_t word;
typedef word adr;

byte mem[1u << 16];

#ifdef MY

byte b_read (adr a);            // читает из "старой памяти" mem байт с "адресом" a.
void b_write(adr a, byte val);  // пишет значение val в "старую память" mem в байт с "адресом" a.
word w_read (adr a);            // читает из "старой памяти" mem слово с "адресом" a.
void w_write(adr a, word val);  // пишет значение val в "старую память" mem в слово с "адресом" a.

#include <stdio.h>
int main() {
    b_write(345, b_read(7));
    w_write(245, w_read(700));
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
