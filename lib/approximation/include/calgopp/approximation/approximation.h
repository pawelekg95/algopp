#pragma once

#include "calgopp/function/LinearFunction.h"
#include "calgopp/signal/Signal.h"

namespace calgopp {
namespace approximation {

function::LinearFunction leastSquares(signal::Signal& signal);

} // namespace approximation
} // namespace calgopp
