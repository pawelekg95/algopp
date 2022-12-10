#include "calgopp/math/math.h"

namespace calgopp::math {

int gcd(int a, int b)
{
    if (a == 0)
    {
        return b;
    }
    if (b == 0)
    {
        return a;
    }
    return a < b ? gcd(a, b % a) : gcd(b, a % b);
}

} // namespace calgopp::math
