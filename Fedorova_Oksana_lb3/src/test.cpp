#include "modules/lib.hpp"
#include <fstream>
#include <cassert>
void testing() {
    ofstream ofs;
    ofs.open("modules/answers.txt");
    test("modules/input.txt", ofs);
    //std::cout<<"HERE"<<std::endl;
    test("modules/input2.txt", ofs);
    ofs.close();
    ifstream check;
    check.open("modules/check.txt");
    string true_ans;
    string tmp;
    while (check) {
        check >> tmp;
        true_ans+=tmp;
    }
    check.close();
    string ans;
    check.open("modules/answers.txt");
    while (check) {
        check >> tmp;
        ans+=tmp;
    }
    assert(true_ans == ans);
    std::cout<<"Passed"<<endl;
    //test("modules/input2.txt", ofs);
}
int main() {
    testing();
}