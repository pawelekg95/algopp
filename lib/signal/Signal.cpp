#include "calgopp/signal/Signal.h"

#include <stdexcept>

namespace calgopp::signal {

Signal::Signal()
    : m_size(0)
    , m_capacity(10)
    , m_points(new types::Point[m_capacity])
{}

Signal::Signal(const types::Point* points, std::size_t size)
    : m_size(size)
    , m_capacity(m_size > 0 ? m_size * 2 : 10)
{
    m_points = new types::Point[m_capacity]; // NOLINT cppcoreguidelines-owning-memory
    for (uint32_t i = 0; i < m_size; i++)
    {
        m_points[i] = points[i];
    }
    m_empty = m_size == 0;
    m_begin = Iterator(m_points);
    m_end = Iterator(&m_points[m_size]);
}

Signal::Signal(const Signal& other)
    : m_size(other.m_size)
    , m_capacity(other.m_capacity)
    , m_empty(other.m_empty)
{
    m_points = new types::Point[m_capacity]; // NOLINT cppcoreguidelines-owning-memory
    for (uint32_t i = 0; i < m_size; i++)
    {
        m_points[i] = other.m_points[i];
    }
    m_end = m_begin = Iterator(m_points);
}

Signal::Signal(Signal&& other) noexcept
    : m_size(other.m_size)
    , m_capacity(other.m_capacity)
    , m_empty(other.m_empty)
    , m_points(other.m_points)
{
    other.m_points = nullptr;
    other.m_size = 0;
    other.m_capacity = 0;
    other.m_empty = true;
}

Signal& Signal::operator=(Signal&& other) noexcept
{
    m_size = other.m_size;
    m_capacity = other.m_capacity;
    m_empty = other.m_empty;
    m_points = other.m_points;
    other.m_points = nullptr;
    other.m_size = 0;
    other.m_capacity = 0;
    other.m_empty = true;
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
    m_capacity = other.m_capacity;
    m_points = new types::Point[m_capacity]; // NOLINT cppcoreguidelines-owning-memory
    for (uint32_t i = 0; i < m_size; i++)
    {
        m_points[i] = other.m_points[i];
    }
    return *this;
}

void Signal::operator+=(const types::Point& point)
{
    append(point);
}

void Signal::operator--()
{
    remove(m_size - 1);
}

void Signal::operator+=(const Signal& signal)
{
    for (const auto& point : signal)
    {
        append(point);
    }
}

void Signal::append(const types::Point& point)
{
    if (m_size >= m_capacity)
    {
        m_capacity = m_capacity * 2;
        auto* tmp = new types::Point[m_capacity];
        for (uint32_t i = 0; i < m_size; i++)
        {
            tmp[i] = m_points[i];
        }
        delete[] m_points;
        m_points = tmp;
    }
    m_points[m_size] = point;
    m_size++;
    m_empty = m_size == 0;
}

void Signal::remove(uint32_t index)
{
    if (index >= m_size)
    {
        throw std::runtime_error("Index out of scope");
    }
    for (uint32_t i = index; i < m_size - 1; i++)
    {
        m_points[i] = m_points[i + 1];
    }
    m_size--;
    m_empty = m_size == 0;
}

types::Point& Signal::operator[](uint32_t index)
{
    if (index >= m_size)
    {
        throw std::runtime_error("Index out of scope");
    }
    return m_points[index];
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
