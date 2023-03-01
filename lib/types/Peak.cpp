#include "calgopp/types/Peak.h"

#include "calgopp/math/math.h"

namespace calgopp::types {

bool operator==(const Peak& lhs, const Peak& rhs)
{
    return math::abs(lhs.x - rhs.x) < math::epsilon() && lhs.y == rhs.y && lhs.type == rhs.type;
}

bool operator==(const Peak&& lhs, const Peak&& rhs)
{
    return math::abs(lhs.x - rhs.x) < math::epsilon() && lhs.y == rhs.y && lhs.type == rhs.type;
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
