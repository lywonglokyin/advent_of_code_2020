#include <iostream>
#include <stdexcept>
#include <unordered_set>

#include "solution.h"
#include "utils.h"

class Day1 : public Solution {
   public:
    void q1() override {
        auto input = utils::parse_file_integer("input/day1.txt");
        std::unordered_set<int> hash_set(input.begin(), input.end());
        for (int i : input) {
            int target = 2020 - i;

            auto got = hash_set.find(target);
            if (got != hash_set.end()) {
                // Found
                int answer = i * target;
                std::cout << "Q1: " << answer << std::endl;
                return;
            }
        }
        throw std::runtime_error("Pair not exist!");
    }
    void q2() override {
        auto input = utils::parse_file_integer("input/day1.txt");
        std::unordered_set<int> hash_set(input.begin(), input.end());
        for (int i : input) {
            int target = 2020 - i;
            for (int j : input) {
                int second_target = target - j;

                auto got = hash_set.find(second_target);
                if (got != hash_set.end()) {
                    // Found
                    int answer = i * j * second_target;
                    std::cout << "Q2: " << answer << std::endl;
                    return;
                }
            }
        }
        throw std::runtime_error("Triplet not exist!");
    }
};

int main() {
    Day1 solution;
    solution.execute_and_time();
}