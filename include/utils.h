#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>
#include <utility>

std::vector<std::string> parse_file_text(std::string filename);

std::vector<int> parse_file_integer(std::string filename);

std::vector<std::string> split(const std::string s, char delim = ' ');

std::pair<std::string, std::string> split_as_pair(const std::string s, char delim = ' ');

long long gcd(long long a, long long b);

long long lcm(long long a, long long b);

#endif