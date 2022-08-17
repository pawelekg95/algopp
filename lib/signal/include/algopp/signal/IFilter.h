#ifndef IFILTER_H
#define IFILTER_H

#include "algopp/signal/Signal.h"

namespace algopp::signal {

class IFilter
{
public:
    virtaul ~IFilter() = default;

    virtaul Signal filter(const Signal& signal) = 0;
};

}

#endif /* IFILTER_H */