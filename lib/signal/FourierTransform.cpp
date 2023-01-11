#include "calgopp/signal/transform/FourierTransform.h"
#include "calgopp/math/math.h"

namespace calgopp::signal::transform {

calgopp::types::Complex fourierSum(const calgopp::signal::Signal& signal, unsigned int k)
{
    double tokenReal = 0;
    double tokenImag = 0;
    auto N = signal.size();
    for (unsigned int n = 0; n < N; n++)
    {
        double arg = 2.0 * calgopp::math::pi() * k * n / N;
        double real = calgopp::math::cos(arg);
        double imag = -calgopp::math::sin(arg);
        auto elem = signal.get(n);
        tokenReal += elem.y.real * real + elem.y.imag * imag;
        tokenImag += elem.y.real * imag + elem.y.imag * real;
    }
    return {tokenReal, tokenImag};
}

Signal FourierTransform::process(const Signal& signal)
{
    signal::Signal token;
    for (unsigned int k = 0; k < signal.size(); k++)
    {
        token += {k, fourierSum(signal, k)};
    }
    return token;
}

} // namespace calgopp::signal::transform
