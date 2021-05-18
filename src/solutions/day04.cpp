#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <stdexcept>

#include "solution.h"
#include "utils.h"

enum PassportFields{
    BYR = 0,
    IYR,
    EYR,
    HGT,
    HCL,
    ECL,
    PID,
    CID,
    NUMBER_OF_PASSPORT_FIELDS
};

static std::unordered_map<std::string, PassportFields> const table = {
    {"byr", BYR}, {"iyr", IYR}, {"eyr", EYR}, {"hgt", HGT}, {"hcl", HCL}, {"ecl", ECL}, {"pid", PID}, {"cid", CID}
};

class Day4: public Solution{
public:
    void q1() override{
        auto input = utils::parse_file_text("input/day4.txt");
        size_t count = 0;
        bool passport_checklist[PassportFields::NUMBER_OF_PASSPORT_FIELDS] = {false};
        for (auto line: input){
            if (line == ""){
                if (is_passport_valid(passport_checklist)){
                    ++count;
                }
                for (size_t i = 0; i< PassportFields::NUMBER_OF_PASSPORT_FIELDS; ++i){
                    passport_checklist[i] = false;
                }
            } else {
                auto entries = utils::split(line, ' ');
                for (auto entry: entries){
                    auto pair = utils::split_as_pair(entry, ':');
                    passport_checklist[table.at(pair.first)] = true;
                }
            }
        }
        if (is_passport_valid(passport_checklist)){
            ++count;
        }
        std::cout << "q1: " << count << std::endl;
    }
    void q2() override{
        auto input = utils::parse_file_text("input/day4.txt");
        size_t count = 0;
        bool passport_checklist[PassportFields::NUMBER_OF_PASSPORT_FIELDS] = {false};
        std::string passport_value[PassportFields::NUMBER_OF_PASSPORT_FIELDS] = {""};
        for (auto line: input){
            if (line == ""){
                if (is_passport_value_valid(passport_checklist, passport_value)){
                    ++count;
                }
                for (size_t i = 0; i< PassportFields::NUMBER_OF_PASSPORT_FIELDS; ++i){
                    passport_checklist[i] = false;
                    passport_value[i] = "";
                }
            } else {
                auto entries = utils::split(line, ' ');
                for (auto entry: entries){
                    auto pair = utils::split_as_pair(entry, ':');
                    passport_checklist[table.at(pair.first)] = true;
                    passport_value[table.at(pair.first)] = pair.second;
                }
            }
        }
        if (is_passport_value_valid(passport_checklist, passport_value)){
            ++count;
        }
        std::cout << "q2: " << count << std::endl;
    }

private:
    bool is_passport_valid(bool checklist[PassportFields::NUMBER_OF_PASSPORT_FIELDS]){
        if (!checklist[PassportFields::BYR]) return false;
        if (!checklist[PassportFields::IYR]) return false;
        if (!checklist[PassportFields::EYR]) return false;
        if (!checklist[PassportFields::HGT]) return false;
        if (!checklist[PassportFields::HCL]) return false;
        if (!checklist[PassportFields::ECL]) return false;
        if (!checklist[PassportFields::PID]) return false;
        return true;
    }

    bool is_passport_value_valid(bool checklist[PassportFields::NUMBER_OF_PASSPORT_FIELDS],
        std::string values[PassportFields::NUMBER_OF_PASSPORT_FIELDS]){
        if (!checklist[PassportFields::BYR] || !validBYR(values[PassportFields::BYR])) return false;
        if (!checklist[PassportFields::IYR] || !validIYR(values[PassportFields::IYR])) return false;
        if (!checklist[PassportFields::EYR] || !validEYR(values[PassportFields::EYR])) return false;
        if (!checklist[PassportFields::HGT] || !validHGT(values[PassportFields::HGT])) return false;
        if (!checklist[PassportFields::HCL] || !validHCL(values[PassportFields::HCL])) return false;
        if (!checklist[PassportFields::ECL] || !validECL(values[PassportFields::ECL])) return false;
        if (!checklist[PassportFields::PID] || !validPID(values[PassportFields::PID])) return false;
        return true;
    }

    bool validBYR(std::string value){
        if (value.length() != 4){
            return false;
        }
        int v;
        try {
            v = std::stoi(value);
        } catch (std::invalid_argument& e){
            return false;
        }
        if (v < 1920 || v > 2002){
            return false;
        }
        return true;
    }

    bool validIYR(std::string value){
        if (value.length() != 4){
            return false;
        }
        int v;
        try {
            v = std::stoi(value);
        } catch (std::invalid_argument& e){
            return false;
        }
        if (v < 2010 || v > 2020){
            return false;
        }
        return true;
    }

    bool validEYR(std::string value){
        if (value.length() != 4){
            return false;
        }
        int v;
        try {
            v = std::stoi(value);
        } catch (std::invalid_argument& e){
            return false;
        }
        if (v < 2020 || v > 2030){
            return false;
        }
        return true;
    }

    bool validHGT(std::string value){
        std::string unit = value.substr(value.length()-2);
        if (unit != "in" && unit != "cm"){
            return false;
        }
        std::string numeric = value.substr(0, value.length()-2);
        int v;
        try {
            v = std::stoi(value);
        } catch (std::invalid_argument& e){
            return false;
        }
        if (unit == "cm" && (v < 150 || v > 193)){
            return false;
        }
        if (unit == "in" && (v < 59 || v > 76)){
            return false;
        }
        return true;
    }

    bool validHCL(std::string value){
        if (value.length() != 7){
            return false;
        }
        if (value.at(0) != '#'){
            return false;
        }
        try {
            std::stoi(value.substr(1), nullptr, 16);
        } catch (std::invalid_argument& e){
            return false;
        }
        return true;
    }

    bool validECL(std::string value){
        std::vector<std::string> possibleValues{"amb","blu","brn","gry","grn","hzl","oth"};
        bool contains = false;
        for (auto possible: possibleValues){
            if (value == possible){
                contains = true;
                break;
            }
        }
        return contains;
    }

    bool validPID(std::string value){
        if (value.length() != 9){
            return false;
        }
        try {
            std::stoi(value);
        } catch (std::invalid_argument& e){
            return false;
        }
        return true;
    }
};

int main(){
    Day4 solution;
    solution.execute_and_time();
}