#pragma once

namespace calgopp {
namespace math {

inline double toRadians(double degrees)
{
    return degrees / 57.29577951;
}

inline double toDegrees(double radians)
{
    return radians * 57.29577951;
}

/**
 * Epsilon number approximation.
 * @return Epsilon number.
 */
inline double epsilon()
{
    return 0.0000000000000000000001;
}

/**
 * Euler number approximation.
 * @return Euler number.
 */
inline double euler()
{
    return 2.7182818284590452353602874713526624977572;
}

/**
 * PI number approximation.
 * @return PI number.
 */
inline double pi()
{
    return 3.14159265358979323846;
}

/**
 * Absolute operator.
 * @tparam Type                         Number type.
 * @param number                        Argument.
 * @return Absolute value of argument.
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
    return number < 0 ? -floor(abs(number - 1)) : int(number);
}

/**
 * Returns next integer to number.
 * @tparam Type                         Number type.
 * @param number                        Argument.
 * @return Next integer after number.
 */
template <typename Type>
Type ceil(const Type& number)
{
    if (int(number) == number)
    {
        return number;
    }
    return number < 0 ? -ceil(abs(number + 1)) : int(number + 1);
}

/**
 * Rounds number to either ceil or floor if floating point part is <0.5.
 * @tparam Type                         Number type.
 * @param number                        Argument.
 * @return Nearest integer.
 */
template <typename Type>
Type round(const Type& number)
{
    auto flr = floor(number);
    return number - flr < 0.5 ? flr : ceil(number);
}

/**
 * Calculates greatest common divisor of provided numbers.
 * @param a                             First number.
 * @param b                             Second number.
 * @return Greates common divisor.
 */
int gcd(int a, int b);

/**
 * Fraction.
 * Stores fraction of the number as numerator and denominator.
 */
class Fraction
{
public:
    /**
     * Template constructor. Allows to store fraction of any floating type number.
     * @tparam Floating                 Floating number type.
     * @param num                       Number to get fraction.
     */

    Fraction(long double num);

    bool operator()() const { return m_denominator != 0 || m_numerator != 0; }

    bool operator!() const { return m_numerator == 0 && m_denominator == 0; }

    /**
     * Numerator getter.
     * @return Fraction numerator.
     */
    int numerator() const { return m_numerator; }

    /**
     * Denominator getter.
     * @return Fraction denominator.
     */
    int denominator() const { return m_denominator; }

private:
    int m_numerator{};
    int m_denominator{};
};

double root(int number, unsigned int base);

double root(long int number, unsigned int base); // NOLINT

double root(double number, unsigned int base);

double root(int number, int base);

double root(long int number, int base); // NOLINT

double root(double number, int base);

double pow(int number, unsigned int power);

double pow(long int number, unsigned int power); // NOLINT

double pow(double number, unsigned int power);

double pow(int number, int power);

double pow(long int number, int power); // NOLINT

double pow(double number, int power);

double pow(int number, double power);

double pow(long int number, double power); // NOLINT

double pow(double number, double power);

/**
 * Exponential function.
 * @tparam PowerType                            Power type.
 * @param power                                 Euler number power.
 * @return Calculated exponential.
 */
template <typename PowerType>
double exp(const PowerType& power)
{
    return pow(euler(), power);
}

/**
 * Sine function. Calculates sine for argument.
 * @tparam Number
 * @param num
 * @return
 */
template <typename Number>
double sin(const Number& num)
{
    double t = num;
    double sine = t;
    for (int a = 1; a < 20; ++a)
    {
        double mult = -num * num / ((2 * a + 1) * (2 * a));
        t *= mult;
        sine += t;
    }
    return sine;
}

/**
 * Cosine function.
 * @tparam Number
 * @param num
 * @return
 */
template <typename Number>
double cos(const Number& num)
{
    auto shouldBePositive = [num]() -> bool {
        auto degrees = abs(toDegrees(num));
        while (degrees > 360)
        {
            degrees -= 360;
        }
        return (degrees >= 0 && degrees <= 90) || (degrees >= 270 && degrees <= 360);
    };
    auto result = root(1 - pow(sin(num), 2), 2);
    return shouldBePositive() ? result : -result;
}

/**
 * Tangent function.
 * @tparam Number
 * @param num
 * @return
 */
template <typename Number>
double tan(const Number& num)
{
    auto shouldBePositive = [num]() -> bool {
        auto degrees = abs(toDegrees(num));
        while (degrees > 360)
        {
            degrees -= 360;
        }
        return (degrees >= 0 && degrees <= 90) || (degrees > 180 && degrees <= 270);
    };
    auto result = abs(sin(num) / cos(num));
    return shouldBePositive() ? result : -result;
}

template <typename T>
long double log(const T& argument)
{
    long double token{};
    auto base = double(argument - 1) / double(argument + 1);
    for (unsigned int i = 1; i < 200; i += 2)
    {
        token += (1.0 / double(i)) * pow(base, i);
    }
    return 2 * token;
}

} // namespace math
} // namespace calgopp
