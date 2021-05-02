#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <iostream>
#include <vector>
#include "sorting_algorithms.hpp"
#include "static_circular_buffer.hpp"


template <typename T>
void print(const T &array)
{
    for (int i : array) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;
}

TEST_CASE("sorting test")
{
    std::vector<int> array {8, 7, 9, 4, 2, 1, 0, 6, 4, 6, 5};
    auto array2 = array;
    std::sort(array2.begin(), array2.end());

    SECTION("insertion_sort") {
        insertion_sort(array.begin(), array.end());
        REQUIRE(array == array2);
    }

    SECTION("selection_sort") {
        selection_sort(array.begin(), array.end());
        REQUIRE(array == array2);
    }

    SECTION("bubble_sort") {
        bubble_sort(array.begin(), array.end());
        REQUIRE(array == array2);
    }

    SECTION("merge_sort") {
        merge_sort(array.begin(), array.end());
        REQUIRE(array == array2);
    }

    SECTION("heap_sort") {
        heap_sort(array.begin(), array.end());
        REQUIRE(array == array2);
    }

    SECTION("quick_sort") {
        quick_sort(array.begin(), array.end());
        REQUIRE(array == array2);
    }
}

TEST_CASE("StaticCircularBuffer test")
{
    StaticCircularBuffer<char, 5> buffer;
    REQUIRE(buffer.capacity() == 5);
    REQUIRE(buffer.size() == 0);

    buffer.store('A');
    REQUIRE(buffer.size() == 1);
    buffer.store('B');
    REQUIRE(buffer.size() == 2);
    buffer.store('C');
    REQUIRE(buffer.size() == 3);
    buffer.store('D');
    REQUIRE(buffer.size() == 4);
    buffer.store('E');
    REQUIRE(buffer.size() == 5);

    REQUIRE(buffer.take() == 'A');
    REQUIRE(buffer.size() == 4);
    REQUIRE(buffer.take() == 'B');
    REQUIRE(buffer.size() == 3);
    REQUIRE(buffer.take() == 'C');
    REQUIRE(buffer.size() == 2);
    REQUIRE(buffer.take() == 'D');
    REQUIRE(buffer.size() == 1);
    REQUIRE(buffer.take() == 'E');

    buffer.store('F');
    REQUIRE(buffer.size() == 1);
    buffer.store('G');
    REQUIRE(buffer.size() == 2);

    REQUIRE(buffer.take() == 'F');
    REQUIRE(buffer.size() == 1);
    REQUIRE(buffer.take() == 'G');
    REQUIRE(buffer.size() == 0);

    buffer.store('H');
    REQUIRE(buffer.size() == 1);

    REQUIRE(buffer.take() == 'H');
    REQUIRE(buffer.size() == 0);

    buffer.store('I');
    REQUIRE(buffer.size() == 1);
    buffer.store('J');
    REQUIRE(buffer.size() == 2);
    buffer.store('K');
    REQUIRE(buffer.size() == 3);
    buffer.store('L');
    REQUIRE(buffer.size() == 4);

    buffer.clear();
    REQUIRE(buffer.size() == 0);

    buffer.store('A');
    REQUIRE(buffer.size() == 1);
    buffer.store('B');
    REQUIRE(buffer.size() == 2);
    REQUIRE(buffer.take() == 'A');
    REQUIRE(buffer.size() == 1);
    buffer.store('C');
    REQUIRE(buffer.size() == 2);
    REQUIRE(buffer.take() == 'B');
    REQUIRE(buffer.size() == 1);
    buffer.store('D');
    REQUIRE(buffer.size() == 2);
    buffer.store('E');
    REQUIRE(buffer.size() == 3);
    buffer.store('F');
    REQUIRE(buffer.size() == 4);
    buffer.store('G');
    REQUIRE(buffer.size() == 5);
    REQUIRE(buffer.take() == 'C');
    REQUIRE(buffer.size() == 4);
}
