#include <stdio.h>
#include <stdint.h>
#include <assert.h>

int read_reverse_3_symb(uint8_t* buf) {
    for (unsigned i = 0; i < 3; ++i) {
        int symb = getchar_unlocked();
        if (symb == EOF) {
            return 0;
        }

        buf[2 - i] = (uint8_t) symb;
    }

    return 3;
}

uint8_t bin_2_base64_symb(uint8_t index) {
    assert(index <= 63);

    if (index <= 25) {
        return 'A' + index;
    }
    if (index <= 51) {
        return 'a' + index - 26;
    }
    if (index <= 61) {
        return '0' + index - 52;
    }

    return index == 62 ? '+' : '/';
}

union base64_chunk
{
    uint8_t in[3];
    uint32_t u32;
};

uint8_t get_hh_base64(union base64_chunk* chunk, unsigned i) {
    return (chunk->u32 >> 6 * (3 - i)) & 0b111111;
}

int main() {
    union base64_chunk chunk = {};
    while (read_reverse_3_symb(chunk.in)) {
        for (int i = 0; i < 4; ++i) {
            uint8_t hh = get_hh_base64(&chunk, i);
            uint8_t symb = bin_2_base64_symb(hh);
            putchar_unlocked(symb);
        }
    }
    putchar_unlocked('\n');
}