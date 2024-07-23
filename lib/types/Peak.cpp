#include "calgopp/types/Peak.h"

namespace calgopp::types {

bool operator==(const Peak& lhs, const Peak& rhs)
{
    return std::abs(lhs.x - rhs.x) < std::numeric_limits<double>::epsilon() && lhs.y == rhs.y && lhs.type == rhs.type;
}

bool operator==(const Peak&& lhs, const Peak&& rhs)
{
    return std::abs(lhs.x - rhs.x) < std::numeric_limits<double>::epsilon() && lhs.y == rhs.y && lhs.type == rhs.type;
}

bool operator!=(const Peak& lhs, const Peak& rhs)
{
    return !(lhs == rhs);
}

bool operator!=(const Peak&& lhs, const Peak&& rhs)
{
    return !(lhs == rhs);
}

} // namespace calgopp::types
