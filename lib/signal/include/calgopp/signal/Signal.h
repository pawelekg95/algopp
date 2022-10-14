#pragma once

#include "calgopp/types/Point.h"
#include "calgopp/types/Peak.h"

#include <vector>
#include <cstdint>
#include <limits>
#include <optional>

namespace calgopp::signal {

class Signal
{
public:
    Signal(const std::vector<long double>& values, std::optional<std::vector<long double>> indexes);

    std::vector<types::Peak> peaks(types::PeakType type = types::PeakType::eHigh,
                                   long double distance = 0,
                                   long double height = std::numeric_limits<long double>::min());

    std::vector<types::Point> points() { return m_points; }

private:
    std::vector<types::Point> m_points;
};

} // namespace calgopp::signal
