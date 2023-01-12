#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this
// in one cpp file
#include "test/utils/helpers.h"

#include <catch2/catch_all.hpp>

#include "calgopp/function/Function.h"
#include "calgopp/function/LinearFunction.h"

#include <cmath>

struct Sine
{
    double operator()(double argument) { return sin(argument); }
};

struct Cosine
{
    double operator()(double argument) { return cos(argument); }
};

TEST_CASE("Trigonometry functions")
{
    Sine sine;
    calgopp::function::Function<Sine> sineFunction(sine);

    REQUIRE(double(sineFunction(60.0)) == sin(60.0));
    REQUIRE(double(sineFunction(60.0)) != cos(60.0));

    Cosine cosine;
    calgopp::function::Function<Cosine> cosineFunction(cosine);
    REQUIRE(double(cosineFunction(60.0)) == cos(60.0));
    REQUIRE(double(cosineFunction(60.0)) != sin(60.0));

    calgopp::function::Function<double (*)(double)> mathSinFunction(std::sin);
    REQUIRE(double(mathSinFunction(60.0)) == sin(60.0));
    REQUIRE(double(mathSinFunction(60.0)) != cos(60.0));

    auto sinLambda = [](double argument) -> double { return std::sin(argument); };
    calgopp::function::Function<double (*)(double)> lambdaFunction(sinLambda);
    REQUIRE(double(lambdaFunction(60.0)) == sin(60.0));
    REQUIRE(double(lambdaFunction(60.0)) != cos(60.0));
}

TEST_CASE("Linear function")
{
    calgopp::function::LinearFunction linearFunction(1, 0);
    REQUIRE(double(linearFunction(100)) == 100);
    REQUIRE(double(linearFunction(54)) == 54);

    linearFunction = calgopp::function::LinearFunction(2, 0);
    REQUIRE(double(linearFunction(100)) == 200);
    REQUIRE(double(linearFunction(54)) == 108);

    linearFunction = calgopp::function::LinearFunction(2, 5);
    REQUIRE(double(linearFunction(100)) == 205);
    REQUIRE(double(linearFunction(54)) == 113);
}
