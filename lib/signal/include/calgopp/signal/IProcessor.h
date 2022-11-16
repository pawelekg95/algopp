#pragma once

#include "calgopp/signal/Signal.h"

namespace calgopp::signal {

class IProcessor
{
public:
    virtual ~IProcessor() = default;

    virtual Signal preProcess(const Signal& signal)
    {
        (void) signal;
        return {};
    }

    virtual Signal process(const Signal& signal) = 0;

    virtual Signal postProcess(const Signal& signal)
    {
        (void) signal;
        return {};
    }
};

} // namespace calgopp::signal
