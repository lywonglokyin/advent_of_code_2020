#include <array>
#include <iostream>

#include "solution.h"
#include "utils.h"

class Day17 : public Solution {
   public:
    static const size_t INITIAL_SLICE_SIZE = 3;
    static const size_t MAX_SIZE =
        INITIAL_SLICE_SIZE + 6 +
        6;  // Abuse the fact that the slice size and iterations is known.
    static const size_t MAX_DEPTH = 1 + 6 + 6;

    using grid = std::array<
        std::array<std::array<bool, Day17::MAX_DEPTH>, Day17::MAX_SIZE>,
        Day17::MAX_SIZE>;
    using hypergrid =
        std::array<std::array<std::array<std::array<bool, Day17::MAX_DEPTH>,
                                         Day17::MAX_DEPTH>,
                              Day17::MAX_SIZE>,
                   Day17::MAX_SIZE>;

    void q1() override {
        grid active = {false};

        auto input = utils::parse_file_text("./input/day17test.txt");
        const int OFFSET = 6;
        for (size_t i = 0; i < input.size(); ++i) {
            for (size_t j = 0; j < input[i].size(); ++j) {
                if (input[i][j] == '#') {
                    active[i + OFFSET][j + OFFSET][OFFSET] = true;
                }
            }
        }

        grid temp = active;

        for (int iteration = 0; iteration < 6; ++iteration) {
            // for (size_t x = 0; x< MAX_SIZE; ++x){
            //     std::cout << x << "\t";
            //     for (size_t y = 0; y < MAX_SIZE; ++y){
            //         if (active[x][y][OFFSET]){
            //             std::cout << "#";
            //         } else {
            //             std::cout << ".";
            //         }
            //     }
            //     std::cout << std::endl;
            // }
            // std::cout << std::endl;

            for (size_t x = 0; x < MAX_SIZE; ++x) {
                for (size_t y = 0; y < MAX_SIZE; ++y) {
                    for (size_t z = 0; z < MAX_DEPTH; ++z) {
                        if (active[x][y][z]) {
                            check_active(active, temp, x, y,
                                         z);  // Wrong because u need two array.
                        } else {
                            check_inactive(active, temp, x, y, z);
                        }
                    }
                }
            }
            active = temp;
        }

        size_t count = 0;
        for (size_t x = 0; x < MAX_SIZE; ++x) {
            for (size_t y = 0; y < MAX_SIZE; ++y) {
                for (size_t z = 0; z < MAX_DEPTH; ++z) {
                    if (active[x][y][z]) {
                        ++count;
                    }
                }
            }
        }
        std::cout << "q1: " << count << std::endl;
    }

    void check_active(const grid& active, grid& temp, size_t x, size_t y,
                      size_t z) {
        size_t count = number_of_active_neighbour(active, x, y, z);
        if (count < 2 || count > 3) {
            temp[x][y][z] = false;
        }
    }
    void check_active(const hypergrid& active, hypergrid& temp, size_t x,
                      size_t y, size_t z, size_t w) {
        size_t count = number_of_active_neighbour(active, x, y, z, w);
        if (count < 2 || count > 3) {
            temp[x][y][z][w] = false;
        }
    }

    void check_inactive(const grid& active, grid& temp, size_t x, size_t y,
                        size_t z) {
        size_t count = number_of_active_neighbour(active, x, y, z);
        if (count == 3) {
            temp[x][y][z] = true;
        }
    }
    void check_inactive(const hypergrid& active, hypergrid& temp, size_t x,
                        size_t y, size_t z, size_t w) {
        size_t count = number_of_active_neighbour(active, x, y, z, w);
        if (count == 3) {
            temp[x][y][z][w] = true;
        }
    }

    size_t number_of_active_neighbour(const grid& active, size_t x, size_t y,
                                      size_t z) {
        size_t count = 0;
        for (int x_i = x - 1; static_cast<size_t>(x_i) <= x + 1; ++x_i) {
            if (x_i < 0) continue;
            if (static_cast<size_t>(x_i) >= Day17::MAX_SIZE) break;
            for (int y_i = y - 1; static_cast<size_t>(y_i) <= y + 1; ++y_i) {
                if (y_i < 0) continue;
                if (static_cast<size_t>(y_i) >= Day17::MAX_SIZE) break;
                for (int z_i = z - 1; static_cast<size_t>(z_i) <= z + 1;
                     ++z_i) {
                    if (z_i < 0) continue;
                    if (static_cast<size_t>(z_i) >= Day17::MAX_DEPTH) break;
                    if (static_cast<size_t>(x_i) == x &&
                        static_cast<size_t>(y_i) == y &&
                        static_cast<size_t>(z_i) == z) {
                        continue;
                    }
                    if (active[x_i][y_i][z_i]) {
                        ++count;
                    }
                }
            }
        }
        return count;
    }

    size_t number_of_active_neighbour(const hypergrid& active, size_t x,
                                      size_t y, size_t z, size_t w) {
        size_t count = 0;
        for (int x_i = x - 1; static_cast<size_t>(x_i) <= x + 1; ++x_i) {
            if (x_i < 0) continue;
            if (static_cast<size_t>(x_i) >= Day17::MAX_SIZE) break;
            for (int y_i = y - 1; static_cast<size_t>(y_i) <= y + 1; ++y_i) {
                if (y_i < 0) continue;
                if (static_cast<size_t>(y_i) >= Day17::MAX_SIZE) break;
                for (int z_i = z - 1; static_cast<size_t>(z_i) <= z + 1;
                     ++z_i) {
                    if (z_i < 0) continue;
                    if (static_cast<size_t>(z_i) >= Day17::MAX_DEPTH) break;
                    for (int w_i = w - 1; static_cast<size_t>(w_i) <= w + 1;
                         ++w_i) {
                        if (w_i < 0) continue;
                        if (static_cast<size_t>(w_i) >= Day17::MAX_DEPTH) break;
                        if (active[x_i][y_i][z_i][w_i]) {
                            ++count;
                        }
                    }
                }
            }
        }
        if (active[x][y][z][w]) --count;
        return count;
    }
    void q2() override {
        hypergrid active = {false};

        auto input = utils::parse_file_text("./input/day17test.txt");
        const int OFFSET = 6;
        for (size_t i = 0; i < input.size(); ++i) {
            for (size_t j = 0; j < input[i].size(); ++j) {
                if (input[i][j] == '#') {
                    active[i + OFFSET][j + OFFSET][OFFSET][OFFSET] = true;
                }
            }
        }

        hypergrid temp = active;

        for (int iteration = 0; iteration < 6; ++iteration) {
            // for (size_t x = 0; x< MAX_SIZE; ++x){
            //     std::cout << x << "\t";
            //     for (size_t y = 0; y < MAX_SIZE; ++y){
            //         if (active[x][y][OFFSET][OFFSET]){
            //             std::cout << "#";
            //         } else {
            //             std::cout << ".";
            //         }
            //     }
            //     std::cout << std::endl;
            // }
            // std::cout << std::endl;

            for (size_t x = 0; x < MAX_SIZE; ++x) {
                for (size_t y = 0; y < MAX_SIZE; ++y) {
                    for (size_t z = 0; z < MAX_DEPTH; ++z) {
                        for (size_t w = 0; w < MAX_DEPTH; ++w) {
                            if (active[x][y][z][w]) {
                                check_active(active, temp, x, y, z, w);
                            } else {
                                check_inactive(active, temp, x, y, z, w);
                            }
                        }
                    }
                }
            }
            active = temp;
        }

        // for (size_t w = 0; w <= MAX_DEPTH; ++w){
        // for (size_t z = 0; z <= MAX_DEPTH; ++z){
        //     std::cout << "z = " << (int)z-OFFSET << ", w = "<< (int)w-OFFSET
        //     << std::endl;
        // for (size_t x = 0; x< MAX_SIZE; ++x){
        //         std::cout << x << "\t";
        //         for (size_t y = 0; y < MAX_SIZE; ++y){
        //             if (active[x][y][z][w]){
        //                 std::cout << "#";
        //             } else {
        //                 std::cout << ".";
        //             }
        //         }
        //         std::cout << std::endl;
        //     }
        // std::cout << std::endl;
        // }
        // }

        size_t count = 0;
        for (size_t x = 0; x < MAX_SIZE; ++x) {
            for (size_t y = 0; y < MAX_SIZE; ++y) {
                for (size_t z = 0; z < MAX_DEPTH; ++z) {
                    for (size_t w = 0; w < MAX_DEPTH; ++w) {
                        if (active[x][y][z][w]) {
                            ++count;
                        }
                    }
                }
            }
        }
        std::cout << "q2: " << count << std::endl;
    }
};

int main() {
    Day17 solution;
    solution.execute_and_time();
}