#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this
// in one cpp file
#include "test/utils/helpers.h"

#include <catch2/catch_all.hpp>

#include <algorithm>

using namespace calgopp::types;

TEST_CASE("Complex")
{
    REQUIRE(test::almostEqual(math::abs(types::Complex{3, 4}), 5));
    REQUIRE(test::almostEqual(math::abs(types::Complex{8, -6}), 10));

    REQUIRE(test::almostEqual(math::pow(2, types::Complex{5, 12}), types::Complex{-14.3147539, 28.61971035}));
    REQUIRE(test::almostEqual(math::pow(3, types::Complex{5.5, 11.1}), types::Complex{392.135, -152.896}, 1));

    REQUIRE(test::almostEqual(math::pow(types::Complex{5, 12}, 2), types::Complex{-119, 120}));
    REQUIRE(test::almostEqual(math::pow(types::Complex{5.5, 11.1}, 3), types::Complex{-1866.59, -360.306}, 1));

    types::Complex i = {0, 1};

    REQUIRE(i * i == types::Complex{-1, 0});
    REQUIRE(i * i * i == types::Complex{0, -1});
    REQUIRE(i * i * i * i == types::Complex{1, 0});

    types::Complex minusI = {0, -1};

    REQUIRE(minusI * minusI == types::Complex{-1, 0});
    REQUIRE(minusI * minusI * minusI == types::Complex{0, 1});
    REQUIRE(minusI * minusI * minusI * minusI == types::Complex{1, 0});

    REQUIRE(types::Complex{42, -23} * types::Complex{7, 3} == types::Complex{363, -35});
}
