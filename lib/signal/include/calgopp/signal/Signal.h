#pragma once

#include "calgopp/types/Point.h"
#include "calgopp/types/Peak.h"
#include "calgopp/types/Container.h"
#include "calgopp/algorithm/numeric.h"

namespace calgopp::signal {

class Signal
{
public:
    Signal() = default;
    Signal(const Signal& other) = default;
    Signal(Signal&& other) noexcept;

    Signal& operator=(const Signal& other);
    Signal& operator=(Signal&& other) noexcept;

    template <typename InputContainer>
    Signal(const InputContainer& values)
        : Signal(values.data(), values.size())
    {}

    template <typename Type>
    Signal(const Type* values, unsigned int size)
    {
        for (unsigned int i = 0; i < size; i++)
        {
            m_points.append(types::Point{i, values[i]});
        }
    }

    Signal(types::Container<types::Point> points)
        : m_points(static_cast<types::Container<types::Point>&&>(points))
    {}

    Signal(const types::Point* points, unsigned int size);

    ~Signal() = default;

    bool empty() const { return m_points.empty(); }

    operator bool() const { return !empty(); }

    void operator+=(const types::Point& point);

    void operator+=(const Signal& signal);

    void operator--();

    void append(const types::Point& point);

    void remove(unsigned int index);

    types::Point& operator[](unsigned int index);

    int size() const { return m_points.size(); }

    types::Container<types::Peak>
    peaks(types::PeakType type = types::PeakType::eHigh, long double height = 0, unsigned int distance = 1);

    types::Container<types::Point>::Iterator begin() const { return m_points.begin(); }

    types::Container<types::Point>::Iterator end() const { return m_points.end(); }

private:
    types::Container<types::Point> m_points;
};

} // namespace calgopp::signal
