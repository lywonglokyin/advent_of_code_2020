#include <fstream>

#include "utils.h"
#include <iostream>

std::vector<std::string> parse_file_text(std::string filename){
    std::vector<std::string> input;
    std::fstream file_stream(filename);

    std::string line;
    while (std::getline(file_stream, line)){
        input.push_back(line);
    }
    file_stream.close();
    return input;
}

std::vector<int> parse_file_integer(std::string filename){
    std::vector<int> input;
    std::fstream file_stream;
    file_stream.open(filename);

    int line;
    while (file_stream >> line){
        input.push_back(line);
    }
    file_stream.close();
    return input;
}

std::vector<std::string> split(const std::string s, char delim){
    std::vector<std::string> words;
    size_t prev_pos = 0;
    for (size_t i = 0; i < s.length(); ++i){
        if (s.at(i) == delim){
            if (prev_pos != i){
                words.push_back(s.substr(prev_pos, i-prev_pos));
            }
            prev_pos = i + 1;
        }
    }
    if (prev_pos != s.length()){
        words.push_back(s.substr(prev_pos, s.length()-prev_pos));
    }
    return words;
}

std::pair<std::string, std::string> split_as_pair(const std::string s, char delim){
    for (size_t i = 0; i< s.length(); ++i){
        if (s.at(i) == delim){
            if (i == s.length() - 1){
                return std::make_pair(s.substr(0, i), "");
            }
            return std::make_pair(s.substr(0, i), s.substr(i+1));
        }
    }
    std::cout << "Delimiter not found for " << s << "!" << std::endl;
    throw "Delimiter not found!";
}

long long gcd(long long a, long long b){
    return a == 0? b
    : b == 0? a
    : gcd(b, a%b);
}

long long lcm(long long a, long long b){
    return (a != 0 && b != 0) ? a / gcd(a, b) * b : 0;
}