#include "calgopp/signal/Signal.h"

#include <algorithm>
#include <exception>

namespace calgopp::signal {

Signal::Signal(const std::vector<long double>& values, std::optional<std::vector<long double>> indexes)
    : m_points(values.size())
{
    if (indexes && values.size() != (*indexes).size())
    {
        throw std::exception();
    }
    for (std::uint32_t i = 0; i < values.size(); i++)
    {
        m_points[i] = {(indexes ? (*indexes)[i] : i), values[i]};
    }
}

std::vector<types::Peak> Signal::peaks(types::PeakType type, long double distance, long double height)
{
    auto isPeak = [&type](long double first, long double second, long double third) -> bool {
        return (type == types::PeakType::eLow ? first > second && second < third : first < second && second > third);
    };
    std::vector<types::Peak> peaks;
    auto beginIt = m_points.begin();
    while (beginIt < m_points.end() - 2)
    {
        beginIt++;
        if ((*beginIt).y < height)
        {
            continue;
        }
        if (isPeak((beginIt - 1)->y, beginIt->y, (beginIt + 1)->y))
        {
            peaks.emplace_back(types::Peak({beginIt->x, beginIt->y, type}));
        }
    }

    if (distance == 0 || distance == 1 || distance == 2 || peaks.empty())
    {
        return peaks;
    }

    auto currentPeak = peaks.begin();
    std::vector<types::Peak> filteredPeaks;
    auto comparator = [](const types::Peak& first, const types::Peak& second) { return first.y <= second.y; };
    for (std::uint32_t i = 0; i < m_points.size(); i += distance)
    {
        std::vector<types::Peak> inRangePeaks;
        while ((*currentPeak).x >= i && (*currentPeak).x < i + distance && currentPeak < peaks.end())
        {
            inRangePeaks.emplace_back(*currentPeak);
            currentPeak++;
        }
        if (!inRangePeaks.empty())
        {
            filteredPeaks.emplace_back(type == types::PeakType::eLow
                                           ? *std::min_element(inRangePeaks.begin(), inRangePeaks.end(), comparator)
                                           : *std::max_element(inRangePeaks.begin(), inRangePeaks.end(), comparator));
        }
    }

    return filteredPeaks;
}

} // namespace calgopp::signal
