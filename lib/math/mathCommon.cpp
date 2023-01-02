#include "calgopp/math/math.h"

namespace calgopp::math {

Fraction::Fraction(double num)
{
    double integral = floor(num);
    double frac = num - integral;

    const int precision = 10000;

    int commonDivisor = gcd(int(round(frac * precision)), precision);

    m_denominator = precision / commonDivisor;
    m_numerator = int(round(frac * precision) / commonDivisor);
}

} // namespace calgopp::math
