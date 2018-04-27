#include <deque>
#include <iostream>

template <typename T>
void printPath (std::deque<T>& vec) {
    size_t i = 0;
    for (; i < vec.size() - 1; ++i)
        std::cout << vec[i] << " -> ";
    std::cout << vec[i] << std::endl;
}