/* gcc -Wall -pthread statistics.c */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <limits.h>
#include <sys/errno.h>
#include "results.h"

int max;
int min;
float avg;
size_t len;

/**
 * Computes and returns an average value of numbers in a given array
 * @param val - a pointer to an array of integers
 * @return average value
 */
void *average(void *val) {
    int* array = (int*) val;
    size_t index;
    int sum;

    sum = 0;
    for (index = 0; index < len; index++) {
        sum += array[index];
    }

    avg = (float) sum / len;

	return NULL;
}

/**
 * Finds out and return a minimum number in a given array
 * @param val - a pointer to an array of integers
 * @return minimum value
 */
void *minimum(void *val) {
	int* array = (int*) val;
    size_t index;
    min = INT_MAX;
    for (index = 0; index < len; index++) {
        min = array[index] < min ? array[index] : min;
    }

	return NULL;
}

/**
 * Finds out and return a minimum number in a given array
 * @param val - a pointer to an array of integers
 * @return maximum value
 */
void *maximum(void *val) {
    int* array = (int*) val;
    size_t index;
    max = INT_MIN;
    for (index = 0; index < len; index++) {
        max = array[index] > max ? array[index] : max;
    }

	return NULL;
}

/**
 * Query a number argument at a given index and store it at retArg address
 * @param arguments a list of arguments
 * @param index an index of a wanted number
 * @param retArg a pointer to returned number
 * @return
 *      RESULT_OK if argument at an index is an integer number
 *      ERROR_NOT_INTEGER if an argument at an index is not a valid number
 */
result number_at(char *arguments[], size_t index, int *retArg) {
    const char* argument = arguments[index + 1];
    char* endPtr;
    long number;
    errno = 0;

    number = strtol(argument, &endPtr, 10); // base it 10, we want decimal numbers

    // strtol allows us to handle string => long conversion errors.
    // check for possible errors and return ERROR_NOT_INTEGER if it is a case
    if (endPtr == argument || *endPtr != '\0' || ((number == LONG_MIN || number == LONG_MAX) && errno == ERANGE)) {
        return ERROR_NOT_INTEGER;
    }

    if (number < INT_MIN || number > INT_MAX) {
        return ERROR_NOT_INTEGER;
    }

    // it is safe to cast long to integer here, we performed a check before
    *retArg = (int) number;

    return RESULT_OK;
}

/**
 * Extract integer arguments of the program
 * @param argc - amount of program arguments
 * @param arguments - an array of program arguments
 * @param amount - amount of numbers to return
 * @param retNumbers - a pointer to an array of returned argument numbers
 * @return
 *      RESULT_OK if all arguments are valid numbers
 *      ERROR_NOT_INTEGER if not all arguments can be represented as integers
  *     ERROR_OUT_OF_BOUNDS if less arguments were passed than expected
 */
result numbers(int argc, char *arguments[], size_t amount, int *retNumbers) {
    result rv;
    // make sure that we are within arguments bounds
    if ((size_t)argc != amount + 1) {
        return ERROR_OUT_OF_BOUNDS;
    }

    {
        size_t index;
        for (index = 0; index < amount; index++) {
            rv = number_at(arguments, index, &retNumbers[index]);
            if (FAILED(rv)) {
                return rv;
            }
        }
    }

    return RESULT_OK;
}

int main(int argc, char *argv[])
{
	int *array; // use this to store the command line parameters as integers
    result rv;

    pthread_t thread0;
    pthread_t thread1;
    pthread_t thread2;

    // find out how many arguments were given
    len = (size_t) argc - 1;

    // make sure we have at least two arguments
    if (len < 2) {
        printf("You have to supply at least 2 integers as arguments!\n");
        exit(1);
    }

    // allocate memory for an array of integers of size `length`
    array = malloc(len * sizeof(int));
    if (!array) {
        printf("Failed to allocate array of numbers!\n");
        exit(1);
    }

    // parse given arguments as integers and write them in a given array
    rv = numbers(argc, argv, len, array);
    if (FAILED(rv)) {
        printf("Error(%d): check your input\n", rv);
        exit(rv);
    }

    // create parallel child threads and pass pointer to integer array as argument
    pthread_create(&thread0, NULL, minimum, array);
    pthread_create(&thread1, NULL, maximum, array);
    pthread_create(&thread2, NULL, average, array);

    // wait for all threads to finish computations
    pthread_join(thread0, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // don't forget to free previously allocated memory for an array
    free(array);

	printf("Average: %f\n" , avg);
	printf("Maximum: %i\n" , max);
	printf("Minimum: %i\n" , min);


	return 0;
}
