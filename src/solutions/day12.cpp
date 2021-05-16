#include <iostream>
#include <vector>
#include <cmath>

#include "solution.h"
#include "utils.h"


struct Ship{
    enum Direction{
        N = 0, E, S, W, NUM_DIRECTION
    };
    
    int x;
    int y;
    Direction d;

    void turnLeft(int degree){
        // degree assumed to be multiple of 90.
        int temp = (d - degree / 90) % Direction::NUM_DIRECTION;
        if (temp < 0){
            temp += Direction::NUM_DIRECTION;
        }
        d = static_cast<Direction>(temp);

    }

    void turnRight(int degree){
        d = static_cast<Direction>((d + degree / 90) % Direction::NUM_DIRECTION);
    }

    void forward(int units){
        switch (d){
            case Direction::N:
                moveNorth(units);
                break;
            case Direction::E:
                moveEast(units);
                break;
            case Direction::S:
                moveSouth(units);
                break;
            case Direction::W:
                moveWest(units);
                break;
            default:
                throw -1;
        }
    }

    void moveNorth(int units){
        y += units;
    }
    void moveSouth(int units){
        y -= units;
    }
    void moveEast(int units){
        x += units;
    }
    void moveWest(int units){
        x -= units;
    }
};

struct Waypoint{
    int x;
    int y;
};

struct WaypointShip{    
    int x;
    int y;
    Waypoint waypoint;

    void turnLeft(int degree){
        // degree assumed to be multiple of 90.
        int right_angle_turns = degree / 90 % 4;
        if (right_angle_turns == 1){
            int temp = waypoint.x;
            waypoint.x = - waypoint.y;
            waypoint.y = temp;
        } else if (right_angle_turns == 2){
            waypoint.x = -waypoint.x;
            waypoint.y = -waypoint.y;
        } else if (right_angle_turns == 3){
            int temp = waypoint.x;
            waypoint.x = waypoint.y;
            waypoint.y = -temp;
        } else {
            throw -1;
        }
    }

    void turnRight(int degree){
        int right_angle_turns = degree / 90 % 4;
        if (right_angle_turns == 1){
            int temp = waypoint.x;
            waypoint.x = waypoint.y;
            waypoint.y = -temp;
        } else if (right_angle_turns == 2){
            waypoint.x = -waypoint.x;
            waypoint.y = -waypoint.y;
        } else if (right_angle_turns == 3){
            int temp = waypoint.x;
            waypoint.x = - waypoint.y;
            waypoint.y = temp;
        } else {
            throw -1;
        }
    }

    void forward(int units){
        this->x += waypoint.x * units;
        this->y += waypoint.y * units;
    }

    void moveNorth(int units){
        waypoint.y += units;
    }
    void moveSouth(int units){
        waypoint.y -= units;
    }
    void moveEast(int units){
        waypoint.x += units;
    }
    void moveWest(int units){
        waypoint.x -= units;
    }
};

class Day12: public Solution{
public:
    void q1() override{
        auto input = parse_file_text("./input/day12.txt");
        
        Ship ship{0, 0, Ship::Direction::E};

        for (auto line: input){
            char command = line[0];
            int value = std::stoi(line.substr(1));

            switch (command)
            {
            case 'N':
                ship.moveNorth(value);
                break;
            case 'E':
                ship.moveEast(value);
                break;
            case 'S':
                ship.moveSouth(value);
                break;
            case 'W':
                ship.moveWest(value);
                break;
            case 'F':
                ship.forward(value);
                break;
            case 'L':
                ship.turnLeft(value);
                break;
            case 'R':
                ship.turnRight(value);
                break;
            default:
                throw -1;
            }
        }

        std::cout << "q1: " << std::abs(ship.x) + std::abs(ship.y) <<std::endl;
    }
    void q2() override{

        auto input = parse_file_text("./input/day12.txt");
        
        WaypointShip ship{0, 0, {10, 1}};

        for (auto line: input){
            char command = line[0];
            int value = std::stoi(line.substr(1));

            switch (command)
            {
            case 'N':
                ship.moveNorth(value);
                break;
            case 'E':
                ship.moveEast(value);
                break;
            case 'S':
                ship.moveSouth(value);
                break;
            case 'W':
                ship.moveWest(value);
                break;
            case 'F':
                ship.forward(value);
                break;
            case 'L':
                ship.turnLeft(value);
                break;
            case 'R':
                ship.turnRight(value);
                break;
            default:
                throw -1;
            }
        }
        std::cout << "q2: " << std::abs(ship.x) + std::abs(ship.y)<< std::endl;
    }

};

int main(){
    Day12 solution;
    solution.execute_and_time();
}