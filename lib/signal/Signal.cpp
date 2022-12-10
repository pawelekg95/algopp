#include "calgopp/signal/Signal.h"
#include "calgopp/math/math.h"

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

types::Container<types::Peak> Signal::peaks(types::PeakType type, long double height, unsigned int distance)
{
    if (distance == 0)
    {
        throw "Invalid distance"; // NOLINT
    }
    auto isPeak = [&type](long double first, long double second, long double third) -> bool {
        return (type == types::PeakType::eLow ? first > second && second < third : first < second && second > third);
    };

    auto comparator = [&type](long double first, long double second) -> bool {
        return (type == types::PeakType::eLow ? first > second : first < second);
    };

    types::Container<types::Peak> peaks;
    auto endIt = end();
    auto currentIt = begin();
    while (currentIt <= endIt - 2)
    {
        currentIt++;
        if ((*currentIt).y < height)
        {
            continue;
        }
        if (!isPeak((*(currentIt - 1)).y, (*currentIt).y, (*(currentIt + 1)).y))
        {
            continue;
        }
        peaks.append(types::Peak((*currentIt).x, (*currentIt).y, type));
    }

    auto peaksLen = peaks.size();
    for (unsigned int i = 0; i < peaksLen - 1; i++)
    {
        if (m_points.index(types::Point(peaks[i + 1].x, peaks[i + 1].y)) -
                m_points.index(types::Point(peaks[i].x, peaks[i].y)) <
            distance)
        {
            peaks.remove(comparator(peaks[i].y, peaks[i + 1].y) ? i : i + 1);
            i--;
            peaksLen--;
        }
    }

    return peaks;
}

} // namespace calgopp::signal
