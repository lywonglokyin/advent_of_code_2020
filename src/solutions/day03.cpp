#include <string>
#include <iostream>
#include <vector>

#include "solution.h"
#include "utils.h"

class Day3: public Solution{
public:
    void q1() override{
        auto input = utils::parse_file_text("input/day3.txt");

        int horizontal_pos = 0;
        int map_length = input[0].length();

        int count = 0;
        for (std::string line: input){
            if (line.at(horizontal_pos) == '#'){
                ++count;
            }
            horizontal_pos = (horizontal_pos + 3) % map_length;
        }
        std::cout << "q1: " <<count << std::endl;
    }
    void q2() override{
        auto input = utils::parse_file_text("input/day3.txt");

        int map_length = input[0].length();

        int horizontal_displacements[4] = {1,3,5,7};
        std::vector<int> trees;
        for (int displacement: horizontal_displacements){
            int count = 0;
            int horizontal_pos = 0;
            for (std::string line: input){
                if (line.at(horizontal_pos) == '#'){
                    ++count;
                }
                horizontal_pos = (horizontal_pos + displacement) % map_length;
            }
            trees.push_back(count);
        }
        int count = 0;
        int horizontal_pos = 0;
        for (unsigned int i=0; i<input.size(); i+=2){
            if (input[i].at(horizontal_pos) == '#'){
                ++count;
            }
            horizontal_pos = (horizontal_pos + 1) % map_length;
        }
        long int product = count;
        for (int tree: trees){
            product *= tree;
        }
        std::cout << "q2: " <<product << std::endl;
    }
};

int main(){
    Day3 solution;
    solution.execute_and_time();
}