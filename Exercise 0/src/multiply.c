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
    if (ch < '0' || ch > '9') {
        return ERROR_NOT_INTEGER;
    }

    int number = ch - '0';
    // we must make sure before conversion that UINT_8 is not overflowed
    if (number < 0 || number > UINT8_MAX) {
        return ERROR_NOT_INTEGER;
    }

    *retNumber = (uint8_t) number;
    return RESULT_OK;
}

result number_at(char *arguments[], size_t index, uint8_t *retArg) {
    // make sure that argument is just a single character
    if (arguments[index + 1][1]) {
        return ERROR_NOT_INTEGER;
    }

    char ch = arguments[index + 1][0];
    return to_number(ch, retArg);
}

result numbers(int argc, char *arguments[], size_t amount, uint8_t *retNumbers) {
    // make sure that we are within arguments bounds
    if (argc != amount + 1) {
        return ERROR_OUT_OF_BOUNDS;
    }

    result rv;
    for (size_t index = 0; index < amount; index++) {
        rv = number_at(arguments, index, &retNumbers[index]);
        if (FAILED(rv)) {
            return rv;
        }
    }
    return RESULT_OK;
}

uint8_t multiply(uint8_t *numbers, size_t amount) {
    uint8_t mult = 1;
    for (size_t index = 0; index < amount; index++) {
        mult *= numbers[index];
    }
    return mult;
}

int main(int argc, char *argv[]) {
    uint8_t *arguments = malloc(EXPECTED_ARGUMENTS * sizeof(uint8_t));

    result rv = numbers(argc, argv, EXPECTED_ARGUMENTS, arguments);
    if (FAILED(rv)) {
        fprintf(stderr, "Error(%u): Check arguments\n", rv);
        exit(EXIT_FAILURE);
    }

    uint8_t mult = multiply(arguments, EXPECTED_ARGUMENTS);

    printf("%u * %u = %u\n", arguments[0], arguments[1], mult);

    free(arguments);

    return 0;
}
