#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this
// in one cpp file
#include "test/utils/helpers.h"

#include <catch2/catch_all.hpp>

#include "calgopp/function/Function.h"
#include "calgopp/function/LinearFunction.h"

#include <cmath>

struct Sine
{
    double operator()(double argument)
    {
        return sin(argument);
    }
};

struct Cosine
{
    double operator()(double argument)
    {
        return cos(argument);
    }
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
}
