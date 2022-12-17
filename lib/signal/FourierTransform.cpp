#include "calgopp/signal/transform/FourierTransform.h"
#include "calgopp/algorithm/algorithm.h"
#include "calgopp/math/math.h"

#include <iostream>

namespace calgopp::signal::transform {

Signal FourierTransform::process(const Signal& signal)
{
    signal::Signal token;
    auto N = signal.size(); // NOLINT
    unsigned int k{};
    auto modifier = [&k, &N, &signal](const types::Point& element) -> types::Point {
        auto n = signal.index(element);
        auto arg = -2.0 * math::pi() * k * n / N;
        auto power = math::pow(math::euler(), types::Complex{0, arg});
        return {0, element.y * power};
    };
    for (k = 0; k < N; k++)
    {
        token += algorithm::numeric::sum(signal.begin(), signal.end(), types::Point{signal.get(k).x, 0.0}, modifier);
    }
    return token;
}

} // namespace calgopp::signal::transform
