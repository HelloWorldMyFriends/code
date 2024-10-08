#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>

void print(int x, int y) {
    std::cout << x << ", " << y << std::endl;
}

int main() {
    auto print_42 = std::bind(print, 42, std::placeholders::_1);
    std::vector<int> vec = {1, 2, 3, 4, 5};
    std::for_each(vec.begin(), vec.end(), print_42);

    return 0;
}