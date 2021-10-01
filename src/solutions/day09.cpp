#include <iostream>
#include <unordered_set>

#include "solution.h"
#include "utils.h"

class Day9 : public Solution {
   public:
    void q1() override {
        auto input = utils::parse_file_integer("./input/day9.txt");

        std::unordered_set<int> prev_num;
        int no_of_preamble = 25;

        prev_num.insert(input.begin(), input.begin() + no_of_preamble);

        for (size_t i = no_of_preamble; i < input.size(); ++i) {
            // Check if valid
            bool invalid = true;
            for (size_t j = i - no_of_preamble; j < i; ++j) {
                if (prev_num.find(input[i] - input[j]) != prev_num.end()) {
                    invalid = false;
                    break;
                }
            }

            if (invalid) {
                std::cout << "q1: " << input[i] << std::endl;
                return;
            } else {
                prev_num.erase(input[i - no_of_preamble]);
                prev_num.insert(input[i]);
            }
        }
    }
    void q2() override {
        const int INVALID_NUM = 50047984;

        auto input = utils::parse_file_integer("./input/day9.txt");
        size_t left_ptr = 0;
        size_t right_ptr = 0;
        int sum = input[0];

        while (true) {
            if (sum < INVALID_NUM) {
                ++right_ptr;
                sum += input[right_ptr];
            } else if (sum > INVALID_NUM) {
                sum -= input[left_ptr];
                ++left_ptr;
            } else {
                break;
            }
        }

        int min = input[left_ptr];
        int max = input[left_ptr];
        for (size_t i = left_ptr + 1; i <= right_ptr; ++i) {
            if (input[i] < min) {
                min = input[i];
            }
            if (input[i] > max) {
                max = input[i];
            }
        }
        std::cout << "q2: " << min + max << std::endl;
    }
};

int main() {
    Day9 solution;
    solution.execute_and_time();
}