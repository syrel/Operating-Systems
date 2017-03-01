/* gcc -Wall -std=gnu99 zombies.c */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void create_zombie() {
	pid_t pid;
    pid = fork();
    if (pid < 0) {
        printf("Failed to create a process\n");
        exit(1);
    }

    // in child process pid is 0
    if (pid == 0) {
        exit(0); // instantly finish it
    }
}

int main(void)
{
	unsigned int wait = 15;

    create_zombie();
    sleep(wait);

	return 0;
}
