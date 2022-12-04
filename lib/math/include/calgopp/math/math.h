#pragma once

namespace calgopp::math {

/**
 * Epsilon constant for floating point comparisons
 */
const long double cEpsilon = 0.0000000001;

/**
 * Absolute operator
 * @tparam Type                         Number type
 * @param number                        Argument
 * @return Absolute value of argument
 */
template <typename Type>
Type abs(const Type& number)
{
    return number < 0 ? -number : number;
}

template <typename Type>
double pow(const Type& number, int power)
{

}

} // namespace calgopp::math
