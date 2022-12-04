#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this
// in one cpp file
#include <catch2/catch_all.hpp>

#include "calgopp/math/math.h"

#include <cmath>

TEST_CASE("Numerics")
{
    REQUIRE(std::abs(-15) == calgopp::math::abs(-15));
    REQUIRE(std::abs(-15.4) == calgopp::math::abs(-15.4));
    REQUIRE(std::abs(15) == calgopp::math::abs(-15));
}
