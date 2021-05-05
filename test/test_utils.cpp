#include <utils.h>

namespace Test_split{
    void test_split_1(){
        std::vector<std::string> expected{"a", "b", "c"};
        auto got = split("a b c", ' ');
        if (expected != got){
            throw -1;
        }
    }

    void test_split_2(){
        std::vector<std::string> expected{"a", "b", "c"};
        auto got = split("a:b:c", ':');
        if (expected != got){
            throw -1;
        }
    }

    void test_split_3(){
        std::vector<std::string> expected{"a", "  b ", "  c"};
        auto got = split("a:  b :  c", ':');
        if (expected != got){
            throw -1;
        }
    }

    void test_split_4(){
        std::vector<std::string> expected{"a:", "b", ":","c"};
        auto got = split("a:  b :  c", ' ');
        if (expected != got){
            throw -1;
        }
    }

    void test_split_5(){
        std::vector<std::string> expected;
        auto got = split("           ", ' ');
        if (expected != got){
            throw -1;
        }
    }
}

namespace Test_split_as_pair{
    void test_split_1(){
        std::pair<std::string, std::string> expected("a", "b");
        auto got = split_as_pair("a b");
        if (expected != got){
            throw -1;
        }
    }

    void test_split_2(){
        std::pair<std::string, std::string> expected("a", "b");
        auto got = split_as_pair("a:b", ':');
        if (expected != got){
            throw -1;
        }
    }

    void test_split_3(){
        std::pair<std::string, std::string> expected("a", "  b");
        auto got = split_as_pair("a   b", ' ');
        if (expected != got){
            throw -1;
        }
    }

    void test_split_4(){
        std::pair<std::string, std::string> expected("abcde", "");
        auto got = split_as_pair("abcde:", ':');
        if (expected != got){
            throw -1;
        }
    }

    void test_split_5(){
        std::pair<std::string, std::string> expected("", "abcde");
        auto got = split_as_pair(":abcde", ':');
        if (expected != got){
            throw -1;
        }
    }
}

int main(){
    Test_split::test_split_1();
    Test_split::test_split_2();
    Test_split::test_split_3();
    Test_split::test_split_4();
    Test_split::test_split_5();
    Test_split_as_pair::test_split_1();
    Test_split_as_pair::test_split_2();
    Test_split_as_pair::test_split_3();
    Test_split_as_pair::test_split_4();
    Test_split_as_pair::test_split_5();
}