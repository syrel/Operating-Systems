/* gcc -Wall -std=gnu99 zombies.c */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pid_t create_zombie() {
	pid_t pid;
    pid = fork();
    if (pid < 0) {
        printf("Failed to create a process\n");
        exit(1);
    }

    // in child process pid is 0
    if (pid == 0) {
        printf("Exit child\n");
        exit(0); // instantly finish it
    }

    return pid;
}

int main(void)
{
	unsigned int wait = 15;
    pid_t pid;

    pid = create_zombie();
    printf("waiting on %d\n", pid);
    sleep(wait);

	return 0;
}
