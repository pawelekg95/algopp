#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this
// in one cpp file
#include "calgopp/algorithm/algorithm.h"

#include <catch2/catch_all.hpp>

#include <numeric>
#include <vector>

TEST_CASE("Find")
{
    std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 1};
    REQUIRE(*std::min_element(vec.begin(), vec.end()) ==
            *calgopp::algorithm::numeric::minElement(vec.begin(), vec.end()));
    REQUIRE(*std::max_element(vec.begin(), vec.end()) ==
            *calgopp::algorithm::numeric::maxElement(vec.begin(), vec.end()));

    calgopp::types::Container<int> container(vec);
    REQUIRE(*std::min_element(container.begin(), container.end()) ==
            *calgopp::algorithm::numeric::minElement(container.begin(), container.end()));
    REQUIRE(*std::max_element(container.begin(), container.end()) ==
            *calgopp::algorithm::numeric::maxElement(container.begin(), container.end()));
}

TEST_CASE("Sum")
{
    std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    REQUIRE(calgopp::algorithm::numeric::sum(vec.begin(), vec.end()) == std::accumulate(vec.begin(), vec.end(), 0));
    REQUIRE(calgopp::algorithm::numeric::sum(vec.begin() + 5, vec.end()) ==
            std::accumulate(vec.begin() + 5, vec.end(), 0));

    calgopp::types::Container<int> container(vec);
    REQUIRE(calgopp::algorithm::numeric::sum(container.begin(), container.end()) ==
            std::accumulate(container.begin(), container.end(), 0));
    REQUIRE(calgopp::algorithm::numeric::sum(container.begin() + 5, container.end()) ==
            std::accumulate(container.begin() + 5, container.end(), 0));
}
