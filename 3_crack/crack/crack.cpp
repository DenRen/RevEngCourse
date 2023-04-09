#include <cstdio>
#include <cstdint>
#include <sys/stat.h>

const unsigned pos = 0x520;
uint8_t b_eq_code = 0xe0;

int main() {
    FILE* src = fopen("source", "rb");
    if (src == nullptr) {
        return -1;
    }

    fseek(src, 0, SEEK_END);
    const unsigned src_size = ftell(src);
    fseek(src, 0, SEEK_SET);

    if (pos >= src_size) {
        fclose(src);
        return -1;
    }

    FILE* dst = fopen("cracked", "wb");
    if (dst == nullptr) {
        fclose(src);
        return -1;
    }

    uint8_t page[4000];
    size_t read_size = 0;
    while(read_size = fread(page, 1, sizeof(page), src)) {
        fwrite(page, read_size, 1, dst);
    }

    fclose(src);

    fseek(dst, pos, SEEK_SET);
    fwrite(&b_eq_code, 1, 1, dst);
    fclose(dst);

    return 0;
}