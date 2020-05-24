#include <iostream>
#include <vector>
#include "sorting_algorithms.h"


template <typename T>
void print(const T &array)
{
    for (int i : array) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;
}

int main()
{
    std::vector<int> array {8, 7, 9, 4, 2, 1, 0, 6, 4, 6, 5};
    auto array2 = array;
    print(array);
//    insertion_sort(array.begin(), array.end());
//    selection_sort(array.begin(), array.end());
//    bubble_sort(array.begin(), array.end());
//    merge_sort(array.begin(), array.end());
//    heap_sort(array.begin(), array.end());
    quick_sort(array.begin(), array.end());
    print(array);
    std::sort(array2.begin(), array2.end());
    print(array2);
}
