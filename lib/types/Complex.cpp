#include "calgopp/types/Complex.h"
#include "calgopp/math/math.h"

namespace calgopp::types {

Complex& Complex::operator+=(const Complex& other)
{
    this->real += other.real;
    this->imag += other.imag;
    return *this;
}

Complex& Complex::operator-=(const Complex& other)
{
    this->imag -= other.imag;
    this->real -= other.real;
    return *this;
}

bool operator==(const Complex& lhs, const Complex& rhs)
{
    return math::abs(lhs.imag - rhs.imag) < math::epsilon() && math::abs(lhs.real - rhs.real) < math::epsilon();
}

bool operator==(const Complex&& lhs, const Complex&& rhs)
{
    return math::abs(lhs.imag - rhs.imag) < math::epsilon() && math::abs(lhs.real - rhs.real) < math::epsilon();
}

bool operator!=(const Complex& lhs, const Complex& rhs)
{
    return !(lhs == rhs);
}

bool operator!=(const Complex&& lhs, const Complex&& rhs)
{
    return !(lhs == rhs);
}

Complex operator+(const Complex& lhs, const Complex& rhs)
{
    return {lhs.real + rhs.real, lhs.imag + rhs.imag};
}

Complex operator-(const Complex& lhs, const Complex& rhs)
{
    return {lhs.real - rhs.real, lhs.imag - rhs.imag};
}

Complex operator*(const Complex& lhs, const Complex& rhs)
{
    return {lhs.real * rhs.real - lhs.imag * rhs.imag, lhs.real * rhs.imag + lhs.imag * rhs.real};
}

Complex operator/(const Complex& lhs, const Complex& rhs)
{
    return {(lhs.real * rhs.real + lhs.imag + rhs.imag) / (math::pow(rhs.real, 2) + math::pow(rhs.imag, 2)),
            (lhs.imag * rhs.real - lhs.real * rhs.imag) / (math::pow(rhs.real, 2) + math::pow(rhs.imag, 2))};
}

bool operator==(const Complex& complex, int number)
{
    return math::abs(complex.real - number) < math::epsilon();
}

bool operator==(const Complex& complex, unsigned int number)
{
    return math::abs(complex.real - number) < math::epsilon();
}

bool operator==(const Complex& complex, long double number)
{
    return math::abs(complex.real - number) < math::epsilon();
}

bool operator!=(const Complex& complex, int number)
{
    return !(complex == number);
}

bool operator!=(const Complex& complex, unsigned int number)
{
    return !(complex == number);
}

bool operator!=(const Complex& complex, long double number)
{
    return !(complex == number);
}

bool operator==(const Complex&& complex, int number)
{
    return math::abs(complex.real - number) < math::epsilon();
}

bool operator==(const Complex&& complex, unsigned int number)
{
    return math::abs(complex.real - number) < math::epsilon();
}

bool operator==(const Complex&& complex, long double number)
{
    return math::abs(complex.real - number) < math::epsilon();
}

bool operator!=(const Complex&& complex, int number)
{
    return !(complex == number);
}

bool operator!=(const Complex&& complex, unsigned int number)
{
    return !(complex == number);
}

bool operator!=(const Complex&& complex, long double number)
{
    return !(complex == number);
}

} // namespace calgopp::types

namespace calgopp::math {

double abs(const types::Complex& number)
{
    return root(pow(number.real, 2) + pow(number.imag, 2), 2);
}

types::Complex pow(const types::Complex& number, unsigned int power)
{
    if (power == 0)
    {
        return {1, 0};
    }
    types::Complex token{number};
    while (power-- > 1)
    {
        token = token * number;
    }
    return token;
}

types::Complex pow(const types::Complex& number, int power)
{
    unsigned int absPower = abs(power);
    return power > 0 ? pow(number, absPower) : 1.0 / pow(number, absPower);
}

}
