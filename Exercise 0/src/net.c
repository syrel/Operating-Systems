/* gcc -Wall net.c */

#include <stdio.h>
#include <stdint.h>

int main(void)
{
	uint8_t add[] = {129, 169,  25, 100};
	uint8_t sub[] = {255, 255, 240,   0};
	uint8_t net[4];

    size_t length = sizeof(net) / sizeof(net[0]);
	for (size_t i = 0; i < length; i++) {
        net[i] = add[i] & sub[i];
	}

	printf("net address: %u.%u.%u.%u\n", net[0], net[1], net[2], net[3]);

	return 0;
}
