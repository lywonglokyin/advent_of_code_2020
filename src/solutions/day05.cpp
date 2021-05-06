#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

#include "solution.h"
#include "utils.h"

class Day5: public Solution{
public:
    void q1() override{
        auto input = parse_file_text("./input/day5.txt");
        int max = -1;
        for (auto line: input){
            std::replace(line.begin(), line.begin() + 7, 'F', '0');
            std::replace(line.begin(), line.begin() + 7, 'B', '1');
            std::replace(line.begin() + 7, line.end(), 'L', '0');
            std::replace(line.begin() + 7, line.end(), 'R', '1');
            int id = std::stoi(line, nullptr, 2);

            if (id > max){
                max = id;
            }
        }
        std::cout << "q1: " << max << std::endl;        
    }
    void q2() override{
        auto input = parse_file_text("./input/day5.txt");
        int sum = 0;
        std::string firstLine = input[0];
        std::replace(firstLine.begin(), firstLine.begin() + 7, 'F', '0');
        std::replace(firstLine.begin(), firstLine.begin() + 7, 'B', '1');
        std::replace(firstLine.begin() + 7, firstLine.end(), 'L', '0');
        std::replace(firstLine.begin() + 7, firstLine.end(), 'R', '1');
        int id = std::stoi(firstLine, nullptr, 2);
        int min = id;
        int max = id;
        for (auto line: input){
            std::replace(line.begin(), line.begin() + 7, 'F', '0');
            std::replace(line.begin(), line.begin() + 7, 'B', '1');
            std::replace(line.begin() + 7, line.end(), 'L', '0');
            std::replace(line.begin() + 7, line.end(), 'R', '1');
            int line_id = std::stoi(line, nullptr, 2);
            if (line_id > max){
                max = line_id;
            }
            if (line_id < min){
                min = line_id;
            }
            sum += line_id;
        }
        int expected_sum = (min + max) * (max - min + 1) / 2;
        std::cout << "q2: " << expected_sum - sum << std::endl;   
    }

    
};

int main(){
    Day5 solution;
    solution.execute_and_time();
}