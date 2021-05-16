#include <iostream>
#include <algorithm>
#include <limits>
#include <vector>

#include "solution.h"
#include "utils.h"

class Day13: public Solution{
public:
    void q1() override{
        auto input = parse_file_text("./input/day13.txt");
        int from_time = std::stoi(input[0]);

        auto buses = split(input[1], ',');


        int earliest_bus_id = -1;
        int shortest_wait_time = std::numeric_limits<int>::max();
        for (auto bus: buses){
            if (bus == "x"){
                continue;
            }
            int bus_id = std::stoi(bus);
            int wait_time = bus_id - (from_time % bus_id);
            if (wait_time < shortest_wait_time){
                earliest_bus_id = bus_id;
                shortest_wait_time = wait_time;
            }
        }
        std::cout << "q1: " << earliest_bus_id * shortest_wait_time << std::endl;
    }
    void q2() override{
        auto input = parse_file_text("./input/day13.txt");

        auto buses = split(input[1], ',');
        std::vector<std::pair<long long, long long>> parsedInput;
        for (size_t i=0; i<buses.size(); ++i){
            if (buses[i] == "x"){
                continue;
            }
            long long bus_id = std::stoi(buses[i]);
            long long shift = bus_id - (i % bus_id);
            if (shift < 0) shift += bus_id;
            parsedInput.emplace_back(std::make_pair(bus_id, shift));
        }
        std::cout << "q2: " << least_common_multiple_with_modulo_recursive(parsedInput) << std::endl;
    }

private:

    long long least_common_multiple_with_modulo_recursive(const std::vector<std::pair<long long, long long>>& input){
        // Assume the divisors of the input are distinct
        if (input.size() < 2){
            throw -1;
        }
        if (input.size() == 2){
            return least_common_multiple_with_modulo(input[0].first, input[0].second, input[1].first, input[1].second);
        }
        long long max_divisor = input[0].first;
        long long max_divisor_modulo = input[0].second;
        for (auto pair: input){
            if (pair.first > max_divisor){
                max_divisor = pair.first;
                max_divisor_modulo = pair.second;
            }
        }

        std::vector<std::pair<long long, long long>> new_input;
        for (auto pair: input){
            if (pair.first == max_divisor){
                continue;
            }
            long long target = least_common_multiple_with_modulo(pair.first, pair.second, max_divisor, max_divisor_modulo);
            long long shift_count = (target - max_divisor_modulo) / max_divisor;
            long long indifferent_shifts = lcm(pair.first, max_divisor)/max_divisor;
            new_input.emplace_back(std::make_pair(indifferent_shifts, shift_count));
        }

        long long to_shift = least_common_multiple_with_modulo_recursive(new_input);
        return to_shift * max_divisor + max_divisor_modulo;
    }

    long long least_common_multiple_with_modulo(long long a, long long mod_a, long long b, long long mod_b){
        // std::cout<< "Calling normal with: Divide " << a <<" remains " << mod_a << ", Divide " <<b << " remains " <<mod_b << "." <<std::endl;
        if (a>b){
            std::swap(a, b);
            std::swap(mod_a, mod_b);
        }

        if (a == 1){
            return b * 1 + mod_b - mod_a;
        }

        if (b % a == 0){
            // Currently, do not deal when cases with b is a multiple of a.
            throw -1;
        }

        int a_need_to_shift = (mod_a - mod_b) % a;
        if (a_need_to_shift < 0) a_need_to_shift += a;

        int a_shift_amount = b % a;
        int total_shift_amount = least_common_multiple_with_modulo(a_shift_amount, 0, a, a_need_to_shift);
        int num_of_times_shifted = (total_shift_amount / a_shift_amount) % a;
        if (num_of_times_shifted == 0){
            // This happens when a_need_to_shift == 0;
            num_of_times_shifted += a;
        }
        return mod_b + b * num_of_times_shifted;
    }
};

int main(){
    Day13 solution;
    solution.execute_and_time();
}