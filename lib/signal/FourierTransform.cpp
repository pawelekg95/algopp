#include "calgopp/signal/transform/FourierTransform.h"
#include "calgopp/algorithm/algorithm.h"
#include "calgopp/math/math.h"

#include <iostream>

namespace calgopp::signal::transform {

Signal FourierTransform::process(const Signal& signal)
{
    signal::Signal token;
    auto N = signal.size();
    for (unsigned int k = 0; k < N; k++)
    {
        auto modifier = [&signal, k, N](types::Point element) -> types::Point {
            auto n = signal.index(element);
            auto xn = element.y;
            types::Complex token = xn * math::pow(math::euler(), types::Complex{0, (-2 * math::pi() * k * n) / N});
            return {0,  token};
        };
        token += algorithm::numeric::sum(signal.begin(), signal.end(), types::Point{signal.get(k).x, 0}, modifier);
        std::cout << (*(token.end() - 1)).y.real << " " << (*(token.end() - 1)).y.imag << std::endl;
    }
    return token;
}

} // namespace calgopp::signal::transform
