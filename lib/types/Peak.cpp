#include "algopp/types/Peak.h"

namespace algopp::types {

bool operator==(const Peak& lhs, const Peak& rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.type == rhs.type;
}

bool operator==(const Peak&& lhs, const Peak&& rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.type == rhs.type;
}

bool operator!=(const Peak& lhs, const Peak& rhs)
{
    return !(lhs == rhs);
}

bool operator!=(const Peak&& lhs, const Peak&& rhs)
{
    return !(lhs == rhs);
}

}
