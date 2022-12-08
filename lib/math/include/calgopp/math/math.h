#pragma once

#include <iostream>
#include <iomanip>

namespace calgopp::math {

/**
 * Epsilon constant for floating point comparisons
 */
inline long double epsilon()
{
    return 0.0000001;
}

/**
 * Euler number approximation
 * @return
 */
inline long double euler()
{
    return 2.7182818284590452353602874713526624977572;
}

/**
 * PI number approximation
 * @return
 */
inline long double pi()
{
    return 3.14159265358979323846;
}

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

/**
 * Returns integral part of the number.
 * @tparam Type                         Number type.
 * @param number                        Argument.
 * @return Integral part of the number.
 */
template <typename Type>
Type floor(const Type& number)
{
    return Type(int(number));
}

/**
 * Returns next integer to number.
 * @tparam Type
 * @param number
 * @return
 */
template <typename Type>
Type ceil(const Type& number)
{
    return Type(int(number + 1));
}

template <typename Type>
Type round(const Type& number)
{
    auto flr = floor(number);
    return number - flr < 0.5 ? flr : ceil(number);
}

class Fraction
{
public:
    template <typename Floating>
    explicit Fraction(const Floating& num)
    {
        double integral = floor(num);
        double frac = num - integral;

        const long precision = 100000; // This is the accuracy.

        long gcd_ = gcd(round(frac * precision), precision);

        m_denominator = precision / gcd_;
        m_numerator = round(frac * precision) / gcd_;
    }

    int numerator() { return m_numerator; }

    int denominator() { return m_denominator; }

private:
    long gcd(long a, long b)
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

private:
    int m_numerator{};
    int m_denominator{};
};

/**
 * Finds root of the number.
 * @tparam ArgumentType                 Number type.
 * @param number                        Number to find root.
 * @param root                          Root grade.
 * @return Approximation of root of the number with precision of epsilon().
 */
template <typename ArgumentType>
double root(ArgumentType number, unsigned int base)
{
    double precision = epsilon() / 10000.0;
    auto multiplication = [](double currentNumber, unsigned int base) {
        double token{currentNumber};
        for (unsigned int i = 1; i < base; i++)
        {
            token = token * currentNumber;
        }
        return token;
    };
    const double cMultiplier = 0.5;
    int maxSpins = 100000;

    auto increase =
        [&multiplication, &base, &precision, &maxSpins](double& token, const double& threshold, double& step) {
            while (multiplication(token, base) - threshold < precision)
            {
                if (maxSpins < 0)
                {
                    break;
                }
                token += step;
                maxSpins--;
            }
        };

    auto decrease =
        [&multiplication, &base, &precision, &maxSpins](double& token, const double& threshold, double& step) {
            while (multiplication(token, base) - threshold > precision)
            {
                if (maxSpins < 0)
                {
                    break;
                }
                token -= step;
                maxSpins--;
            }
        };

    double token = epsilon();
    double jump = cMultiplier * number;

    while (abs(multiplication(token, base) - number) > precision)
    {
        if (maxSpins < 0)
        {
            break;
        }
        auto multiplied = multiplication(token, base);
        if (multiplied - number > precision)
        {
            jump = jump * cMultiplier;
            decrease(token, number, jump);
        }
        else if (multiplied - number < precision)
        {
            jump = jump * cMultiplier;
            increase(token, number, jump);
        }
        maxSpins--;
    }
    return token;
}

/**
 * Calculates power of the number.
 * @tparam ArgumentType                         Number type.
 * @param number                                Argument.
 * @param power                                 Power.
 * @return Approximation of power of the provided number with precision of epsilon().
 */
template <typename ArgumentType>
long double pow(ArgumentType number, int power)
{
    unsigned int absPower = abs(power);
    if (power == 0)
    {
        return 1;
    }
    if (absPower == 1)
    {
        return power < 0 ? 1.0 / number : number;
    }
    long double token = number;
    while (absPower > 1)
    {
        token = token * double(number);
        absPower--;
    }

    return power < 0 ? 1.0 / token : token;
}

/**
 * Power for floating point powers.
 * @tparam ArgumentType                         Number type.
 * @tparam PowerType                            Power type.
 * @param number                                Number to power.
 * @param power                                 Power.
 * @return Approximation of power of the provided number with precision of epsilon().
 */
template <typename ArgumentType, typename PowerType>
long double pow(ArgumentType number, PowerType power)
{
    if (power < 0 && int(power) % 2 == 0)
    {
        return pow(number, abs(power));
    }
    if (power < 0 && int(power) % 2 == 1)
    {
        return -pow(number, abs(power));
    }
    auto basePwr = pow(number, int(floor(power)));
    Fraction pwrFraction(power);
    auto fractionPwr = root(pow(number, pwrFraction.numerator()), pwrFraction.denominator());
    return basePwr * fractionPwr;
}

/**
 * Exponential function.
 * @tparam PowerType
 * @param power
 * @return
 */
template <typename PowerType>
long double exp(const PowerType& power)
{
    return pow(euler(), power);
}

} // namespace calgopp::math
