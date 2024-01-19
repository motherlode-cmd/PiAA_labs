#include <cassert>
#include <algorithm>
#include <unordered_map>
#include "modules/a_star.hpp"
#include <fstream>
void read_file(std::string & s_str, std::string & e_str, char & start, char & end, std::map <char, Node *> & table, std::string filename) {
    table.clear();
    std::ifstream f;
    f.open(filename);
    f>>s_str>>e_str;
    start = s_str[0];
    end = e_str[0];
    get_table(table, f);
    f.close();
}
void test() {
    std::string s_str, e_str;
    char start, end;
    std::map <char, Node *> table;
    read_file(s_str, e_str, start, end, table, "./modules/tests/input1.txt");
    assert(a_star(start, end, table) == "eda");
    read_file(s_str, e_str, start, end, table, "./modules/tests/input2.txt");
    assert(a_star(start, end, table) == "eda");
    read_file(s_str, e_str, start, end, table, "./modules/tests/input3.txt");
    assert(a_star(start, end, table) == "gfa");
    read_file(s_str, e_str, start, end, table, "./modules/tests/input4.txt");
    assert(a_star(start, end, table) == "edca");
    read_file(s_str, e_str, start, end, table, "./modules/tests/input5.txt");
    assert(a_star(start, end, table) == "edcba");
    std::cout << "Test #1 passed successfully\n";
}


int main() {
    test();
    return 0;
}
