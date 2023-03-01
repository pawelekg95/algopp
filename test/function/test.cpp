#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this
// in one cpp file
#include "calgopp/function/Function.h"
#include "calgopp/function/LinearFunction.h"
#include "test/utils/helpers.h"

#include <catch2/catch_all.hpp>

#include <cmath>

const long double comparingThreshold = 0.0001;

struct Sine
{
    double operator()(double argument) { return std::sin(argument); }
};

struct Cosine
{
    double operator()(double argument) { return std::cos(argument); }
};

TEST_CASE("Trigonometry functions")
{
    Sine sine;
    calgopp::function::Function<Sine> sineFunction(sine);

    REQUIRE(double(sineFunction(60.0)) == std::sin(60.0));
    REQUIRE(double(sineFunction(60.0)) != std::cos(60.0));

    Cosine cosine;
    calgopp::function::Function<Cosine> cosineFunction(cosine);
    REQUIRE(double(cosineFunction(60.0)) == std::cos(60.0));
    REQUIRE(double(cosineFunction(60.0)) != std::sin(60.0));

    calgopp::function::Function<double (*)(double)> mathSinFunction(std::sin);
    REQUIRE(double(mathSinFunction(60.0)) == std::sin(60.0));
    REQUIRE(double(mathSinFunction(60.0)) != std::cos(60.0));

    auto sinLambda = [](double argument) -> double { return std::sin(argument); };
    calgopp::function::Function<double (*)(double)> lambdaFunction(sinLambda);
    REQUIRE(double(lambdaFunction(60.0)) == std::sin(60.0));
    REQUIRE(double(lambdaFunction(60.0)) != std::cos(60.0));

    calgopp::function::Function<double (*)(double)> calgoppMathSinFunction(calgopp::math::sin);
    REQUIRE(test::almostEqual(double(calgoppMathSinFunction(calgopp::math::toRadians(60.0))),
                              std::sin(calgopp::math::toRadians(60.0))));
    REQUIRE(double(calgoppMathSinFunction(calgopp::math::toRadians(60.0))) != std::cos(calgopp::math::toRadians(60.0)));
}

TEST_CASE("Linear function")
{
    calgopp::function::LinearFunction linearFunction(1, 0);
    REQUIRE(double(linearFunction(100)) == 100);
    REQUIRE(double(linearFunction(54)) == 54);
    REQUIRE(test::almostEqual(linearFunction.slope(), calgopp::math::toRadians(45), comparingThreshold));

    linearFunction = calgopp::function::LinearFunction(2, 0);
    REQUIRE(double(linearFunction(100)) == 200);
    REQUIRE(double(linearFunction(54)) == 108);
    REQUIRE(test::almostEqual(linearFunction.slope(), calgopp::math::toRadians(63.43), comparingThreshold));

    linearFunction = calgopp::function::LinearFunction(2, 5);
    REQUIRE(double(linearFunction(100)) == 205);
    REQUIRE(double(linearFunction(54)) == 113);
    REQUIRE(test::almostEqual(linearFunction.slope(), calgopp::math::toRadians(63.43), comparingThreshold));

    linearFunction = calgopp::function::LinearFunction(4.5, 1);
    REQUIRE(double(linearFunction(100)) == 451);
    REQUIRE(double(linearFunction(54)) == 244);
    REQUIRE(test::almostEqual(calgopp::math::toDegrees(linearFunction.slope()), 77.47, comparingThreshold));

    linearFunction = calgopp::function::LinearFunction(-2, 0);
    REQUIRE(double(linearFunction(100)) == -200);
    REQUIRE(double(linearFunction(54)) == -108);
    REQUIRE(test::almostEqual(linearFunction.slope(), calgopp::math::toRadians(-63.43), comparingThreshold));
}

TEST_CASE("Angles")
{
    calgopp::function::LinearFunction linearFunction1(3, 0);
    calgopp::function::LinearFunction linearFunction2((1.0 / 3.0), 0);
    REQUIRE(test::almostEqual(linearFunction1.angle(linearFunction2), calgopp::math::toRadians(90)));

    linearFunction1 = calgopp::function::LinearFunction(3, 0);
    linearFunction2 = calgopp::function::LinearFunction(3, 100);
    REQUIRE(test::almostEqual(linearFunction1.angle(linearFunction2), calgopp::math::toRadians(0)));
}
