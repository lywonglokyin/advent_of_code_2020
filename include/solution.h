#ifndef SOLUTION_H
#define SOLUTION_H

class Solution {
   public:
    virtual void q1() = 0;
    virtual void q2() = 0;

    void execute_and_time();
};

#endif