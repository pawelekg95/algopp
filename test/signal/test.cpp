#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this
// in one cpp file
#include <catch2/catch_all.hpp>

#include "algopp/signal/Signal.h"
#include "algopp/types/Peak.h"
#include "algopp/types/Point.h"

#include <vector>
#include <utility>

using namespace algopp;

TEST_CASE("Points tests")
{
    types::Point a{10, 20};
    types::Point b{10, 25};
    REQUIRE(a != b);
    b.y = 20;
    REQUIRE(a == b);
    REQUIRE(a + b == types::Point{20, 40});
    a += b;
    REQUIRE(a == types::Point{20, 40});
    a -= {20, 40};
    REQUIRE(a == types::Point{0, 0});
}

TEST_CASE("Peaks tests")
{
    types::Peak a{10, 20, types::PeakType::eLow};
    types::Peak b{10, 25, types::PeakType::eHigh};
    REQUIRE(a != b);
    b.y = 20;
    REQUIRE(a != b);
    b.type = types::PeakType::eLow;
    REQUIRE(a == b);
    REQUIRE(a + b == types::Peak{20, 40, types::PeakType::eLow});
    a += b;
    REQUIRE(a == types::Peak{20, 40, types::PeakType::eLow});
    a -= {20, 40};
    REQUIRE(a == types::Peak{0, 0, types::PeakType::eLow});
}
