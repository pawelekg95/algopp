#pragma once

#include "calgopp/signal/IProcessor.h"

namespace calgopp::signal::transform {

class Jacymirski : public process::IProcessor
{
public:
    Signal process(const Signal& signal) override;
};

} // namespace calgopp::signal::transform
