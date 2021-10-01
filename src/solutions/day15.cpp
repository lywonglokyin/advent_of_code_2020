#include <iostream>
#include <stack>
#include <unordered_map>

#include "solution.h"
#include "utils.h"

class Day15 : public Solution {
   public:
    void q1() override {
        std::unordered_map<int, int> history(
            {{12, 1}, {1, 2}, {16, 3}, {3, 4}, {11, 5}});

        int prev_num = 0;
        int curr_round = 7;

        while (curr_round != 2021) {
            int to_be_spoken = 0;
            if (history.find(prev_num) != history.end()) {
                // Not new
                to_be_spoken = (curr_round - 1) - history[prev_num];
            }
            history[prev_num] = curr_round - 1;
            prev_num = to_be_spoken;
            ++curr_round;
        }
        std::cout << "q1: " << prev_num << std::endl;
    }
    void q2() override {
        std::unordered_map<int, int> history(
            {{12, 1}, {1, 2}, {16, 3}, {3, 4}, {11, 5}});

        int prev_num = 0;
        int curr_round = 7;

        while (curr_round != 30000001) {
            int to_be_spoken = 0;
            if (history.find(prev_num) != history.end()) {
                // Not new
                to_be_spoken = (curr_round - 1) - history[prev_num];
            }
            history[prev_num] = curr_round - 1;
            prev_num = to_be_spoken;
            ++curr_round;
        }
        std::cout << "q2: " << prev_num << std::endl;
    }
};

int main() {
    Day15 solution;
    solution.execute_and_time();
}