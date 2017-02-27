//
// Created by Aliaksei Syrel on 21.02.17.
//

#include <stdio.h>
#include <stdlib.h>
#include "multiply.h"

#define EXPECTED_ARGUMENTS 2

/**
 * Converts a character representing a number to an integer, e.g '8' -> 8
 * @param ch - character to convert
 * @param retNumber - a pointer to converted integer
 * @return
 *  RESULT_OK if conversion was successful
 *  ERROR_NOT_INTEGER if a given character does not represent a number
 */
result to_number(char ch, uint8_t *retNumber) {
    int number;
    if (ch < '0' || ch > '9') {
        return ERROR_NOT_INTEGER;
    }

    number = ch - '0';
    // we must make sure before conversion that UINT_8 is not overflowed
    if (number < 0 || number > UINT8_MAX) {
        return ERROR_NOT_INTEGER;
    }

    *retNumber = (uint8_t) number;
    return RESULT_OK;
}

/**
 * Query a number argument at a given index and store it at retArg address
 * @param arguments a list of arguments
 * @param index an index of a wanted number
 * @param retArg a pointer to returned number
 * @return
 *      RESULT_OK if argument at an index is a number [0-9]
 *      ERROR_NOT_INTEGER if an argument at an index is not a valid number
 */
result number_at(char *arguments[], size_t index, uint8_t *retArg) {
    char ch;
    // make sure that argument is just a single character
    if (!arguments[index + 1][0]) {
        return ERROR_NOT_INTEGER;
    }

    if (arguments[index + 1][1]) {
        return ERROR_NOT_INTEGER;
    }


    ch = arguments[index + 1][0];
    return to_number(ch, retArg);
}

/**
 * Extract number arguments of the program
 * @param argc - amount of program arguments
 * @param arguments - an array of program arguments
 * @param amount - amount of numbers to return
 * @param retNumbers - a pointer to an array of returned argument numbers
 * @return
 *      RESULT_OK if all arguments are valid numbers
 *      ERROR_NOT_INTEGER if not all arguments can be represented as numbers [0-9]
  *     ERROR_OUT_OF_BOUNDS if less arguments were passed than expected
 */
result numbers(int argc, char *arguments[], size_t amount, uint8_t *retNumbers) {
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

/**
 * Return a result of multiplication of all integers in a given array of numbers
 * @param numbers - an array of numbers to multiply
 * @param amount - how many numbers to multiply
 * @return return of multiplication
 */
uint8_t multiply(uint8_t *numbers, size_t amount) {
    uint8_t mult;
    mult = 1;
    {
        size_t index;
        for (index = 0; index < amount; index++) {
            mult *= numbers[index];
        }
    }

    return mult;
}

int main(int argc, char *argv[]) {
    uint8_t *arguments;
    uint8_t mult;
    result rv;

    arguments = malloc(EXPECTED_ARGUMENTS * sizeof(uint8_t));

    // first we want to convert string arguments to a collection of numbers to multiply
    rv = numbers(argc, argv, EXPECTED_ARGUMENTS, arguments);
    if (FAILED(rv)) {
        fprintf(stderr, "Error(%u): Check arguments\n", rv);
        exit(EXIT_FAILURE);
    }

    // next we multiply then
    mult = multiply(arguments, EXPECTED_ARGUMENTS);

    // print
    printf("%u * %u = %u\n", arguments[0], arguments[1], mult);

    // and free allocated numbers array
    free(arguments);

    return 0;
}
