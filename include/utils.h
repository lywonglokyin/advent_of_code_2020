#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>
#include <utility>
#include <algorithm>

namespace utils{

    std::vector<std::string> parse_file_text(const std::string& filename);

    std::vector<int> parse_file_integer(const std::string& filename);

    std::vector<std::string> split(const std::string& s, char delim = ' ');

    std::pair<std::string, std::string> split_as_pair(const std::string& s, char delim = ' ');

    long long gcd(long long a, long long b);

    long long lcm(long long a, long long b);

    inline std::vector<int> stringvec_to_intvec(const std::vector<std::string>& string_vec){
        std::vector<int> intvec;
        std::transform(string_vec.begin(), string_vec.end(), std::back_inserter(intvec),
        [](const std::string& str){return std::stoi(str);});
        return intvec;
    }
}

#endif