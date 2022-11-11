#pragma once

#include "Signal.h"

#include <stdint.h>
#include <stdlib.h>

namespace calgopp::signal::factory {

template <typename Container>
Signal fromContainer(const Container& container)
{
    return Signal(container.data(), container.size());
}

} // namespace calgopp::signal::factory
