#include "calgopp/signal/Signal.h"

#include <cmath>

namespace calgopp::signal {

Signal::Signal(const types::Point* points, std::uint32_t size)
{
    for (std::uint32_t i = 0; i < size; i++)
    {
        m_points.push_back(points[i]);
    }
}

Signal::Signal(const types::Peak* peaks, std::uint32_t size)
    : m_points(static_cast<std::uint32_t>(size))
{
    for (std::uint32_t i = 0; i < size; i++)
    {
        m_points[i].x = peaks[i].x; // NOLINT
        m_points[i].y = peaks[i].y; // NOLINT
    }
}

void Signal::operator+=(const types::Point& point)
{
    append(point);
}

void Signal::operator--()
{
    m_points.erase(m_points.end() - 1);
}

void Signal::operator+=(Signal& signal)
{
    for (const auto& point : signal)
    {
        append(point);
    }
}

void Signal::append(const types::Point& point)
{
    m_points.push_back(point);
}

void Signal::remove(std::uint32_t index)
{
    m_points.erase(m_points.begin() + index);
}

types::Point& Signal::operator[](std::uint32_t index)
{
    if (index >= m_points.size())
    {
        throw "Index out of scope"; // NOLINT
    }
    return m_points.at(index);
}

etl::vector<types::Peak, MAX_SIGNAL_SIZE>
Signal::peaks(types::PeakType type, long double height, std::uint32_t distance)
{
    if (distance == 0)
    {
        throw "Invalid distance"; // NOLINT
    }
    if (empty())
    {
        return {};
    }
    auto isPeak = [type](long double first, long double second, long double third) -> bool {
        switch (type)
        {
            case types::PeakType::eLow:
            {
                return (first > second && second < third);
            }
            case types::PeakType::eHigh:
            {
                return (first < second && second > third);
            }
            default:
            {
                return false;
            }
        }
    };

    auto comparator = [&type](long double first, long double second) -> bool {
        return (type == types::PeakType::eLow ? first >= second : first <= second);
    };

    etl::vector<types::Peak, MAX_SIGNAL_SIZE> token;
    auto* endIt = end();
    auto* currentIt = begin();
    while (currentIt < endIt - 1)
    {
        currentIt++;
        if ((*currentIt).y < height)
        {
            continue;
        }
        if (!isPeak((currentIt - 1)->y, currentIt->y, (currentIt + 1)->y))
        {
            continue;
        }
        token.push_back(types::Peak(currentIt->x, currentIt->y, type));
    }

    auto peaksLen = token.size();
    if (peaksLen == 0 || distance == 1)
    {
        return token;
    }

    for (std::uint32_t i = 0; i < peaksLen - 1; i++)
    {
        if (index(types::Point(token[i + 1].x, token[i + 1].y)) - index(types::Point(token[i].x, token[i].y)) <
            distance)
        {
            token.erase(token.begin() + (comparator(token[i].y, token[i + 1].y) ? i : i + 1));
            i--;
            peaksLen--;
        }
    }

    return token;
}

types::Point Signal::get(std::uint32_t index) const
{
    return m_points.at(index);
}

std::uint32_t Signal::index(const types::Point& point) const
{
    return etl::find(m_points.begin(), m_points.end(), point) - m_points.begin();
}

} // namespace calgopp::signal
