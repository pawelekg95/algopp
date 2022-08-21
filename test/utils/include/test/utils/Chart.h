#pragma once

#include "calgopp/types/Point.h"

#include <vector>

using namespace calgopp;

namespace test {

class Chart
{
public:
    explicit Chart(const std::vector<types::Point>& dataset)
        : m_points(dataset)
    {}

    void show();

private:
    std::vector<types::Point> m_points;
};

} // namespace test
