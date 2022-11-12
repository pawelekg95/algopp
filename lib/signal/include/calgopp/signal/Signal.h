#pragma once

#include "calgopp/types/Point.h"
#include "calgopp/types/Peak.h"
#include "Iterator.h"

#include <cstdint>
#include <cstdlib>

namespace calgopp::signal {

class Signal
{
public:
    Signal();
    Signal(const Signal& other);
    Signal(Signal&& other) noexcept;

    Signal& operator=(const Signal& other);
    Signal& operator=(Signal&& other) noexcept;

    template <typename InputType>
    Signal(const InputType* values, std::size_t length)
        : m_size(length)
        , m_capacity(m_size > 0 ? m_size * 2 : 10)
    {
        m_points = new types::Point[m_capacity]; // NOLINT cppcoreguidelines-owning-memory
        for (uint32_t i = 0; i < m_size; i++)
        {
            m_points[i] = {double(i), double(values[i])};
        }
        m_empty = m_size == 0;
        m_begin = Iterator(m_points);
        m_end = Iterator(&m_points[m_size]);
    }

    template <typename Container>
    Signal(const Container& values)
        : Signal(values.data(), values.size())
    {}

    Signal(const types::Point* points, std::size_t size);

    ~Signal() { delete[] m_points; }

    bool empty() const { return m_empty; }

    operator bool() const { return !empty(); }

    void operator+=(const types::Point& point);

    void operator+=(const Signal& signal);

    void operator--();

    void append(const types::Point& point);

    void remove(uint32_t index);

    types::Point& operator[](uint32_t index);

    std::size_t size() const { return m_size; }

    std::size_t capacity() const { return m_capacity; }

    Iterator begin() const { return m_begin; }

    Iterator end() const { return m_end; }

    //    std::vector<types::Peak> peaks(types::PeakType type = types::PeakType::eHigh,
    //                                   long double height = std::numeric_limits<long double>::min());

private:
    uint32_t m_size{};
    uint32_t m_capacity{};
    bool m_empty{true};
    types::Point* m_points{nullptr};
    Iterator m_begin;
    Iterator m_end;
};

} // namespace calgopp::signal
