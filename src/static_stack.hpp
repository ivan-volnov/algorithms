#ifndef STATIC_STACK_HPP
#define STATIC_STACK_HPP

#include <cassert>


template <class T, size_t N>
class StaticStack
{
public:
    StaticStack() = default;
    ~StaticStack() = default;
    StaticStack(const StaticStack &) = delete;
    StaticStack &operator=(const StaticStack &) = delete;

    T &operator[] (size_t idx)
    {
        return data_[idx];
    }

    const T &operator[] (size_t idx) const
    {
        return data_[idx];
    }

    T *begin()
    {
        return data_;
    }

    T *end()
    {
        return data_ + head_;
    }

    void store(T &&value)
    {
        assert(head_ < N);
        data_[head_++] = std::forward<T>(value);
    }

    T take()
    {
        assert(head_ > 0);
        return std::move(data_[--head_]);
    }

    void pop()
    {
        --head_;
    }

    T &top()
    {
        return data_[head_ - 1];
    }

    size_t capacity() const
    {
        return N;
    }

    size_t size() const
    {
        return head_;
    }

    bool have_space() const
    {
        return head_ < N;
    }

    bool empty() const
    {
        return !head_;
    }

private:
    size_t head_ = 0;
    T data_[N];
};

#endif // STATIC_STACK_HPP
