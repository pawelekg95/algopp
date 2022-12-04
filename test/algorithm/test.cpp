#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this
// in one cpp file
#include <catch2/catch_all.hpp>

#include "calgopp/algorithm/algorithm.h"

#include <numeric>
#include <vector>

TEST_CASE("Basic algorithms - finding elements in container")
{
    std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 1};
    REQUIRE(*std::min_element(vec.begin(), vec.end()) ==
            *calgopp::algorithm::numeric::minElement(vec.begin(), vec.end()));
    REQUIRE(*std::max_element(vec.begin(), vec.end()) ==
            *calgopp::algorithm::numeric::maxElement(vec.begin(), vec.end()));
}
