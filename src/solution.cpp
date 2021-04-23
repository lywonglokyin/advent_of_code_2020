#include <time.h>
#include <stdio.h>

#include "solution.h"

void Solution::execute_and_time(){
    time_t start_time, end_time;

    time(&start_time);
    this->q1();
    time(&end_time);
    printf("Q1 finished in %4.3f seconds.\n", difftime(start_time, end_time));

    time(&start_time);
    this->q2();
    time(&end_time);
    printf("Q2 finished in %4.3f seconds.\n", difftime(start_time, end_time));
}