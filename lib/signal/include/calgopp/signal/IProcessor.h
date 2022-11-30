#pragma once

#include "calgopp/signal/Signal.h"

namespace calgopp::signal::process {

/**
 * Base class for any classes to process signal in any way
 */
class IProcessor
{
public:
    virtual ~IProcessor() = default;

    /**
     * Virtual pre-processing method.
     * @param signal                Input signal
     * @return Pre processed signal
     */
    virtual Signal preProcess(const Signal& signal)
    {
        (void) signal;
        return {};
    }

    /**
     * Virtual processing method
     * @param signal                Input signal
     * @return Processed signal
     */
    virtual Signal process(const Signal& signal) = 0;

    /**
     * Virtual post-processing method
     * @param signal                Input signal
     * @return  Post-processed signal
     */
    virtual Signal postProcess(const Signal& signal)
    {
        (void) signal;
        return {};
    }
};

} // namespace calgopp::signal::process
