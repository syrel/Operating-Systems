/* gcc -Wall -std=gnu99 zombies.c */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * Creates and instantly finishes a forked process producing
 * a so called "zombie" process.
 */
void create_zombie() {
	pid_t pid;
    // create a new process and store it's pid in order to detect what which
    // code branch to run in which process
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
    // for how many seconds a zombie process will live in the system
	unsigned int wait = 15;

    create_zombie();
    sleep(wait);

	return 0;
}
