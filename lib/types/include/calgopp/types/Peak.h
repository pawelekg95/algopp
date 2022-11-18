#pragma once

#include "calgopp/types/Point.h"

namespace calgopp::types {

enum class PeakType
{
    eLow,
    eHigh
};

struct Peak : public Point
{
    Peak() = default;

    template <typename T>
    Peak(T x, T y)
        : Point(x, y)
    {}

    template <typename T>
    Peak(T x, T y, PeakType type)
        : Point(x, y)
        , type(type)
    {}

    template <typename T, typename Y>
    Peak(T x, Y y)
        : Point(x, y)
    {}

    template <typename T, typename Y>
    Peak(T x, Y y, PeakType type)
        : Point(x, y)
        , type(type)
    {}

    PeakType type{PeakType::eHigh};
};

bool operator==(const Peak& lhs, const Peak& rhs);

bool operator==(const Peak&& lhs, const Peak&& rhs);

bool operator!=(const Peak& lhs, const Peak& rhs);

bool operator!=(const Peak&& lhs, const Peak&& rhs);

} // namespace calgopp::types
