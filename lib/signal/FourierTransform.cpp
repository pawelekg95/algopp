#include "calgopp/signal/transform/FourierTransform.h"

#include <cmath>
#include <cstdint>

namespace calgopp::signal::transform {

calgopp::types::Complex fourierSum(const calgopp::signal::Signal& signal, std::uint32_t k)
{
    double tokenReal = 0;
    double tokenImag = 0;
    auto n = signal.size();
    for (std::uint32_t i = 0; i < n; i++)
    {
        double arg = 2.0 * M_PI * k * i / n;
        double real = std::cos(arg);
        double imag = -std::sin(arg);
        auto elem = signal.get(i);
        tokenReal += elem.y.real * real + elem.y.imag * imag;
        tokenImag += elem.y.real * imag + elem.y.imag * real;
    }
    return {tokenReal, tokenImag};
}

Signal FourierTransform::process(const Signal& signal)
{
    signal::Signal token;
    for (std::uint32_t k = 0; k < signal.size(); k++)
    {
        token += {k, fourierSum(signal, k)};
    }
    return token;
}

} // namespace calgopp::signal::transform
