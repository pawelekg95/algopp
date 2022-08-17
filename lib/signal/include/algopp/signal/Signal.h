#ifndef SIGNAL_H
#define SIGNAL_H

#include "algopp/types/Point.h"
#include "algopp/types/Peak.h"

#include <vector>
#include <list>
#include <array>

namespace algopp::signal {

class Signal
{
public:
    Signal();

private:
    std::list<types::Point> m_points;
};

}

#endif /* SIGNAL_H */