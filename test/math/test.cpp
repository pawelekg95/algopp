#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this
// in one cpp file
#include "calgopp/math/math.h"
#include "test/utils/helpers.h"

#include <catch2/catch_all.hpp>

#include <cmath>
#include <iostream>

#ifdef GPU_PARALLEL
const long double comparingThreshold = 0.01;
#else
const long double comparingThreshold = 0.0001;
#endif

class OverallTimerWatcher // NOLINT
{
public:
    ~OverallTimerWatcher() { std::cout << "Total time elapsed (us): " << m_overallWatcher << std::endl; }

    const OverallTimerWatcher& operator+=(std::uint64_t timer) const
    {
        m_overallWatcher += timer;
        std::cout << "Timer added (us): " << timer
                  << " from test case: " << Catch::getResultCapture().getCurrentTestName() << std::endl;
        return *this;
    }

private:
    mutable std::uint64_t m_overallWatcher{};
};

class TimerTracker // NOLINT
{
public:
    TimerTracker(const OverallTimerWatcher& overallTimerWatcher)
        : m_overallTimerWatcher(overallTimerWatcher)
    {
        m_timer.start();
    }

    ~TimerTracker() { m_overallTimerWatcher += m_timer.getElapsedMicroseconds(); }

private:
    const OverallTimerWatcher& m_overallTimerWatcher;
    Catch::Timer m_timer;
};

const OverallTimerWatcher overallTimer;

TEST_CASE("Absolute number")
{
#ifdef GPU_PARALLEL
    // Initialize GPU functions
    calgopp::math::pow(3.4, 2.5);
#endif
    TimerTracker tracker(overallTimer);
    REQUIRE(std::abs(-15) == calgopp::math::abs(-15));
    REQUIRE(std::abs(-15.4) == calgopp::math::abs(-15.4));
    REQUIRE(std::abs(15) == calgopp::math::abs(-15));
}

TEST_CASE("Root")
{
    TimerTracker tracker(overallTimer);
    REQUIRE(test::almostEqual(std::sqrt(100), calgopp::math::root(100, 2), comparingThreshold));
    REQUIRE(test::almostEqual(std::sqrt(64), calgopp::math::root(64, 2), comparingThreshold));
    REQUIRE(test::almostEqual(calgopp::math::root(27, 3), 3, comparingThreshold));
    REQUIRE(test::almostEqual(calgopp::math::root(3125, 5), 5, comparingThreshold));
    REQUIRE(test::almostEqual(calgopp::math::root(701583371424, 5), 234, comparingThreshold));
    REQUIRE(test::almostEqual(calgopp::math::root(61917364224, 10), 12, comparingThreshold));
    REQUIRE(test::almostEqual(calgopp::math::sqrt(100), std::sqrt(100)));
}

TEST_CASE("Floor and ceil")
{
    TimerTracker tracker(overallTimer);
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
    TimerTracker tracker(overallTimer);
    REQUIRE(std::round(1.14) == calgopp::math::round(1.14));
    REQUIRE(std::round(25.50) == calgopp::math::round(25.50));
    REQUIRE(std::round(90.9) == calgopp::math::round(90.9));
    REQUIRE(std::round(1.14) == calgopp::math::round(1.14));
}

TEST_CASE("Fraction")
{
    TimerTracker tracker(overallTimer);
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
    TimerTracker tracker(overallTimer);
    REQUIRE(test::almostEqual(std::pow(123143, 0), calgopp::math::pow(123143, 0), comparingThreshold));
    REQUIRE(test::almostEqual(std::pow(10, 5), calgopp::math::pow(10, 5), comparingThreshold));
    REQUIRE(test::almostEqual(std::pow(16, 3), calgopp::math::pow(16, 3), comparingThreshold));
    REQUIRE(test::almostEqual(std::pow(256.2, 2), calgopp::math::pow(256.2, 2), comparingThreshold));
    REQUIRE(test::almostEqual(std::pow(256.2, -2), calgopp::math::pow(256.2, -2), comparingThreshold));
    REQUIRE(test::almostEqual(std::pow(-12, 2), calgopp::math::pow(-12, 2), comparingThreshold));
    REQUIRE(test::almostEqual(std::pow(-12, 3), calgopp::math::pow(-12, 3), comparingThreshold));
    REQUIRE(test::almostEqual(std::pow(234, 6), calgopp::math::pow(234, 6), comparingThreshold * std::pow(234, 6)));

    REQUIRE(test::almostEqual(std::pow(10, 1.5), calgopp::math::pow(10, 1.5), comparingThreshold));
    REQUIRE(test::almostEqual(std::pow(10, 2.5), calgopp::math::pow(10, 2.5), comparingThreshold));
    REQUIRE(
        test::almostEqual(std::pow(234, 6.2), calgopp::math::pow(234, 6.2), comparingThreshold * std::pow(234, 6.2)));
    REQUIRE(test::almostEqual(std::pow(234, -6.2),
                              calgopp::math::pow(234, -6.2),
                              comparingThreshold * std::pow(234, -6.2)));
}

TEST_CASE("Exponential function")
{
    TimerTracker tracker(overallTimer);
    REQUIRE(test::almostEqual(std::exp(2), calgopp::math::exp(2), comparingThreshold));
    REQUIRE(test::almostEqual(std::exp(10), calgopp::math::exp(10), comparingThreshold));
    REQUIRE(test::almostEqual(std::exp(23.245), calgopp::math::exp(23.245), comparingThreshold * std::exp(23.245)));

#ifndef GPU_PARALLEL
    REQUIRE(test::almostEqual(std::exp(std::pow(6, 3)),
                              calgopp::math::exp(math::pow(6, 3)),
                              comparingThreshold * std::exp(std::pow(6, 3))));
    REQUIRE(test::almostEqual(std::exp(std::sin(60 * (M_PI / 180))),
                              calgopp::math::exp(math::sin(60 * (math::pi() / 180))),
                              comparingThreshold * std::exp(std::sin(60 * (M_PI / 180)))));
#endif
}

TEST_CASE("Trigonometry")
{
    TimerTracker tracker(overallTimer);
    REQUIRE(
        test::almostEqual(std::sin(60 * (M_PI / 180)), calgopp::math::sin(math::toRadians(60)), comparingThreshold));
    REQUIRE(
        test::almostEqual(std::cos(60 * (M_PI / 180)), calgopp::math::cos(math::toRadians(60)), comparingThreshold));
    REQUIRE(
        test::almostEqual(std::tan(60 * (M_PI / 180)), calgopp::math::tan(math::toRadians(60)), comparingThreshold));

    REQUIRE(
        test::almostEqual(std::sin(60 * (M_PI / 180)), calgopp::math::sin(math::toRadians(60)), comparingThreshold));
    REQUIRE(
        test::almostEqual(std::sin(120 * (M_PI / 180)), calgopp::math::sin(math::toRadians(120)), comparingThreshold));
    REQUIRE(
        test::almostEqual(std::sin(180 * (M_PI / 180)), calgopp::math::sin(math::toRadians(180)), comparingThreshold));
    REQUIRE(
        test::almostEqual(std::sin(270 * (M_PI / 180)), calgopp::math::sin(math::toRadians(270)), comparingThreshold));

    REQUIRE(
        test::almostEqual(std::sin(-60 * (M_PI / 180)), calgopp::math::sin(math::toRadians(-60)), comparingThreshold));
    REQUIRE(test::almostEqual(std::sin(-120 * (M_PI / 180)),
                              calgopp::math::sin(math::toRadians(-120)),
                              comparingThreshold));
    REQUIRE(test::almostEqual(std::sin(-180 * (M_PI / 180)),
                              calgopp::math::sin(math::toRadians(-180)),
                              comparingThreshold));
    REQUIRE(test::almostEqual(std::sin(-270 * (M_PI / 180)),
                              calgopp::math::sin(math::toRadians(-270)),
                              comparingThreshold));

    REQUIRE(
        test::almostEqual(std::cos(60 * (M_PI / 180)), calgopp::math::cos(math::toRadians(60)), comparingThreshold));
    REQUIRE(
        test::almostEqual(std::cos(120 * (M_PI / 180)), calgopp::math::cos(math::toRadians(120)), comparingThreshold));
    REQUIRE(
        test::almostEqual(std::cos(180 * (M_PI / 180)), calgopp::math::cos(math::toRadians(180)), comparingThreshold));
    REQUIRE(
        test::almostEqual(std::cos(270 * (M_PI / 180)), calgopp::math::cos(math::toRadians(270)), comparingThreshold));

    REQUIRE(
        test::almostEqual(std::cos(-60 * (M_PI / 180)), calgopp::math::cos(math::toRadians(-60)), comparingThreshold));
    REQUIRE(test::almostEqual(std::cos(-120 * (M_PI / 180)),
                              calgopp::math::cos(math::toRadians(-120)),
                              comparingThreshold));
    REQUIRE(test::almostEqual(std::cos(-180 * (M_PI / 180)),
                              calgopp::math::cos(math::toRadians(-180)),
                              comparingThreshold));
    REQUIRE(test::almostEqual(std::cos(-270 * (M_PI / 180)),
                              calgopp::math::cos(math::toRadians(-270)),
                              comparingThreshold));

    REQUIRE(
        test::almostEqual(std::tan(60 * (M_PI / 180)), calgopp::math::tan(math::toRadians(60)), comparingThreshold));
    REQUIRE(
        test::almostEqual(std::tan(120 * (M_PI / 180)), calgopp::math::tan(math::toRadians(120)), comparingThreshold));
    REQUIRE(
        test::almostEqual(std::tan(180 * (M_PI / 180)), calgopp::math::tan(math::toRadians(180)), comparingThreshold));

    REQUIRE(test::almostEqual(std::asin(1), calgopp::math::asin(1), comparingThreshold));
    REQUIRE(test::almostEqual(std::asin(0.8), calgopp::math::asin(0.8), comparingThreshold));
    REQUIRE(test::almostEqual(std::asin(0.6), calgopp::math::asin(0.6), comparingThreshold));
    REQUIRE(test::almostEqual(std::asin(-1), calgopp::math::asin(-1), comparingThreshold));
    REQUIRE(test::almostEqual(std::asin(-0.8), calgopp::math::asin(-0.8), comparingThreshold));
    REQUIRE(test::almostEqual(std::asin(-0.6), calgopp::math::asin(-0.6), comparingThreshold));

    REQUIRE(test::almostEqual(std::acos(1), calgopp::math::acos(1), comparingThreshold));
    REQUIRE(test::almostEqual(std::acos(0.8), calgopp::math::acos(0.8), comparingThreshold));
    REQUIRE(test::almostEqual(std::acos(0.6), calgopp::math::acos(0.6), comparingThreshold));
    REQUIRE(test::almostEqual(std::acos(-1), calgopp::math::acos(-1), comparingThreshold));
    REQUIRE(test::almostEqual(std::acos(-0.8), calgopp::math::acos(-0.8), comparingThreshold));
    REQUIRE(test::almostEqual(std::acos(-0.6), calgopp::math::acos(-0.6), comparingThreshold));

    REQUIRE(test::almostEqual(std::atan(1), calgopp::math::atan(1), comparingThreshold));
    REQUIRE(test::almostEqual(std::atan(0.8), calgopp::math::atan(0.8), comparingThreshold));
    REQUIRE(test::almostEqual(std::atan(0.6), calgopp::math::atan(0.6), comparingThreshold));
    REQUIRE(test::almostEqual(std::atan(-1), calgopp::math::atan(-1), comparingThreshold));
    REQUIRE(test::almostEqual(std::atan(-0.8), calgopp::math::atan(-0.8), comparingThreshold));
    REQUIRE(test::almostEqual(std::atan(-0.6), calgopp::math::atan(-0.6), comparingThreshold));
    REQUIRE(test::almostEqual(std::atan(2), calgopp::math::atan(2), comparingThreshold));
    REQUIRE(test::almostEqual(std::atan(3), calgopp::math::atan(3), comparingThreshold));
    REQUIRE(test::almostEqual(std::atan(-2), calgopp::math::atan(-2), comparingThreshold));
    REQUIRE(test::almostEqual(std::atan(-3), calgopp::math::atan(-3), comparingThreshold));
}

TEST_CASE("Benchmark test")
{
    TimerTracker tracker(overallTimer);
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

TEST_CASE("Logarithms")
{
    TimerTracker tracker(overallTimer);
    REQUIRE(test::almostEqual(std::log(10), calgopp::math::log(10), comparingThreshold));
    REQUIRE(test::almostEqual(std::log(2), calgopp::math::log(2), comparingThreshold));
    REQUIRE(test::almostEqual(std::log(1.5), calgopp::math::log(1.5), comparingThreshold));
    REQUIRE(test::almostEqual(std::log(12), calgopp::math::log(12), comparingThreshold));
    REQUIRE(test::almostEqual(std::log(12.78), calgopp::math::log(12.78), comparingThreshold));
}
