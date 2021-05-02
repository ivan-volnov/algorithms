#ifndef STATIC_CIRCULAR_BUFFER_HPP
#define STATIC_CIRCULAR_BUFFER_HPP

#include <cassert>


template <typename T, size_t N>
class StaticCircularBuffer
{
public:
    StaticCircularBuffer() = default;
    ~StaticCircularBuffer() = default;
    StaticCircularBuffer(const StaticCircularBuffer &) = delete;
    StaticCircularBuffer &operator=(const StaticCircularBuffer &) = delete;

    void store(T &&elem)
    {
        assert(m_length < N);
        m_buffer[m_head] = std::forward<T>(elem);
        m_head = (m_head + 1) % N;
        ++m_length;
    }

    T take()
    {
        assert(m_length > 0);
        return std::move(m_buffer[(N - m_length-- + m_head) % N]);
    }

    void clear()
    {
        m_head = m_length = 0;
    }

    size_t capacity()
    {
        return N;
    }

    size_t size()
    {
        return m_length;
    }

    bool have_space() const
    {
        return m_length < N;
    }

    bool empty() const
    {
        return !m_length;
    }

private:
    size_t m_head = 0;
    size_t m_length = 0;
    T m_buffer[N];
};

#endif // STATIC_CIRCULAR_BUFFER_HPP
