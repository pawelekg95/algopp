#pragma once

namespace calgopp::math {

/**
 * Epsilon number approximation.
 * @return Epsilon number.
 */
inline long double epsilon()
{
    return 0.0000001;
}

/**
 * Euler number approximation.
 * @return Euler number.
 */
inline long double euler()
{
    return 2.7182818284590452353602874713526624977572;
}

/**
 * PI number approximation.
 * @return PI number.
 */
inline long double pi()
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
    template <typename Floating>
    explicit Fraction(const Floating& num)
    {
        double integral = floor(num);
        double frac = num - integral;

        const int precision = 10000;

        int commonDivisor = gcd(int(round(frac * precision)), precision);

        m_denominator = precision / commonDivisor;
        m_numerator = int(round(frac * precision) / commonDivisor);
    }

    bool operator()() const { return m_denominator != 0 && m_numerator != 0; }

    bool operator!() const { return m_numerator == 0 || m_denominator == 0; }

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
        return power < 0 ? 1.0 / double(number) : double(number);
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
    Fraction pwrFraction(power);
    if (power < 0 && int(power) % 2 == 0 && !pwrFraction)
    {
        return pow(number, abs(power));
    }
    if (power < 0 && int(power) % 2 == 1 && !pwrFraction)
    {
        return -pow(number, abs(power));
    }
    auto basePwr = pow(number, int(floor(power)));
    auto fractionPwr = root(pow(number, pwrFraction.numerator()), pwrFraction.denominator());
    return basePwr * fractionPwr;
}

/**
 * Exponential function.
 * @tparam PowerType                            Power type.
 * @param power                                 Euler number power.
 * @return Calculated exponential.
 */
template <typename PowerType>
long double exp(const PowerType& power)
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
    return root(1 - pow(sin(num), 2), 2);
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
    return sin(num) / cos(num);
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

} // namespace calgopp::math
