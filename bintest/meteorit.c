#include <stdio.h>
#include <stdint.h>

union data
{
    uint64_t u64;
    uint8_t arr[8];
    uint32_t a32[2];
};

union data convert(union data x);

int main() {
    {
        union data val;
        val.u64 = 0x0011223344556677;

        val = convert(val);
        if (val.u64 != 0x7766554433221100) {
            printf("Error!\n");
        } else {
            printf("Good!\n");
        }
    }

    union data val;
    scanf("%zu", &val.u64);
    printf("%zu\n", convert(val));
}

// 0 1 2 3 4 5 6 7
// 7 6 5 4 3 2 1 0
union data convert(union data x) {
    for (unsigned i = 0; i < 4; ++i) {
        uint8_t tmp_u8 = x.arr[i];
        x.arr[i] = x.arr[7 - i];
        x.arr[7 - i] = tmp_u8;
    }
    return x;
}