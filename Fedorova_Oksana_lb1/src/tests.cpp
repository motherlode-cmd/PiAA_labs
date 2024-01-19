#include <cassert>
#include <algorithm>
#include <unordered_map>
#include "modules/backtracking.hpp"


void test() {

    assert(start(4) == 4);
    assert(start(19) == 13);
    assert(start(29) == 14);
    assert(start(23) == 13);
    assert(start(17) == 12);
    std::cout << "Test #1 passed successfully\n";
}


int main() {
    test();
    return 0;
}
