#ifndef STATIC_CIRCULAR_BUFFER_HPP
#define STATIC_CIRCULAR_BUFFER_HPP

#include <cassert>


template <class T, size_t N>
class StaticCircularBuffer
{
public:
    StaticCircularBuffer() = default;
    ~StaticCircularBuffer() = default;
    StaticCircularBuffer(const StaticCircularBuffer &) = delete;
    StaticCircularBuffer &operator=(const StaticCircularBuffer &) = delete;

    void store(T &&elem)
    {
        assert(size_ < N);
        data_[head_] = std::forward<T>(elem);
        head_ = (head_ + 1) % N;
        ++size_;
    }

    T take()
    {
        assert(size_ > 0);
        return std::move(data_[(N - size_-- + head_) % N]);
    }

    void clear()
    {
        head_ = size_ = 0;
    }

    size_t capacity()
    {
        return N;
    }

    size_t size()
    {
        return size_;
    }

    bool have_space() const
    {
        return size_ < N;
    }

    bool empty() const
    {
        return !size_;
    }

private:
    size_t head_ = 0;
    size_t size_ = 0;
    T data_[N];
};

#endif // STATIC_CIRCULAR_BUFFER_HPP
