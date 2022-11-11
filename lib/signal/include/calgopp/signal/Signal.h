#pragma once

#include "calgopp/types/Point.h"
#include "calgopp/types/Peak.h"

#include <stdint.h>
#include <exception>

namespace calgopp::signal {

template <typename Container>
Container indexes(const Container& container)
{
    Container token;
    for (const auto& index : container)
    {
        token.push_back(index);
    }
    return token;
}

class Signal
{
public:
    template <typename Container>
    Signal(const Container& values, const Container& indexes)
    {
        if (values.size() != indexes.size())
        {
            throw std::exception();
        }
        for (std::uint32_t i = 0; i < values.size(); i++)
        {
            m_points.push_back({values[i], indexes[i]});
        }
    }

    template <typename Container>
    Signal(const Container& values)
        : Signal(values, indexes<Container>(values))
    {}

    Signal()

    std::vector<types::Peak> peaks(types::PeakType type = types::PeakType::eHigh,
                                   long double distance = 0,
                                   long double height = std::numeric_limits<long double>::min());

    std::vector<types::Point> points() { return m_points; }

private:
    types::Point** m_points{nullptr};
};

} // namespace calgopp::signal
