#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <functional>


template<typename T, typename Predicate = std::less<T>>
T median(const T &a, const T &b, const T &c, Predicate pred = Predicate())
{
    if (pred(a, b)) {
        if (pred(b, c)) {
            return b;
        }
        if (pred(a, c)) {
            return c;
        }
        return a;
    }
    if (pred(a, c)) {
        return a;
    }
    if (pred(b, c)) {
        return c;
    }
    return b;
}

#endif // ALGORITHMS_HPP
