#pragma once

#include "calgopp/types/Point.h"

namespace calgopp::signal {

class Iterator
{
public:
    Iterator() = default;

    Iterator(types::Point* point)
        : m_point(point)
    {}

    void operator++() { m_point++; }

    void operator--() { m_point--; }

    types::Point& operator*() { return *m_point; }

private:
    friend bool operator==(const Iterator& lhs, const Iterator& rhs);
    friend bool operator==(const Iterator&& lhs, const Iterator&& rhs);
    friend bool operator!=(const Iterator& lhs, const Iterator& rhs);
    friend bool operator!=(const Iterator&& lhs, const Iterator&& rhs);

    types::Point* m_point{nullptr};
};

bool operator==(const Iterator& lhs, const Iterator& rhs);

bool operator==(const Iterator&& lhs, const Iterator&& rhs);

bool operator!=(const Iterator& lhs, const Iterator& rhs);

bool operator!=(const Iterator&& lhs, const Iterator&& rhs);

} // namespace calgopp::signal
