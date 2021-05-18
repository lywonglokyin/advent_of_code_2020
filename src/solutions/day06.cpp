#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

#include "solution.h"
#include "utils.h"

class Day6: public Solution{
public:
    void q1() override{
        const int NUMBER_OF_CHAR = 26;
        bool flags[NUMBER_OF_CHAR] = {false};

        int count = 0;

        auto input = utils::parse_file_text("./input/day6.txt");
        for (auto line: input){
            if (line == ""){
                count += std::accumulate(flags, flags + NUMBER_OF_CHAR, 0);
                for (int i=0; i<NUMBER_OF_CHAR; ++i){
                    flags[i] = false;
                }
            } else {
                for (char c: line){
                    flags[to_int(c)] = true;
                }
            }
        }
        count += std::accumulate(flags, flags + NUMBER_OF_CHAR, 0);
        std::cout << "q1: " << count << std::endl;        
    }
    void q2() override{
        const int NUMBER_OF_CHAR = 26;
        int flags[NUMBER_OF_CHAR] = {0};

        int count = 0;
        int num_ppl = 0;

        auto input = utils::parse_file_text("./input/day6.txt");
        for (auto line: input){
            if (line == ""){
                for (int i=0; i<NUMBER_OF_CHAR; ++i){
                    if (flags[i] == num_ppl){
                        ++count;
                    }
                    flags[i] = 0;
                }
                num_ppl = 0;
            } else {
                for (char c: line){
                    ++flags[to_int(c)];
                }
                ++num_ppl;
            }
        }
        for (int i=0; i<NUMBER_OF_CHAR; ++i){
            if (flags[i] == num_ppl){
                ++count;
            }
        }
        std::cout << "q2: " << count << std::endl;   
    }

private:
    int to_int(char c){
        int i = (int)c;
        if (i < 97 || i > 122){
            throw -1;
        }
        return i-97;
    }

};

int main(){
    Day6 solution;
    solution.execute_and_time();
}