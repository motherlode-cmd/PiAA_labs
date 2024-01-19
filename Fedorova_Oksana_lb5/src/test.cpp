#include "modules/aho.hpp"
#include "cassert"

void test(){
    std::string txt = "abcdefg";
    bohr_ini();
    std::string tmp = "abc";
    char jock = 'a';
    create_bohr(tmp, 0, jock);
    find_all_pos(txt);
    assert(ans.size() == 0);
    bohr.clear();
    txt = "ababcbdb";
    tmp = "ab";
    jock = 'a';
    create_bohr(tmp, 0, jock);
    find_all_pos(txt);
    assert(ans.size() == 2);
    bohr.clear();
    ans.clear();
    txt = "abcbdcdes";
    tmp = "bcb";
    jock = 'b';
    create_bohr(tmp, 0, jock);
    find_all_pos(txt);
    assert(ans.size() == 1);
    std::cout<<"all tests passed";
    //assert(ans.size() == 0);
}
int main() {
    test();
    return 0;
}