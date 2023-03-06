#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define NBIT_IPAGE 6

int main() {
    const uint32_t max_num_pages = 1u << NBIT_IPAGE;
    uint32_t phys_pages[max_num_pages];

    uint32_t num_pages = 0;
    if (scanf("%u", &num_pages) != 1 || num_pages > max_num_pages) {
        perror("scanf num pages");
        exit(-1);
    }

    for (unsigned i_page = 0; i_page < num_pages; ++i_page) {
        if (scanf("%x", &phys_pages[i_page]) != 1) {
            perror("scanf phys pages");
            exit(-1);
        }
    }

    uint32_t logic_addr = 0;
    if (scanf("%x", &logic_addr) != 1) {
        perror("scanf logic address");
        exit(-1);
    }

    const uint32_t i_page = logic_addr >> (32 - NBIT_IPAGE);
    if (i_page >= num_pages) {
        printf("error\n");
        return 0;
    }

    const uint32_t offset = (logic_addr << NBIT_IPAGE) >> NBIT_IPAGE;
    const uint32_t phys_addres = phys_pages[i_page] | offset;
    printf("%x\n", phys_addres);
}