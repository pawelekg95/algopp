#ifndef SIGNAL_H
#define SIGNAL_H

#include "algopp/types/Point.h"
#include "algopp/types/Peak.h"

#include <vector>
#include <list>
#include <array>
#include <cstdint>
#include <limits>

namespace algopp::signal {

class Signal
{
public:
    Signal();

    types::Peak peaks(types::PeakType type = types::PeakType::eHigh, long double distance = 0, long double height = std::numeric_limits<long double>::min());

    std::list<types::Point> points() { return m_points; }

private:
    std::list<types::Point> m_points;
};

}

#endif /* SIGNAL_H */