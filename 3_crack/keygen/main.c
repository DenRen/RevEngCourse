#include <stdio.h>
#include <stdint.h>

int main () {
		uint32_t wtf_number = 0;
		if (scanf("%u", &wtf_number) != 1) {
				return 1;
		}
		
		uint32_t key = 7530 - wtf_number; // What if ?... no-no, everything is fine
		printf("%u\n", key);
}
