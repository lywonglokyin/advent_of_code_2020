#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>

std::vector<std::string> parse_file_text(std::string filename);

std::vector<int> parse_file_integer(std::string filename);
#endif