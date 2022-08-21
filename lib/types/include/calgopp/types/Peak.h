#ifndef PEAK_H
#define PEAK_H

#include "calgopp/types/Point.h"

namespace calgopp::types {

enum class PeakType
{
    eLow,
    eHigh
};

struct Peak : public Point
{
    Peak(long double x, long double y)
        : Peak(x, y, PeakType::eHigh)
    {}

    Peak(long double x, long double y, PeakType type)
        : Point(x, y)
        , type(type)
    {}

    PeakType type{};
};

bool operator==(const Peak& lhs, const Peak& rhs);

bool operator==(const Peak&& lhs, const Peak&& rhs);

bool operator!=(const Peak& lhs, const Peak& rhs);

bool operator!=(const Peak&& lhs, const Peak&& rhs);

} // namespace calgopp::types

#endif /* PEAK_H */
