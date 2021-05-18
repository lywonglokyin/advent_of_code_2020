#include <iostream>
#include <vector>
#include <queue>

#include "solution.h"
#include "utils.h"


struct Pos{
    int x;
    int y;
};

class Day11: public Solution{
public:
    void q1() override{
        auto input = utils::parse_file_text("./input/day11.txt");
        int width = input[0].length();
        int height = input.size();

        std::queue<std::pair<Pos, char>> to_be_update;
        bool changed = true;

        while (changed){
            changed = false;
            for (int y=0; y<height; ++y){
                for (int x=0; x<width; ++x){
                    char new_c = get_updated_char(input, Pos{x, y});
                    if (new_c != input[y][x]){
                        changed = true;
                        to_be_update.push(std::make_pair(Pos{x, y}, new_c));
                    }
                }
            }
            while (!to_be_update.empty()){
                auto pair = to_be_update.front();
                input[pair.first.y][pair.first.x] = pair.second;
                to_be_update.pop();
            }
        }

        int count = 0;
        for (int y=0; y<height; ++y){
            for (int x=0; x<width; ++x){
                if (input[y][x] == '#') ++count;
            }
        }

        std::cout << "q1: " << count << std::endl;
    }
    void q2() override{
        auto input = utils::parse_file_text("./input/day11.txt");
        int width = input[0].length();
        int height = input.size();

        std::queue<std::pair<Pos, char>> to_be_update;
        bool changed = true;

        while (changed){
            changed = false;
            for (int y=0; y<height; ++y){
                for (int x=0; x<width; ++x){
                    char new_c = get_updated_char_with_visibility(input, Pos{x, y});
                    if (new_c != input[y][x]){
                        changed = true;
                        to_be_update.push(std::make_pair(Pos{x, y}, new_c));
                    }
                }
            }
            while (!to_be_update.empty()){
                auto pair = to_be_update.front();
                input[pair.first.y][pair.first.x] = pair.second;
                to_be_update.pop();
            }
        }

        int count = 0;
        for (int y=0; y<height; ++y){
            for (int x=0; x<width; ++x){
                if (input[y][x] == '#') ++count;
            }
        }

        std::cout << "q2: " << count << std::endl;
    }

private:

    char get_updated_char(const std::vector<std::string>& input, const Pos& pos){
        char my_val = input[pos.y][pos.x];
        if (my_val=='.'){
            return '.';
        }

        int o_seats = get_surrounding_occupied_seat(input, pos);
        if (o_seats == 0){
            return '#';
        }
        if (o_seats >= 4){
            return 'L';
        }
        return my_val;
    }

    char get_updated_char_with_visibility(const std::vector<std::string>& input, const Pos& pos){
        char my_val = input[pos.y][pos.x];
        if (my_val=='.'){
            return '.';
        }

        int o_seats = get_visible_occupied_seat(input, pos);
        if (o_seats == 0){
            return '#';
        }
        if (o_seats >= 5){
            return 'L';
        }
        return my_val;
    }

    inline int get_surrounding_occupied_seat(const std::vector<std::string>& input, const Pos& pos){
        int width = input[0].length();
        int height = input.size();
        int count = 0;
        
        if (pos.y != 0){
            if (input[pos.y-1][pos.x] == '#') ++count;

            if (pos.x != 0){
                if (input[pos.y-1][pos.x - 1] == '#') ++count;
            }
            if (pos.x != width-1){
                if (input[pos.y-1][pos.x + 1] == '#') ++count;
            }
        }

        if (pos.y != height-1){
            if (input[pos.y+1][pos.x] == '#') ++count;

            if (pos.x != 0){
                if (input[pos.y+1][pos.x - 1] == '#') ++count;
            }
            if (pos.x != width-1){
                if (input[pos.y+1][pos.x + 1] == '#') ++count;
            }
        }

        if (pos.x != 0){
            if (input[pos.y][pos.x - 1] == '#') ++count;
        }
        if (pos.x != width-1){
            if (input[pos.y][pos.x + 1] == '#') ++count;
        }
        return count;
    }

    inline int get_visible_occupied_seat(const std::vector<std::string>& input, const Pos& pos){
        int width = input[0].length();
        int height = input.size();
        int count = 0;

        int up = 1;
        while ((pos.y - up) != -1){
            char target_char = input[pos.y - up][pos.x];
            if (target_char == '#'){
                ++count;
                break;
            }
            if (target_char == 'L'){
                break;
            }
            ++up;
        }

        int down = 1;
        while ((pos.y + down) != height){
            char target_char = input[pos.y + down][pos.x];
            if (target_char == '#'){
                ++count;
                break;
            }
            if (target_char == 'L'){
                break;
            }
            ++down;
        }

        int left = 1;
        while ((pos.x - left) != -1){
            char target_char = input[pos.y][pos.x - left];
            if (target_char == '#'){
                ++count;
                break;
            }
            if (target_char == 'L'){
                break;
            }
            ++left;
        }

        int right = 1;
        while ((pos.x + right) != width){
            char target_char = input[pos.y][pos.x + right];
            if (target_char == '#'){
                ++count;
                break;
            }
            if (target_char == 'L'){
                break;
            }
            ++right;
        }

        up = 1;
        left = 1;
        while ((pos.y - up) != -1 && (pos.x - left) != -1){
            char target_char = input[pos.y - up][pos.x - left];
            if (target_char == '#'){
                ++count;
                break;
            }
            if (target_char == 'L'){
                break;
            }
            ++up;
            ++left;
        }

        up = 1;
        right = 1;
        while ((pos.y - up) != -1 && (pos.x + right) != width){
            char target_char = input[pos.y - up][pos.x + right];
            if (target_char == '#'){
                ++count;
                break;
            }
            if (target_char == 'L'){
                break;
            }
            ++up;
            ++right;
        }

        down = 1;
        left = 1;
        while ((pos.y + down) != height && (pos.x - left) != -1){
            char target_char = input[pos.y + down][pos.x - left];
            if (target_char == '#'){
                ++count;
                break;
            }
            if (target_char == 'L'){
                break;
            }
            ++down;
            ++left;
        }

        down = 1;
        right = 1;
        while ((pos.y + down) != height && (pos.x + right) != width){
            char target_char = input[pos.y + down][pos.x + right];
            if (target_char == '#'){
                ++count;
                break;
            }
            if (target_char == 'L'){
                break;
            }
            ++down;
            ++right;
        }
        return count;
    }

};

int main(){
    Day11 solution;
    solution.execute_and_time();
}