#pragma once

#include "calgopp/signal/IProcessor.h"

namespace calgopp::signal::transform {

/**
 * Implementation of prof. Michał Jacymirski transform
 */
class JacymirskiTransform : public process::IProcessor
{
public:
    /**
     * Processing signal using Jacymirski's transform
     * @param signal                    Input signal
     * @return Transformed signal
     */
    Signal process(const Signal& signal) override;
};

} // namespace calgopp::signal::transform
