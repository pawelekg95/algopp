#pragma once

#include "calgopp/types/Point.h"
#include "calgopp/types/Peak.h"
#include "Iterator.h"

#include <stdint.h>
#include <stdlib.h>

namespace calgopp::signal {

class Signal
{
public:
    Signal() = default;
    Signal(const Signal& other);
    Signal(Signal&& other) noexcept;

    Signal& operator=(const Signal& other);
    Signal& operator=(Signal&& other) noexcept;

    template <typename InputType>
    Signal(const InputType* values, std::size_t length)
        : m_size(length)
    {
        m_points = new types::Point[m_size]; // NOLINT cppcoreguidelines-owning-memory
        for (uint32_t i = 0; i < m_size; i++)
        {
            m_points[i] = {double(i), double(values[i])};
        }
        m_empty = m_size == 0;
        m_begin = Iterator(&m_points[0]);
        m_end = Iterator(&m_points[m_size - 1]);
    }

    ~Signal() { delete[] m_points; }

    bool empty() const { return m_empty; }

    operator bool() const { return !empty(); }

    types::Point& operator[](uint32_t index) { return m_points[index]; }

    size_t size() { return m_size; }

    Iterator begin() { return m_begin; }

    Iterator end() { return m_end; }

    //    std::vector<types::Peak> peaks(types::PeakType type = types::PeakType::eHigh,
    //                                   long double height = std::numeric_limits<long double>::min());

private:
    types::Point* m_points{nullptr};
    uint32_t m_size{0};
    bool m_empty{true};
    Iterator m_begin;
    Iterator m_end;
};

} // namespace calgopp::signal
