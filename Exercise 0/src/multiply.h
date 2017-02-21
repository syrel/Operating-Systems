//
// Created by Aliaksei Syrel on 21.02.17.
//

#ifndef OS_EXERCISE_0_MULTIPLY_H
#define OS_EXERCISE_0_MULTIPLY_H

#include <stdint.h>
#include "results.h"

/**
 * Converts a character representing a number to an integer, e.g '8' -> 8
 * @param ch - character to convert
 * @param retNumber - a pointer to converted integer
 * @return
 *  RESULT_OK if conversion was successful
 *  ERROR_NOT_INTEGER if a given character does not represent a number
 */
result to_number (char ch, uint8_t *retNumber);

#endif //OS_EXERCISE_0_MULTIPLY_H
