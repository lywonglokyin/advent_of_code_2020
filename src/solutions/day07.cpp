#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <unordered_map>
#include <unordered_set>
#include <stack>

#include "solution.h"
#include "utils.h"

namespace q1{
    class Bag{
    public:
        std::vector<std::pair<Bag*, int>> parent_bags;
        std::string name;

        Bag(std::string name){
            this->name = name;
        }

        void add_parent_bag(Bag* bag, int count){
            this->parent_bags.push_back(std::make_pair(bag, count));
        }
    };
}

namespace q2{
    class Bag{
    public:
        std::vector<std::pair<Bag*, int>> child_bags;
        std::string name;

        Bag(std::string name){
            this->name = name;
        }

        void add_child_bag(Bag* bag, int count){
            this->child_bags.push_back(std::make_pair(bag, count));
        }
    };
}


class Day6: public Solution{
public:
    void q1() override{
        auto input = utils::parse_file_text("./input/day7.txt");

        std::unordered_map<std::string, q1::Bag*> table;

        for (auto line: input){
            auto sections = utils::split(line, ',');

            int bagPos = sections[0].find("bag");
            std::string parent = sections[0].substr(0, bagPos-1);

            int containPos = sections[0].rfind("contain");
            int spacePos = sections[0].find(' ', containPos+8);
            bagPos = sections[0].rfind("bag");
            std::string count =  sections[0].substr(containPos+8, spacePos - (containPos+7) - 1);
            std::string child = sections[0].substr(spacePos + 1, bagPos-spacePos-2);

            
            auto got = table.find(parent);
            q1::Bag* parent_bag;
            if (got == table.end()){
                parent_bag = new q1::Bag(parent);
                table.insert(std::make_pair(parent, parent_bag));
            } else {
                parent_bag = got->second;
            }

            if (count == "no"){
                continue;
            } else {
                got = table.find(child);
                q1::Bag* child_bag;
                if (got == table.end()){
                    child_bag = new q1::Bag(child);
                    table.insert(std::make_pair(child, child_bag));
                } else {
                    child_bag = got->second;
                }
                child_bag->add_parent_bag(parent_bag, std::stoi(count));
            }
            
            for (size_t j=1; j<sections.size(); ++j){
                bagPos = sections[j].rfind("bag");
                spacePos = sections[j].find(' ', 1);
                count =  sections[j].substr(1, spacePos - 1);
                child =  sections[j].substr(spacePos + 1, bagPos-4);

                got = table.find(child);
                q1::Bag* child_bag;
                if (got == table.end()){
                    child_bag = new q1::Bag(child);
                    table.insert(std::make_pair(child, child_bag));
                } else {
                    child_bag = got->second;
                }
                child_bag->add_parent_bag(parent_bag, std::stoi(count));
            }
        }

        std::unordered_set<std::string> explored;
        std::stack<std::string> to_be_explored;
        to_be_explored.push("shiny gold");
        int count = 0;
        while (!to_be_explored.empty()){
            auto bag_name = to_be_explored.top();
            to_be_explored.pop();

            for (auto pair: table.at(bag_name)->parent_bags){
                auto parent_bag_name = pair.first->name;
                if (explored.find(parent_bag_name) != explored.end()){
                    continue;
                } else {
                    ++count;
                    explored.insert(parent_bag_name);
                    to_be_explored.push(parent_bag_name);
                }
            }
        }
        std::cout << "q1: " << count << std::endl;

        for ( auto it = table.begin(); it != table.end(); ++it ){
            delete it->second;
        }
    }
    void q2() override{
        auto input = utils::parse_file_text("./input/day7.txt");

        std::unordered_map<std::string, q2::Bag*> table;

        for (auto line: input){
            auto sections = utils::split(line, ',');

            int bagPos = sections[0].find("bag");
            std::string parent = sections[0].substr(0, bagPos-1);

            int containPos = sections[0].rfind("contain");
            int spacePos = sections[0].find(' ', containPos+8);
            bagPos = sections[0].rfind("bag");
            std::string count =  sections[0].substr(containPos+8, spacePos - (containPos+7) - 1);
            std::string child = sections[0].substr(spacePos + 1, bagPos-spacePos-2);

            
            auto got = table.find(parent);
            q2::Bag* parent_bag;
            if (got == table.end()){
                parent_bag = new q2::Bag(parent);
                table.insert(std::make_pair(parent, parent_bag));
            } else {
                parent_bag = got->second;
            }

            if (count == "no"){
                continue;
            } else {
                got = table.find(child);
                q2::Bag* child_bag;
                if (got == table.end()){
                    child_bag = new q2::Bag(child);
                    table.insert(std::make_pair(child, child_bag));
                } else {
                    child_bag = got->second;
                }
                parent_bag->add_child_bag(child_bag, std::stoi(count));
            }
            
            for (size_t j=1; j<sections.size(); ++j){
                bagPos = sections[j].rfind("bag");
                spacePos = sections[j].find(' ', 1);
                count =  sections[j].substr(1, spacePos - 1);
                child =  sections[j].substr(spacePos + 1, bagPos-4);

                got = table.find(child);
                q2::Bag* child_bag;
                if (got == table.end()){
                    child_bag = new q2::Bag(child);
                    table.insert(std::make_pair(child, child_bag));
                } else {
                    child_bag = got->second;
                }
                parent_bag->add_child_bag(child_bag, std::stoi(count));
            }
        }

        auto shiny_gold_bag = table.at("shiny gold");
        std::cout << "q2: " << get_bag_count(shiny_gold_bag) - 1 << std::endl;

        for ( auto it = table.begin(); it != table.end(); ++it ){
            delete it->second;
        }
    }

private:
    int get_bag_count(q2::Bag* bag){
        int count = 1;
        for (auto pair: bag->child_bags){
            count += pair.second * get_bag_count(pair.first);
        }
        return count;
    }

};

int main(){
    Day6 solution;
    solution.execute_and_time();
}