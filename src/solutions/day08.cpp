#include <string>
#include <vector>
#include <iostream>
#include <utility>
#include <unordered_map>
#include <functional>

#include "solution.h"
#include "utils.h"


class Interpreter{
public:
    using func = void (Interpreter::*)(int, int);

    std::vector<std::pair<std::string, int>> code;
    int accumulator;
    int instr_ptr;
    Interpreter::func test;

    std::unordered_map<std::string, Interpreter::func> funcMap;

    Interpreter(std::vector<std::pair<std::string, int>> code){
        this->code = code;
        this->accumulator = 0;
        this->instr_ptr = 0;

        funcMap = {
            {"nop", &Interpreter::nop},
            {"acc", &Interpreter::acc},
            {"jmp", &Interpreter::jmp}
        };
    }

    void run_next(){
        int pos = instr_ptr;
        ++instr_ptr;
        run_cmd_at(pos);
    }

    void run_cmd_at(int pos){
        auto func = funcMap.at(code[pos].first);
        (this->*func)(code[pos].second, pos);
    }

    void nop(int value, int pos){
        (void)value;
        (void)pos;
        return;
    }

    void acc(int value, int pos){
        (void)pos;
        this->accumulator += value;
        return;
    }

    void jmp(int value, int pos){
        (void)value;
        this->instr_ptr = pos + value;
        return;
    }
};

class Day8: public Solution{
public:
    void q1() override{
        auto input = utils::parse_file_text("./input/day8.txt");
        std::vector<std::pair<std::string, int>> code;
        for (auto line: input){
            auto words = utils::split_as_pair(line, ' ');
            code.push_back(std::make_pair(words.first, std::stoi(words.second)));
        };
        std::vector<int> count(input.size(),0);
        Interpreter itpr{std::move(code)};

        while (true){
            ++count[itpr.instr_ptr];
            if (count[itpr.instr_ptr] == 2){
                break;
            }
            itpr.run_next();
        }
        std::cout << "q1: " << itpr.accumulator << std::endl;
    }
    void q2() override{
        auto input = utils::parse_file_text("./input/day8.txt");
        std::vector<std::pair<std::string, int>> code;
        for (auto line: input){
            auto words = utils::split_as_pair(line, ' ');
            code.push_back(std::make_pair(words.first, std::stoi(words.second)));
        };
        size_t code_size = code.size();
        std::vector<int> count(code_size,0);

        for (size_t i=0; i<code_size; ++i){
            if (code[i].first == "nop"){
                code[i].first = "jmp";
            } else if (code[i].first == "jmp"){
                code[i].first = "nop";
            } else {
                continue;
            }
            Interpreter itpr{std::move(code)};
            std::fill(count.begin(), count.end(), 0);
            bool reached_end = false;
            while (true){
                ++count[itpr.instr_ptr];
                if (itpr.instr_ptr == code_size - 1){
                    reached_end = true;
                    itpr.run_next();
                    break;
                }
                if (count[itpr.instr_ptr] == 2){
                    break;
                }
                itpr.run_next();
            }
            if (reached_end){
                std::cout << "q2: " << itpr.accumulator << std::endl;
                return;
            } else {
                code = std::move(itpr.code);
                if (code[i].first == "nop"){
                    code[i].first = "jmp";
                } else if (code[i].first == "jmp"){
                    code[i].first = "nop";
                }
            }
        }
    }
};

int main(){
    Day8 solution;
    solution.execute_and_time();
}