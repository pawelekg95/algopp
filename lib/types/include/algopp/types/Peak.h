#ifndef PEAK_H
#define PEAK_H

#include "algopp/types/Point.h"

namespace algopp::types {

enum class PeakType
{
    eLow,
    eHigh
};

struct Peak : public Point
{
    PeakType type;
};

bool operator==(const Peak& lhs, const Peak& rhs);

bool operator==(const Peak&& lhs, const Peak&& rhs);

bool operator!=(const Peak& lhs, const Peak& rhs);

bool operator!=(const Peak&& lhs, const Peak&& rhs);

} // namespace algopp::types

#endif /* PEAK_H */