#pragma once

#include <cmath>

namespace calgopp::types {

struct Complex
{
    Complex() = default;

    Complex(const Complex& other) = default;

    Complex(Complex&& other) noexcept = default;

    Complex& operator=(const Complex& other) = default;

    Complex& operator=(Complex&& other) noexcept = default;

    template <typename T>
    Complex(T real)
        : real(real)
    {
    }

    template <typename T>
    Complex(T real, T imag)
        : real(real)
        , imag(imag)
    {
    }

    template <typename T, typename Y>
    Complex(T real, Y imag)
        : real(real)
        , imag(imag)
    {
    }

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

template <typename T>
Complex operator*(const types::Complex& num1, const T& num2)
{
    return {num1.real * num2, num1.imag * num2};
}

template <typename T>
Complex operator*(const T& num1, const Complex& num2)
{
    return {num1 * num2.real, num1 * num2.imag};
}

template <typename T>
Complex operator/(const T& num1, const Complex& num2)
{
    return {num1 / num2.real, num1 / num2.imag};
}

template <typename T>
Complex operator/(const Complex& num1, const T& num2)
{
    return {num1.real / num2, num1.imag / num2};
}

} // namespace calgopp::types

namespace calgopp::math {

double abs(const types::Complex& number);

template <typename T>
types::Complex pow(const T& number, const types::Complex& power)
{
    auto pwr = math::pow(number, power.real);
    return {pwr * std::cos(power.imag * std::log(number)), pwr * std::sin(power.imag * std::log(number))};
}

types::Complex pow(const types::Complex& number, unsigned int power);

types::Complex pow(const types::Complex& number, int power);

} // namespace calgopp::math