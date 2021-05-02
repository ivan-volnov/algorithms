#ifndef STATIC_STACK_HPP
#define STATIC_STACK_HPP

#include <cassert>


template<class T, size_t N>
class StaticStack
{
public:
    StaticStack() = default;
    ~StaticStack() = default;
    StaticStack(const StaticStack &) = delete;
    StaticStack &operator=(const StaticStack &) = delete;

    T &operator[] (size_t idx)
    {
        return _stack[idx];
    }

    const T &operator[] (size_t idx) const
    {
        return _stack[idx];
    }

    T *begin()
    {
        return _stack;
    }

    T *end()
    {
        return _stack + head;
    }

    void store(T &&value)
    {
        assert(head < N);
        _stack[head++] = std::forward<T>(value);
    }

    T take()
    {
        assert(head > 0);
        return std::move(_stack[--head]);
    }

    void pop()
    {
        --head;
    }

    T &top()
    {
        return _stack[head - 1];
    }

    size_t capacity() const
    {
        return N;
    }

    size_t size() const
    {
        return head;
    }

    bool have_space() const
    {
        return head < N;
    }

    bool empty() const
    {
        return !head;
    }

private:
    size_t head = 0;
    T _stack[N];
};

#endif // STATIC_STACK_HPP
