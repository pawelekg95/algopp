#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this
// in one cpp file

#include <catch2/catch_all.hpp>

#include "calgopp/approximation/approximation.h"
#include "calgopp/signal/Signal.h"
#include "calgopp/types/Point.h"

#include <iostream>

TEST_CASE("Least squares method")
{
    SECTION("5 points")
    {
        calgopp::types::Point points[] = {{2.0, 2.5}, {4.0, 10.0}, {6.0, 32.0}, {8.0, 40.0}, {10.0, 60.0}};
        calgopp::signal::Signal signal(points, 5);
        auto linearFunction = calgopp::approximation::leastSquares(signal);
        REQUIRE(linearFunction.a() == 7.25);
        REQUIRE(linearFunction.b() == -14.6);
        std::cout << linearFunction.a() << " " << linearFunction.b() << std::endl;
    }

    SECTION("2 points")
    {
        calgopp::types::Point points[] = {{2.0, 4.0}, {4.0, 10.0}};
        calgopp::signal::Signal signal(points, 2);
        auto linearFunction = calgopp::approximation::leastSquares(signal);
        REQUIRE(linearFunction.a() == 3);
        REQUIRE(linearFunction.b() == -2);
        std::cout << linearFunction.a() << " " << linearFunction.b() << std::endl;
    }
}
