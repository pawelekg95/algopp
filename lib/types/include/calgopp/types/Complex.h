#pragma once

#include "calgopp/math/math.h"

namespace calgopp::types {

struct Complex
{
    Complex() = default;

    template <typename T>
    Complex(T real)
        : real(double(real))
    {}

    template <typename T>
    Complex(T real, T imag)
        : real(double(real))
        , imag(double(imag))
    {}

    template <typename T, typename Y>
    Complex(T real, Y imag)
        : real(double(real))
        , imag(double(imag))
    {}

    operator double() const { return real; }

    Complex& operator+=(const Complex& other);

    Complex& operator-=(const Complex& other);

    double real{};
    double imag{};
};

Complex operator+(const Complex& lhs, const Complex& rhs);

Complex operator-(const Complex& lhs, const Complex& rhs);

Complex operator*(const Complex& lhs, const Complex& rhs);

Complex operator/(const Complex& lhs, const Complex& rhs);

/**
 * Equality operator for lvalue reference.
 * @param lhs                       Left hand object.
 * @param rhs                       Right hand object.
 * @return True if complex numbers equal, false otherwise.
 */
bool operator==(const Complex& lhs, const Complex& rhs);

/**
 * Equality operator for rvalue reference.
 * @param lhs                       Left hand object.
 * @param rhs                       Right hand object.
 * @return True if complex numbers equal, false otherwise.
 */
bool operator==(const Complex&& lhs, const Complex&& rhs);

/**
 * Inequality operator for lvalue reference.
 * @param lhs                       Left hand object.
 * @param rhs                       Right hand object.
 * @return True if complex numbers are not equal, false otherwise.
 */
bool operator!=(const Complex& lhs, const Complex& rhs);

/**
 * Inequality operator for rvalue reference.
 * @param lhs                       Left hand object.
 * @param rhs                       Right hand object.
 * @return True if complex numbers are not equal, false otherwise.
 */
bool operator!=(const Complex&& lhs, const Complex&& rhs);

bool operator==(const Complex& complex, int number);

bool operator==(const Complex& complex, unsigned int number);

bool operator==(const Complex& complex, long double number);

bool operator!=(const Complex& complex, int number);

bool operator!=(const Complex& complex, unsigned int number);

bool operator!=(const Complex& complex, long double number);

bool operator==(const Complex&& complex, int number);

bool operator==(const Complex&& complex, unsigned int number);

bool operator==(const Complex&& complex, long double number);

bool operator!=(const Complex&& complex, int number);

bool operator!=(const Complex&& complex, unsigned int number);

bool operator!=(const Complex&& complex, long double number);

Complex operator*(const Complex& num1, const double& num2);

} // namespace calgopp::types

namespace calgopp::math {

template <typename T>
types::Complex pow(const T& number, const types::Complex& power)
{
    int multiplier = int(power.imag) % 2 == 1 || power.imag == 0 ? 1 : -1;
    return {multiplier * math::pow(number, power.real) * math::cos(power.imag * math::log(number)),
            math::pow(number, power.real) * math::sin(power.imag * math::log(number))};
}

} // namespace calgopp::math