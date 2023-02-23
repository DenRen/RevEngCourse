#include <stdio.h>
#include <stdint.h>

union addr_ipv4
{
    uint32_t addr;
    uint8_t dec[4];
};

int read_addr_ipv4(union addr_ipv4* addr) {
    uint8_t* decs = (uint8_t*)&addr->dec;
    return scanf("%hhu.%hhu.%hhu.%hhu", &decs[0], &decs[1], &decs[2], &decs[3]) != 4;
}

int print_addr_ipv4(const union addr_ipv4* addr) {
    const uint8_t* decs = (const uint8_t*)&addr->dec;
    return printf("%hhu.%hhu.%hhu.%hhu", decs[0], decs[1], decs[2], decs[3]);
}

void apply_broadcast_ipv4(union addr_ipv4* addr, const union addr_ipv4* mask) {
    addr->addr |= ~mask->addr;
}

int main() {
    union addr_ipv4 addr = {};
    if (read_addr_ipv4(&addr)) {
        fprintf(stderr, "Failed to read IPv4 address\n");
        return -1;
    }

    union addr_ipv4 mask = {};
    if (read_addr_ipv4(&mask)) {
        fprintf(stderr, "Failed to read IPv4 mask\n");
        return -1;
    }

    apply_broadcast_ipv4(&addr, &mask);

    print_addr_ipv4(&addr);
    putchar('\n');

    return 0;
}