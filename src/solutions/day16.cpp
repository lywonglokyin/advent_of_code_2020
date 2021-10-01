#include <array>
#include <fstream>
#include <iostream>

#include "solution.h"
#include "utils.h"

class Day16 : public Solution {
   public:
    void q1() override {
        auto input = utils::parse_file_text("./input/day16.txt");
        const size_t FIELD_RULE_LINE_END = 19;
        // const size_t MY_TICKET_LINE = 22;
        const size_t NEARBY_TICKET_LINE_START = 25;

        const size_t BOOL_ARRAY_SIZE = 1000;
        bool valid[BOOL_ARRAY_SIZE] = {
            false};  // Use fixed size array to indicate if a value is valid.

        for (size_t i = 0; i <= FIELD_RULE_LINE_END; ++i) {
            auto pair = utils::split_as_pair(input[i], ':');
            auto range_pair = utils::split_as_pair(pair.second, 'o');
            auto first_range_pair = utils::split_as_pair(range_pair.first, '-');
            for (int j = std::stoi(first_range_pair.first);
                 j <= std::stoi(first_range_pair.second); ++j) {
                valid[j] = true;
            }
            auto second_range_pair =
                utils::split_as_pair(range_pair.second.substr(2), '-');
            for (int j = std::stoi(second_range_pair.first);
                 j <= std::stoi(second_range_pair.second); ++j) {
                valid[j] = true;
            }
        }

        // auto my_ticket = utils::split(input[MY_TICKET_LINE], ',');
        // auto my_ticket_nums = utils::stringvec_to_intvec(my_ticket);

        int sum = 0;
        for (size_t i = NEARBY_TICKET_LINE_START; i < input.size(); ++i) {
            auto nearby_ticket = utils::split(input[i], ',');
            auto nearby_ticket_nums = utils::stringvec_to_intvec(nearby_ticket);
            for (int num : nearby_ticket_nums) {
                if ((num < 0) ||
                    (static_cast<size_t>(num) >= BOOL_ARRAY_SIZE) ||
                    !valid[num]) {
                    sum += num;
                }
            }
        }
        std::cout << "q1: " << sum << std::endl;
    }
    void q2() override {
        auto input = utils::parse_file_text("./input/day16q2.txt");

        const size_t FIELD_RULE_LINE_END = 19;
        const size_t MY_TICKET_LINE = 22;
        const size_t NEARBY_TICKET_LINE_START = 25;

        const size_t NUM_OF_FIELDS = 20;
        bool not_possible[NUM_OF_FIELDS][NUM_OF_FIELDS] = {
            false};  // e.g. [0][1] = true means the 0th col could not be the
                     // 1st field.

        const size_t BOOL_ARRAY_SIZE = 1000;
        bool valid[NUM_OF_FIELDS][BOOL_ARRAY_SIZE] = {false};

        for (size_t i = 0; i <= FIELD_RULE_LINE_END; ++i) {
            auto pair = utils::split_as_pair(input[i], ':');
            auto range_pair = utils::split_as_pair(pair.second, 'o');
            auto first_range_pair = utils::split_as_pair(range_pair.first, '-');
            for (int j = std::stoi(first_range_pair.first);
                 j <= std::stoi(first_range_pair.second); ++j) {
                valid[i][j] = true;
            }
            auto second_range_pair =
                utils::split_as_pair(range_pair.second.substr(2), '-');
            for (int j = std::stoi(second_range_pair.first);
                 j <= std::stoi(second_range_pair.second); ++j) {
                valid[i][j] = true;
            }
        }

        auto my_ticket = utils::split(input[MY_TICKET_LINE], ',');
        auto my_ticket_nums = utils::stringvec_to_intvec(my_ticket);

        for (size_t i = NEARBY_TICKET_LINE_START; i < input.size(); ++i) {
            auto nearby_ticket = utils::split(input[i], ',');
            auto nearby_ticket_nums = utils::stringvec_to_intvec(nearby_ticket);
            for (size_t col_idx = 0; col_idx < nearby_ticket_nums.size();
                 ++col_idx) {
                int num = nearby_ticket_nums[col_idx];
                for (size_t field_idx = 0; field_idx < NUM_OF_FIELDS;
                     ++field_idx) {
                    if (not_possible[col_idx][field_idx]) {
                        continue;
                    }
                    if (!valid[field_idx][num]) {
                        not_possible[col_idx][field_idx] = true;
                    }
                }
            }
        }

        std::array<int, NUM_OF_FIELDS> field_num = {
            0};  // e.g [2] refers to the field num of the 2nd col.
        bool changed = true;
        while (changed) {
            changed = false;
            for (size_t col_idx = 0; col_idx < NUM_OF_FIELDS; ++col_idx) {
                int possible_count = 0;
                int possible_field = -1;
                for (size_t field_idx = 0; field_idx < NUM_OF_FIELDS;
                     ++field_idx) {
                    if (!not_possible[col_idx][field_idx]) {
                        ++possible_count;
                        possible_field = field_idx;
                    }
                }
                if (possible_count == 1) {
                    changed = true;
                    for (size_t col_idx_inner = 0;
                         col_idx_inner < NUM_OF_FIELDS; ++col_idx_inner) {
                        if (col_idx_inner == col_idx) {
                            field_num[col_idx_inner] = possible_field;
                        }
                        not_possible[col_idx_inner][possible_field] = true;
                    }
                }
            }
            for (size_t field_idx = 0; field_idx < NUM_OF_FIELDS; ++field_idx) {
                int possible_count = 0;
                int possible_col = -1;
                for (size_t col_idx = 0; col_idx < NUM_OF_FIELDS; ++col_idx) {
                    if (!not_possible[col_idx][field_idx]) {
                        ++possible_count;
                        possible_col = col_idx;
                    }
                }
                if (possible_count == 1) {
                    changed = true;
                    for (size_t field_idx_inner = 0;
                         field_idx_inner < NUM_OF_FIELDS; ++field_idx_inner) {
                        if (field_idx_inner == field_idx) {
                            field_num[possible_col] = field_idx;
                        }
                        not_possible[possible_col][field_idx_inner] = true;
                    }
                }
            }
        }

        long product = 1;
        for (size_t i = 0; i < field_num.size(); ++i) {
            if (field_num[i] < 6) {
                product *= my_ticket_nums[i];
            }
        }
        std::cout << "q2: " << product << std::endl;
    }

    void produce_q2_file() {
        std::ofstream myfile;
        myfile.open("./input/day16q2.txt");

        auto input = utils::parse_file_text("./input/day16.txt");
        const size_t FIELD_RULE_LINE_END = 19;
        const size_t NEARBY_TICKET_LINE_START = 25;

        const size_t BOOL_ARRAY_SIZE = 1000;
        bool valid[BOOL_ARRAY_SIZE] = {
            false};  // Use fixed size array to indicate if a value is valid.

        for (size_t i = 0; i <= FIELD_RULE_LINE_END; ++i) {
            auto pair = utils::split_as_pair(input[i], ':');
            auto range_pair = utils::split_as_pair(pair.second, 'o');
            auto first_range_pair = utils::split_as_pair(range_pair.first, '-');
            for (int j = std::stoi(first_range_pair.first);
                 j <= std::stoi(first_range_pair.second); ++j) {
                valid[j] = true;
            }
            auto second_range_pair =
                utils::split_as_pair(range_pair.second.substr(2), '-');
            for (int j = std::stoi(second_range_pair.first);
                 j <= std::stoi(second_range_pair.second); ++j) {
                valid[j] = true;
            }
        }

        for (size_t i = 0; i < NEARBY_TICKET_LINE_START; ++i) {
            myfile << input[i] << "\n";
        }

        for (size_t i = NEARBY_TICKET_LINE_START; i < input.size(); ++i) {
            auto nearby_ticket = utils::split(input[i], ',');
            auto nearby_ticket_nums = utils::stringvec_to_intvec(nearby_ticket);
            bool line_valid = true;
            for (int num : nearby_ticket_nums) {
                if ((num < 0) ||
                    (static_cast<size_t>(num) >= BOOL_ARRAY_SIZE) ||
                    !valid[num]) {
                    line_valid = false;
                    break;
                }
            }
            if (line_valid) {
                myfile << input[i] << "\n";
            }
        }
        myfile.close();
    }
};

int main() {
    Day16 solution;
    solution.produce_q2_file();
    solution.execute_and_time();
}