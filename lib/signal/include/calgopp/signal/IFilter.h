#ifndef IFILTER_H
#define IFILTER_H

#include "calgopp/signal/Signal.h"

namespace calgopp::signal {

class IFilter
{
public:
    virtaul ~IFilter() = default;

    virtaul Signal filter(const Signal& signal) = 0;
};

} // namespace calgopp::signal

#endif /* IFILTER_H */
