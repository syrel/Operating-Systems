/* gcc -Wall -pthread ./resources.c -o resources */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_RESOURCES 5

int available_resources = MAX_RESOURCES;
int times = 100000;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

/**
 * Perform a given "closure" with a provided argument wrapping it within a critical section
 * @param closure - block "closure" to evaluate
 * @param argument - "closure" parameter
 * @return "closure" return value
 */
int lock_during(int (*closure)(int), int argument) {
    int result = 0;
    pthread_mutex_lock(&mutex);  //lock the critical section
    result = closure(argument); // evaluate closure
    pthread_mutex_unlock(&mutex); //unlock the critical section
    return result;
}

/* decrease available_resources by count resources
 * return 0 if sufficient resources available,
 * otherwise return -1 */
int decrease_count (int count) {
    if (available_resources < count) {
        return -1;
    } else {
        available_resources -= count;
        printf("Locked %i resources, now available: %i\n" , count , available_resources);
        return 0;
    }
}

/* increase available resources by count */
int increase_count (int count) {
    if (count + available_resources > 5) {
        return -1;
    } else {
        available_resources += count;
        printf("Freed %i resources, now available: %i\n" , count , available_resources);
        return 0;
    }
}

/**
 * Thread safe version of decrease_count()
 */
int decrease_count_safe(int count) {
    return lock_during(decrease_count, count);
}

/**
 * Thread safe version of increase_count()
 */
int increase_count_safe(int count) {
    return lock_during(increase_count, count);
}

void *runTimes(void *null) {
	int i = 0 , result;
	while (i < times) {
		result = -1;
		while (result < 0) {result = decrease_count_safe(1);}
		result = -1;
		while (result < 0) {result = increase_count_safe(1);}
		i += 1;
	}

	return NULL;
}

int main(int argc, char *argv[])
{

	pthread_t thread1 , thread0;

	decrease_count(2);

    // create two threads
	pthread_create(&thread0, NULL, runTimes, NULL);
	pthread_create(&thread1, NULL, runTimes, NULL);

	// wait for all threads to finish computations
	pthread_join(thread0, NULL);
	pthread_join(thread1, NULL);

	printf("Currently available resources (should be 3): %i\n" , available_resources);

	return 0;
}
