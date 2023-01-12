#pragma once

#include "calgopp/signal/Signal.h"
#include "calgopp/function/LinearFunction.h"

namespace calgopp {
namespace approximation {

function::LinearFunction leastSquares(const signal::Signal& signal);

} // namespace approximation
} // namespace calgopp
