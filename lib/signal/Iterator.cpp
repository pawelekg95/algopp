#include "calgopp/signal/Iterator.h"

namespace calgopp::signal {

bool operator==(const Iterator& lhs, const Iterator& rhs)
{
    return lhs.m_point == rhs.m_point;
}

bool operator==(const Iterator&& lhs, const Iterator&& rhs)
{
    return lhs.m_point == rhs.m_point;
}

bool operator!=(const Iterator& lhs, const Iterator& rhs)
{
    return !(lhs == rhs);
}

bool operator!=(const Iterator&& lhs, const Iterator&& rhs)
{
    return !(lhs == rhs);
}

} // namespace calgopp::signal
