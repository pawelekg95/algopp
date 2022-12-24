#pragma once

#include "calgopp/signal/IProcessor.h"

namespace calgopp::signal::transform {

/**
 * Implementation of discrete Fourier transform.
 */
class FourierTransform : public process::IProcessor
{
public:
    /**
     * Processing signal using Discrete Fourier transform
     * @param signal                    Input signal
     * @return Transformed signal
     */
    Signal process(const Signal& signal) override;
};

} // namespace calgopp::signal::transform
