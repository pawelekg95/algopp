#include "calgopp/math/math.h"

namespace calgopp::math {

Fraction::Fraction(long double num)
{
    long double integral = floor(num);
    long double frac = num - integral;

    const int precision = 10000;

    int commonDivisor = gcd(int(round(frac * precision)), precision);

    m_denominator = precision / commonDivisor;
    m_numerator = int(round(frac * precision) / commonDivisor);
}

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

double root(int number, unsigned int base)
{
    return root(static_cast<double>(number), static_cast<int>(base));
}

double root(long int number, unsigned int base)
{
    return root(static_cast<double>(number), static_cast<int>(base));
}

double root(double number, unsigned int base)
{
    return root(static_cast<double>(number), static_cast<int>(base));
}

double root(int number, int base)
{
    return root(static_cast<double>(number), base);
}

double root(long int number, int base)
{
    return root(static_cast<double>(number), base);
}

double root(double number, int base)
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
    int maxSpins = 10000;

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

double pow(int number, unsigned int power)
{
    return pow(static_cast<double>(number), static_cast<int>(power));
}

double pow(long int number, unsigned int power)
{
    return pow(static_cast<double>(number), static_cast<int>(power));
}

double pow(double number, unsigned int power)
{
    return pow(number, static_cast<int>(power));
}

double pow(int number, int power)
{
    return pow(static_cast<double>(number), power);
}

double pow(long int number, int power)
{
    return pow(static_cast<double>(number), power);
}

double pow(double number, int power)
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
    double token = number;
    while (absPower > 1)
    {
        token = token * double(number);
        absPower--;
    }

    return power < 0 ? 1.0 / token : token;
}

double pow(int number, double power)
{
    return pow(static_cast<double>(number), power);
}

double pow(long int number, double power)
{
    return pow(static_cast<double>(number), power);
}

double pow(double number, double power)
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

} // namespace calgopp::math
