#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this
// in one cpp file
#include <catch2/catch_all.hpp>

#include "calgopp/algorithm/algorithm.h"

#include <numeric>
#include <vector>

TEST_CASE("Find")
{
    std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 1};
    REQUIRE(*std::min_element(vec.begin(), vec.end()) ==
            *calgopp::algorithm::numeric::minElement(vec.begin(), vec.end()));
    REQUIRE(*std::max_element(vec.begin(), vec.end()) ==
            *calgopp::algorithm::numeric::maxElement(vec.begin(), vec.end()));
}

TEST_CASE("Sum")
{
    std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    REQUIRE(calgopp::algorithm::numeric::sum(vec.begin(), vec.end()) == std::accumulate(vec.begin(), vec.end(), 0));
    REQUIRE(calgopp::algorithm::numeric::sum(vec.begin() + 5, vec.end()) ==
            std::accumulate(vec.begin() + 5, vec.end(), 0));
}
