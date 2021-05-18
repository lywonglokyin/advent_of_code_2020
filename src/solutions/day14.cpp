#include <iostream>
#include <limits>
#include <unordered_map>

#include "solution.h"
#include "utils.h"

class Day14: public Solution{
public:
    void q1() override{
        auto input = utils::parse_file_text("./input/day14.txt");

        unsigned long zero_mask = std::numeric_limits<unsigned long>::max();
        unsigned long one_mask = 0;

        std::unordered_map<int, unsigned long> mem;

        for (auto line: input){
            // This assumed only "mask" and "mem" instructions;
            if (line.at(1) == 'a'){
                // Mask
                zero_mask = std::numeric_limits<unsigned long>::max();
                one_mask = 0;

                for (size_t i=line.size()-1; i>=7; --i){
                    size_t place = line.size()-1 - i;
                    if (line.at(i) == '1'){
                        one_mask += (1UL<<place);
                    } else if (line.at(i) == '0'){
                        zero_mask -= (1UL<<place);
                    }
                }
            } else {
                // Mem
                auto pair = utils::split_as_pair(line, ']');
                int mem_loc = std::stoi(pair.first.substr(4));
                unsigned long value = std::stoi(pair.second.substr(3));
                value = (value & zero_mask) | one_mask;
                mem[mem_loc] = value;
            }
        }

        unsigned long sum = 0;
        for (auto it = mem.begin(); it != mem.end(); ++it){
            sum += it->second;
        }
        std::cout << "q1: " << sum << std::endl;
    }
    void q2() override{
        auto input = utils::parse_file_text("./input/day14.txt");

        unsigned long zero_mask = std::numeric_limits<unsigned long>::max();
        unsigned long one_mask = 0;
        std::vector<int> pos;

        std::unordered_map<unsigned long, unsigned long> mem;

        for (auto line: input){
            // This assumed only "mask" and "mem" instructions;
            if (line.at(1) == 'a'){
                // Mask
                zero_mask = std::numeric_limits<unsigned long>::max();
                one_mask = 0;
                pos.clear();
                for (size_t i=line.size()-1; i>=7; --i){
                    size_t place = line.size()-1 - i;
                    if (line.at(i) == '1'){
                        one_mask += (1UL<<place);
                    } else if (line.at(i) == '0'){
                        zero_mask -= (1UL<<place);
                    } else if (line.at(i) == 'X'){
                        pos.emplace_back(place);
                    }
                }
            } else {
                // Mem
                auto pair = utils::split_as_pair(line, ']');
                unsigned long mem_loc = std::stoi(pair.first.substr(4));
                mem_loc = mem_loc | one_mask;
                unsigned long value = std::stoi(pair.second.substr(3));

                auto floating_mems = get_combination(mem_loc, pos, 0);
                for (auto mem_pos: floating_mems){
                    mem[mem_pos] = value;
                }
            }
        }

        unsigned long sum = 0;
        for (auto it = mem.begin(); it != mem.end(); ++it){
            sum += it->second;
        }
        std::cout << "q2: " << sum << std::endl;
    }

private:
    std::vector<unsigned long> get_combination(unsigned long base, const std::vector<int> positions, size_t index){
        unsigned long zero_mask = std::numeric_limits<unsigned long>::max();
        unsigned long one_mask = 0;
        zero_mask -= 1UL << positions[index];
        one_mask += 1UL << positions[index];
        if (index == positions.size()-1){
            return std::vector<unsigned long>{base&zero_mask, base|one_mask};
        } else {
            std::vector<unsigned long> result_zero = get_combination(base&zero_mask, positions, index+1);
            std::vector<unsigned long> result_one = get_combination(base|one_mask, positions, index+1);
            result_zero.insert(result_zero.end(),
                std::make_move_iterator(result_one.begin()),
                std::make_move_iterator(result_one.end()));
            return result_zero;
        }
    }
};

int main(){
    Day14 solution;
    solution.execute_and_time();
}