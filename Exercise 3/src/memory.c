/* gcc -Wall ./memory.c -o memory */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
 * System used: macOSX Sierra 10.12.4 (16E195) Darwin 16.5.0
 */

/**
 * According to the exercise page size is 4kB = 4096 byte
 */
#define PAGE_SIZE 4096

/**
 * Return a virtual page number corresponding to a given address.
 * @param address - an address for which to find a page number
 * @return page number
 */
int calculate_page (uint32_t address) {
    // page number can be found by dividing an address by a page size
    // and discarding a fractional part (floor rounding) which
    // is a default behaviour of "/" operator in C
	return address / PAGE_SIZE;
}

/**
 * Return a distance in bytes from the start of a page to a given address
 * @param address - an address for which to find an offset
 * @param page - an (optional) page number that corresponds a given address
 * @return memory offset
 */
int calculate_offset (uint32_t address , int page) {
    // offset can be computed without the need of a page number
    // we can juts simply find a modulo of address and page size
    return address % PAGE_SIZE;
}

int main(int argc, char *argv[])
{
	long long_input;
	uint32_t address;
	int offset , page;

	if (argc != 2) {
		printf("You must provide a parameter as input!\n");
		return -1;
	} else {
		long_input = atol(argv[1]);
		long supremum = pow(2 , 8*sizeof(uint32_t));
		if (long_input < 0 || long_input >= supremum) {
			printf("You must enter a valid 32bit address as parameter!\n");
			return -1;
		} else {
			address = (uint32_t) long_input;
		}
	}

    page = calculate_page(address);
    offset = calculate_offset(address, page);

    // Output example:
    //The address 19986 contains:
    //page number = 4
    //offset = 3602

	printf("The address %d contains:\npage number = %d\noffset = %d\n", address, page, offset);

	return 0;
}
