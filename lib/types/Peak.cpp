#include "calgopp/types/Peak.h"
#include "calgopp/algorithm/numeric.h"

namespace calgopp::types {

bool operator==(const Peak& lhs, const Peak& rhs)
{
    return algorithm::numeric::abs(lhs.x - rhs.x) < algorithm::numeric::cEpsilon &&
           algorithm::numeric::abs(lhs.y - rhs.y) < algorithm::numeric::cEpsilon && lhs.type == rhs.type;
}

bool operator==(const Peak&& lhs, const Peak&& rhs)
{
    return algorithm::numeric::abs(lhs.x - rhs.x) < algorithm::numeric::cEpsilon &&
           algorithm::numeric::abs(lhs.y - rhs.y) < algorithm::numeric::cEpsilon && lhs.type == rhs.type;
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
