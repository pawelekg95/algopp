#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this
// in one cpp file
#include "test/utils/helpers.h"

#include <catch2/catch_all.hpp>

#include "calgopp/math/math.h"

#include <cmath>

TEST_CASE("Absolute number")
{
    REQUIRE(std::abs(-15) == calgopp::math::abs(-15));
    REQUIRE(std::abs(-15.4) == calgopp::math::abs(-15.4));
    REQUIRE(std::abs(15) == calgopp::math::abs(-15));
}

TEST_CASE("Root")
{
    REQUIRE(test::almostEqual(std::sqrt(100), calgopp::math::root(100, 2)));
    REQUIRE(test::almostEqual(std::sqrt(64), calgopp::math::root(64, 2)));
    REQUIRE(test::almostEqual(calgopp::math::root(27, 3), 3));
    REQUIRE(test::almostEqual(calgopp::math::root(3125, 5), 5));
    REQUIRE(test::almostEqual(calgopp::math::root(701583371424, 5), 234));
    REQUIRE(test::almostEqual(calgopp::math::root(61917364224, 10), 12));
}

TEST_CASE("Floor and ceil")
{
    REQUIRE(std::floor(1.14) == calgopp::math::floor(1.14));
    REQUIRE(std::floor(25.50) == calgopp::math::floor(25.50));
    REQUIRE(std::floor(90.9) == calgopp::math::floor(90.9));
    REQUIRE(std::floor(1.14) == calgopp::math::floor(1.14));

    REQUIRE(std::ceil(1.14) == calgopp::math::ceil(1.14));
    REQUIRE(std::ceil(25.50) == calgopp::math::ceil(25.50));
    REQUIRE(std::ceil(90.9) == calgopp::math::ceil(90.9));
    REQUIRE(std::ceil(1.14) == calgopp::math::ceil(1.14));

    REQUIRE(std::floor(-1.14) == calgopp::math::floor(-1.14));
    REQUIRE(std::floor(-25.50) == calgopp::math::floor(-25.50));
    REQUIRE(std::floor(-90.9) == calgopp::math::floor(-90.9));
    REQUIRE(std::floor(-1.14) == calgopp::math::floor(-1.14));

    REQUIRE(std::ceil(-1.14) == calgopp::math::ceil(-1.14));
    REQUIRE(std::ceil(-25.50) == calgopp::math::ceil(-25.50));
    REQUIRE(std::ceil(-90.9) == calgopp::math::ceil(-90.9));
    REQUIRE(std::ceil(-1.14) == calgopp::math::ceil(-1.14));

    REQUIRE(std::ceil(25.0) == calgopp::math::ceil(25.0));
    REQUIRE(std::floor(25.0) == calgopp::math::floor(25.0));
}

TEST_CASE("Round")
{
    REQUIRE(std::round(1.14) == calgopp::math::round(1.14));
    REQUIRE(std::round(25.50) == calgopp::math::round(25.50));
    REQUIRE(std::round(90.9) == calgopp::math::round(90.9));
    REQUIRE(std::round(1.14) == calgopp::math::round(1.14));
}

TEST_CASE("Fraction")
{
    REQUIRE(calgopp::math::Fraction(0.5).numerator() == 1);
    REQUIRE(calgopp::math::Fraction(0.5).denominator() == 2);

    REQUIRE(calgopp::math::Fraction(1.5).numerator() == 1);
    REQUIRE(calgopp::math::Fraction(1.5).denominator() == 2);

    REQUIRE(calgopp::math::Fraction(0.2).numerator() == 1);
    REQUIRE(calgopp::math::Fraction(0.2).denominator() == 5);

    REQUIRE(calgopp::math::Fraction(0.25).numerator() == 1);
    REQUIRE(calgopp::math::Fraction(0.25).denominator() == 4);

    REQUIRE(calgopp::math::Fraction(0.33).numerator() == 33);
    REQUIRE(calgopp::math::Fraction(0.33).denominator() == 100);

    REQUIRE(calgopp::math::Fraction(0.125).numerator() == 1);
    REQUIRE(calgopp::math::Fraction(0.125).denominator() == 8);

    REQUIRE(calgopp::math::Fraction(0.375).numerator() == 3);
    REQUIRE(calgopp::math::Fraction(0.375).denominator() == 8);
}

TEST_CASE("Power")
{
    REQUIRE(test::almostEqual(std::pow(123143, 0), calgopp::math::pow(123143, 0)));
    REQUIRE(test::almostEqual(std::pow(10, 5), calgopp::math::pow(10, 5)));
    REQUIRE(test::almostEqual(std::pow(16, 3), calgopp::math::pow(16, 3)));
    REQUIRE(test::almostEqual(std::pow(256.2, 2), calgopp::math::pow(256.2, 2)));
    REQUIRE(test::almostEqual(std::pow(256.2, -2), calgopp::math::pow(256.2, -2)));
    REQUIRE(test::almostEqual(std::pow(-12, 2), calgopp::math::pow(-12, 2)));
    REQUIRE(test::almostEqual(std::pow(-12, 3), calgopp::math::pow(-12, 3)));
    REQUIRE(test::almostEqual(std::pow(234, 6), calgopp::math::pow(234, 6)));

    REQUIRE(test::almostEqual(std::pow(10, 1.5), calgopp::math::pow(10, 1.5)));
    REQUIRE(test::almostEqual(std::pow(10, 2.5), calgopp::math::pow(10, 2.5)));
    REQUIRE(test::almostEqual(std::pow(234, 6.2), calgopp::math::pow(234, 6.2)));
    REQUIRE(test::almostEqual(std::pow(234, -6.2), calgopp::math::pow(234, -6.2)));
}

TEST_CASE("Exponential function")
{
    REQUIRE(test::almostEqual(std::exp(2), calgopp::math::exp(2)));
    REQUIRE(test::almostEqual(std::exp(10), calgopp::math::exp(10)));
    REQUIRE(test::almostEqual(std::exp(23.245), calgopp::math::exp(23.245)));
    REQUIRE(test::almostEqual(std::exp(std::pow(6, 3)), calgopp::math::exp(math::pow(6, 3))));
    REQUIRE(test::almostEqual(std::exp(std::sin(60 * (M_PI / 180))),
                              calgopp::math::exp(math::sin(60 * (math::pi() / 180))),
                              0.0001));
}

TEST_CASE("Trigonometry")
{
    REQUIRE(test::almostEqual(std::sin(60 * (M_PI / 180)), calgopp::math::sin(60 * (calgopp::math::pi() / 180))));
    REQUIRE(test::almostEqual(std::cos(60 * (M_PI / 180)), calgopp::math::cos(60 * (calgopp::math::pi() / 180))));
    REQUIRE(test::almostEqual(std::tan(60 * (M_PI / 180)), calgopp::math::tan(60 * (calgopp::math::pi() / 180))));
}

TEST_CASE("Benchmark test")
{
    const float cThresholdMultiplier = 1.0;
    CHECK(cThresholdMultiplier * test::benchmark([]() { std::sqrt(100); }) >=
          test::benchmark([]() { calgopp::math::root(100, 2); }));
    CHECK(cThresholdMultiplier * test::benchmark([]() { std::sqrt(64); }) >=
          test::benchmark([]() { calgopp::math::root(64, 2); }));

    CHECK(cThresholdMultiplier * test::benchmark([]() { std::pow(123143, 0); }) >=
          test::benchmark([]() { calgopp::math::pow(123143, 0); }));
    CHECK(cThresholdMultiplier * test::benchmark([]() { std::pow(10, 5); }) >=
          test::benchmark([]() { calgopp::math::pow(10, 5); }));
    CHECK(cThresholdMultiplier * test::benchmark([]() { std::pow(16, 3); }) >=
          test::benchmark([]() { calgopp::math::pow(16, 3); }));
    CHECK(cThresholdMultiplier * test::benchmark([]() { std::pow(256.2, 2); }) >=
          test::benchmark([]() { calgopp::math::pow(256.2, 2); }));
    CHECK(cThresholdMultiplier * test::benchmark([]() { std::pow(-12, 2); }) >=
          test::benchmark([]() { calgopp::math::pow(-12, 2); }));
    CHECK(cThresholdMultiplier * test::benchmark([]() { std::pow(-12, 3); }) >=
          test::benchmark([]() { calgopp::math::pow(-12, 3); }));
}
