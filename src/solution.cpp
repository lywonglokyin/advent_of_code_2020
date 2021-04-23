#include <chrono>
#include <stdio.h>

#include "solution.h"

void Solution::execute_and_time(){
    typedef std::chrono::high_resolution_clock Clock;
    Clock::time_point start_time, end_time;

    start_time = Clock::now();
    this->q1();
    end_time = Clock::now();
    std::chrono::duration<double, std::milli> ms = end_time - start_time;
    printf("Q1 finished in %4.2f milliseconds.\n", ms.count());

    start_time = Clock::now();
    this->q2();
    end_time = Clock::now();
    ms = end_time - start_time;
    printf("Q1 finished in %4.2f milliseconds.\n", ms.count());
}