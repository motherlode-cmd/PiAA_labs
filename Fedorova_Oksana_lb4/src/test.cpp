#include "modules/kmp.hpp"
#include "cassert"
#include "iostream"
void test() {
    //std::cout<<find_shift("sss", "sss")<<std::endl;
    assert(find_shift("abcde", "abcde") == 0);
    assert(find_shift("abcde", "bcdea") == 4);
    assert(find_shift("aaa", "aaa") == 0);
    assert(find_shift("aaab", "aaad") == -1);
    assert(find_shift("dada", "adad") == 3);
    std::cout<<"Suckessfull";
}
int main() {
    test();
    return 0;
}