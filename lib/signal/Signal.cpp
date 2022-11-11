#include "calgopp/signal/Signal.h"

namespace calgopp::signal {

Signal::Signal(const Signal& other)
    : m_size(other.m_size)
    , m_empty(other.m_empty)
{
    m_points = new types::Point[m_size]; // NOLINT cppcoreguidelines-owning-memory
    for (uint32_t i = 0; i < m_size; i++)
    {
        m_points[i] = other.m_points[i];
    }
    m_end = m_begin = Iterator(m_points);
}

Signal::Signal(Signal&& other) noexcept
    : m_points(other.m_points)
    , m_size(other.m_size)
    , m_empty(other.m_empty)
{
    other.m_points = nullptr;
    other.m_size = 0;
    m_empty = true;
}

Signal& Signal::operator=(Signal&& other) noexcept
{
    m_size = other.m_size;
    m_empty = other.m_empty;
    m_points = other.m_points;
    other.m_points = nullptr;
    other.m_size = 0;
    m_empty = true;
    return *this;
}

Signal& Signal::operator=(const Signal& other)
{
    if (&other == this)
    {
        return *this;
    }
    m_size = other.m_size;
    m_empty = other.m_empty;
    m_points = new types::Point[m_size]; // NOLINT cppcoreguidelines-owning-memory
    for (uint32_t i = 0; i < m_size; i++)
    {
        m_points[i] = other.m_points[i];
    }
    return *this;
}

// std::vector<types::Peak> Signal::peaks(types::PeakType type, long double distance, long double height)
//{
//    auto isPeak = [&type](long double first, long double second, long double third) -> bool {
//        return (type == types::PeakType::eLow ? first > second && second < third : first < second && second > third);
//    };
//    std::vector<types::Peak> peaks;
//    auto beginIt = m_points.begin();
//    while (beginIt < m_points.end() - 2)
//    {
//        beginIt++;
//        if ((*beginIt).y < height)
//        {
//            continue;
//        }
//        if (isPeak((beginIt - 1)->y, beginIt->y, (beginIt + 1)->y))
//        {
//            peaks.emplace_back(types::Peak({beginIt->x, beginIt->y, type}));
//        }
//    }
//
//    if (distance == 0 || distance == 1 || distance == 2 || peaks.empty())
//    {
//        return peaks;
//    }
//
//    auto currentPeak = peaks.begin();
//    std::vector<types::Peak> filteredPeaks;
//    auto comparator = [](const types::Peak& first, const types::Peak& second) { return first.y <= second.y; };
//    for (std::uint32_t i = 0; i < m_points.size(); i += distance)
//    {
//        std::vector<types::Peak> inRangePeaks;
//        while ((*currentPeak).x >= i && (*currentPeak).x < i + distance && currentPeak < peaks.end())
//        {
//            inRangePeaks.emplace_back(*currentPeak);
//            currentPeak++;
//        }
//        if (!inRangePeaks.empty())
//        {
//            filteredPeaks.emplace_back(type == types::PeakType::eLow
//                                           ? *std::min_element(inRangePeaks.begin(), inRangePeaks.end(), comparator)
//                                           : *std::max_element(inRangePeaks.begin(), inRangePeaks.end(), comparator));
//        }
//    }
//
//    return filteredPeaks;
//}

} // namespace calgopp::signal
