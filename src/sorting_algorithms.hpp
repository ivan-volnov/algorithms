#ifndef SORTING_ALGORITHMS_HPP
#define SORTING_ALGORITHMS_HPP

#include <algorithm>


// Time Complexity: Best O(n), Average O(n^2), Worst O(n^2). Space Complexity: O(1)
template<typename It, typename Predicate = std::less<typename std::iterator_traits<It>::value_type>>
void insertion_sort(It begin, It end, Predicate pred = Predicate())
{
    if (begin == end) {
        return;
    }
    for (auto it = std::next(begin); it != end; ++it) {
        for (auto it_cur = it, it_prev = std::prev(it); pred(*it_cur, *it_prev); --it_cur, --it_prev) {
            std::iter_swap(it_cur, it_prev);
            if (it_prev == begin) {
                break;
            }
        }
    }
}


// Time Complexity: Best O(n^2), Average O(n^2), Worst O(n^2). Space Complexity: O(1)
template<typename It, typename Predicate = std::less<typename std::iterator_traits<It>::value_type>>
void selection_sort(It begin, It end, Predicate pred = Predicate())
{
    for (; begin != end; ++begin) {
        std::iter_swap(std::min_element(begin, end, pred), begin);
    }
}


// Time Complexity: Best O(n), Average O(n^2), Worst O(n^2). Space Complexity: O(1)
template<typename It, typename Predicate = std::less<typename std::iterator_traits<It>::value_type>>
void bubble_sort(It begin, It end, Predicate pred = Predicate())
{
    for (; begin != end; --end) {
        for (auto it_cur = std::next(begin), it_prev = begin; it_cur != end; ++it_cur, ++it_prev) {
            if (pred(*it_cur, *it_prev)) {
                std::iter_swap(it_cur, it_prev);
            }
        }
    }
}


// Time Complexity: Best O(n log(n)), Average O(n log(n)), Worst O(n log(n)). Space Complexity: O(n)
template<typename It, typename Predicate = std::less<typename std::iterator_traits<It>::value_type>>
void merge_sort(It begin, It end, Predicate pred = Predicate())
{
    const auto size = std::distance(begin, end);
    if (size > 1) {
        const auto middle = std::next(begin, size / 2);
        merge_sort(begin, middle, pred);
        merge_sort(middle, end, pred);
        std::inplace_merge(begin, middle, end, pred);
    }
}


// Time Complexity: Best O(n log(n)), Average O(n log(n)), Worst O(n log(n)). Space Complexity: O(1)
template<typename It, typename Predicate = std::less<typename std::iterator_traits<It>::value_type>>
void heap_sort(It begin, It end, Predicate pred = Predicate())
{
    std::make_heap(begin, end, pred);
    std::sort_heap(begin, end, pred);
}


// Time Complexity: Best O(n log(n)), Average O(n log(n)), Worst O(n^2). Space Complexity: O(log(n))
template<typename It, typename Predicate = std::less<typename std::iterator_traits<It>::value_type>>
void quick_sort(It begin, It end, Predicate pred = Predicate())
{
    if (begin != end)
    {
        const auto partition = [begin, end, pred]() {
            const auto pivot = *std::next(begin, std::distance(begin, end) / 2);
            auto partition_first = std::partition(begin, end, [&pivot, pred](const auto &e) { return pred(e, pivot); });
            return std::make_pair(partition_first, std::partition(partition_first, end, [&pivot, pred](const auto &e) { return !pred(pivot, e); }));
        }();
        quick_sort(begin, partition.first, pred);
        quick_sort(partition.second, end, pred);
    }
}


#endif // SORTING_ALGORITHMS_HPP
