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

double root(int number, int base)
{
    return root((long double)(number), (unsigned int)(base));
}

double root(long int number, int base)
{
    return root((long double)(number), (unsigned int)(base));
}

double root(long long int number, int base)
{
    return root((long double)(number), (unsigned int)(base));
}

double root(int number, unsigned int base)
{
    return root((long double)(number), base);
}

double root(long int number, unsigned int base)
{
    return root((long double)(number), base);
}

double root(long long int number, unsigned int base)
{
    return root((long double)(number), base);
}


double root(double number, int base)
{
    return root((long double)(number), (unsigned int)(base));
}

double root(long double number, int base)
{
    return root(number, (unsigned int)(base));
}

double root(double number, unsigned int base)
{
    return root((long double)(number), base);
}

double root(long double number, unsigned int base)
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

} // namespace calgopp::math
