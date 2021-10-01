#include <iostream>
#include <string>

#include "solution.h"
#include "utils.h"

class Day2 : public Solution {
   public:
    void q1() override {
        int valid = 0;

        auto input = utils::parse_file_text("input/day2.txt");
        for (std::string s : input) {
            std::size_t dash_pos = s.find('-');
            std::size_t colon_pos = s.find(':');
            int min = std::stoi(s.substr(0, dash_pos));
            int max =
                std::stoi(s.substr(dash_pos + 1, colon_pos - dash_pos - 2));
            char target = s.at(colon_pos - 1);
            std::string password = s.substr(colon_pos + 2);

            int count = 0;
            for (char c : password) {
                if (c == target) {
                    ++count;
                }
            }
            if ((count >= min) && (count <= max)) {
                ++valid;
            }
        }
        std::cout << "q1: " << valid << std::endl;
    }
    void q2() override {
        int valid = 0;

        auto input = utils::parse_file_text("input/day2.txt");
        for (std::string s : input) {
            std::size_t dash_pos = s.find('-');
            std::size_t colon_pos = s.find(':');
            int pos1 = std::stoi(s.substr(0, dash_pos));
            int pos2 =
                std::stoi(s.substr(dash_pos + 1, colon_pos - dash_pos - 2));
            char target = s.at(colon_pos - 1);
            std::string password = s.substr(colon_pos + 2);

            if ((password.at(pos1 - 1) == target) !=
                (password.at(pos2 - 1) == target)) {
                ++valid;
            }
        }
        std::cout << "q2: " << valid << std::endl;
    }
};

int main() {
    Day2 solution;
    solution.execute_and_time();
}