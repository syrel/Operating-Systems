//
// Created by Aliaksei Syrel on 21.02.17.
//

#ifndef OS_EXERCISE_0_RESULTS_H_H
#define OS_EXERCISE_0_RESULTS_H_H

#define result int

#define RESULT_OK 0
#define RESULT_ERROR 1 << 1
#define ERROR_NOT_INTEGER 2 << 1
#define ERROR_OUT_OF_BOUNDS 3 << 1

#define FAILED(x) x != RESULT_OK

#endif //OS_EXERCISE_0_RESULTS_H_H
