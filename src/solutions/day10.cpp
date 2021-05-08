#include <algorithm>
#include <iostream>
#include <functional>

#include "solution.h"
#include "utils.h"


class Day10: public Solution{
public:
    void q1() override{
        auto input = parse_file_integer("./input/day10.txt");
        std::sort(input.begin(), input.end());

        int oneDiff = 0;
        int threeDiff = 0;

        int jolt = 0;
        for (int rating: input){
            int jolt_diff = rating - jolt;
            if (jolt_diff == 1){
                ++oneDiff;
            } else if (jolt_diff == 3){
                ++threeDiff;
            }
            jolt = rating;
        }
        ++threeDiff; // built-in adapter
        std::cout << "q1: " << oneDiff * threeDiff << std::endl;
        
    }
    void q2() override{
        auto input = parse_file_integer("./input/day10.txt");
        std::sort(input.begin(), input.end(), std::greater<int>());

        int max = input[0];
        std::vector<long long> combin(max + 4, 0);
        combin[max+3] = 1;
        combin[max] = 1;
        for (int rating: input){
            combin[rating] = combin[rating+1] + combin[rating+2] + combin[rating+3];
        }
        combin[0] = combin[1] + combin[2] + combin[3];

        std::cout << "q2: " << combin[0] << std::endl;
       
    }
};

int main(){
    Day10 solution;
    solution.execute_and_time();
}