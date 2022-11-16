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

    template <template <typename> class Container, typename Type>
    Signal(const Container<Type>& values)
        : Signal(types::Container<Type>(values))
    {}

    template <template <typename> class Container, typename Type>
    Signal(const Container<Type>& values, const Container<Type>& indexes)
        : Signal(types::Container<Type>(values), types::Container<Type>(indexes))
    {}

    template <typename InputType>
    Signal(const InputType* values, unsigned int length)
        : Signal(types::Container<InputType>(values, length))
    {}

    template <template <typename, typename> class Container, typename Type>
    Signal(const Container<Type, unsigned int>& values)
        : Signal(types::Container<Type>(values))
    {}

    template <template <typename, typename> class Container, typename Type, typename Size>
    Signal(const Container<Type, Size>& values, const Container<Type, Size>& indexes)
        : Signal(types::Container<Type>(values), types::Container<Type>(indexes))
    {}

    template <typename Type>
    Signal(const types::Container<Type>& values, const types::Container<Type>& indexes)
    {
        if (values.size() != indexes.size())
        {
            throw "Invalid size of containers";
        }
        for (unsigned int i = 0; i < values.size(); i++)
        {
            m_points.append(types::Point{indexes.at(i), values.at(i)});
        }
    }

    template <typename Type>
    Signal(const types::Container<Type>& values)
        : Signal(values, algorithm::numeric::range<Type>(0, values.size()))
    {}

    Signal(types::Container<types::Point> values)
        : m_points(static_cast<types::Container<types::Point>&&>(values))
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
    peaks(types::PeakType type = types::PeakType::eHigh, long double height = 0, long double distance = 0);

    types::Container<types::Point>::Iterator begin() const { return m_points.begin(); }

    types::Container<types::Point>::Iterator end() const { return m_points.end(); }

private:
    types::Container<types::Point> m_points;
};

} // namespace calgopp::signal
