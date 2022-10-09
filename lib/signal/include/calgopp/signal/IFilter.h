#pragma once

#include "calgopp/signal/Signal.h"

namespace calgopp::signal {

class IFilter
{
public:
    virtaul ~IFilter() = default;

    virtaul Signal filter(const Signal& signal) = 0;
};

} // namespace calgopp::signal
