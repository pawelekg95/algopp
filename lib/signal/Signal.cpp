#include "calgopp/signal/Signal.h"

namespace calgopp::signal {

Signal::Signal(const types::Point* points, unsigned int size)
    : m_points(points, size)
{}

Signal::Signal(Signal&& other) noexcept
    : m_points(static_cast<types::Container<types::Point>&&>(other.m_points))
{}

Signal& Signal::operator=(Signal&& other) noexcept
{
    if (&other == this)
    {
        return *this;
    }
    m_points = static_cast<types::Container<types::Point>&&>(other.m_points);
    return *this;
}

Signal& Signal::operator=(const Signal& other)
{
    if (&other == this)
    {
        return *this;
    }
    m_points = other.m_points;
    return *this;
}

void Signal::operator+=(const types::Point& point)
{
    append(point);
}

void Signal::operator--()
{
    m_points.remove(m_points.size() - 1);
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
    m_points.append(point);
}

void Signal::remove(unsigned int index)
{
    m_points.remove(index);
}

types::Point& Signal::operator[](unsigned int index)
{
    return m_points[index];
}

types::Container<types::Peak> Signal::peaks(types::PeakType type, long double height, long double distance)
{
    auto isPeak = [&type](long double first, long double second, long double third) -> bool {
        return (type == types::PeakType::eLow ? first > second && second < third : first < second && second > third);
    };

    auto lastElementIsPeak = [&type](long double first, long double second) -> bool {
        return (type == types::PeakType::eLow ? first > second : first < second);
    };

    types::Container<types::Peak> peaks;
    auto beginIt = begin();
    auto endIt = end();
    while (beginIt < endIt - 2)
    {
        beginIt++;
        if ((*beginIt).y < height)
        {
            continue;
        }
        if (isPeak((*(beginIt - 1)).y, (*beginIt).y, (*(beginIt + 1)).y))
        {
            peaks.append(types::Peak({(*beginIt).x, (*beginIt).y, type}));
        }
        else if (beginIt == endIt - 2 && lastElementIsPeak((*beginIt).y, (*(beginIt + 1)).y))
        {
            peaks.append(types::Peak({(*(beginIt + 1)).x, (*(beginIt + 1)).y, type}));
        }
    }

    if (distance == 0 || distance == 1 || distance == 2 || peaks.empty())
    {
        return peaks;
    }

    auto currentPeak = peaks.begin();
    types::Container<types::Peak> filteredPeaks;
    auto minComparator = [](const types::Peak& first, const types::Peak& second) -> bool {
        return first.y <= second.y;
    };
    auto maxComparator = [](const types::Peak& first, const types::Peak& second) -> bool {
        return first.y >= second.y;
    };
    for (unsigned int i = 0; i < m_points.size(); i += int(distance))
    {
        types::Container<types::Peak> inRangePeaks;
        while ((*currentPeak).x >= i && (*currentPeak).x <= i + distance && currentPeak < peaks.end())
        {
            inRangePeaks.append(*currentPeak);
            currentPeak++;
        }
        auto elementToAdd = type == types::PeakType::eLow
                            ? *algorithm::numeric::findElement<types::Peak>(inRangePeaks.begin(),
                                                                            inRangePeaks.end(),
                                                                            minComparator)
                            : *algorithm::numeric::findElement<types::Peak>(inRangePeaks.begin(),
                                                                            inRangePeaks.end(),
                                                                            maxComparator);
        if (!inRangePeaks.empty() && filteredPeaks.empty())
        {
            filteredPeaks.append(elementToAdd);
        }
        else if (!inRangePeaks.empty() && *(filteredPeaks.end() - 1). - elementToAdd)
    }

    return filteredPeaks;
}

} // namespace calgopp::signal
