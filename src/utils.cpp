#include <fstream>

#include "utils.h"

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
