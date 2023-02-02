#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this
// in one cpp file
#include <catch2/catch_all.hpp>

#include "calgopp/types/Container.h"

#include "test/utils/helpers.h"

#include <algorithm>

using namespace calgopp::types;

TEST_CASE("Creating container from STL container")
{
    test::ContainerVariant variant;
    std::unique_ptr<Container<double>> container;

    SECTION("Vector of doubles") { variant = test::vectorInput<double>(); }

    SECTION("Array of doubles") { variant = test::arrayInput<double>(); }

    switch (variant.index())
    {
        case 0:
        {
            container = std::make_unique<Container<double>>(std::get<std::vector<double>>(variant));
            break;
        }
        case 3:
        {
            container = std::make_unique<Container<double>>(std::get<std::array<double, 1000>>(variant));
            break;
        }
        default: break;
    }

    REQUIRE(container->size() == 1000);
    REQUIRE(!container->empty());

    for (std::uint32_t i = 0; i < 1000; i++)
    {
        REQUIRE((*container)[i] == 2 * i);
    }

    std::uint32_t i = 0;
    for (const auto& point : *container)
    {
        REQUIRE(point == 2 * i);
        i++;
    }
    REQUIRE(i == 1000);
}

TEST_CASE("Creating container from C style array container")
{
    test::CStyleArrayVariant<double> array(1000);
    Container<double> container(static_cast<double*>(array), 1000);

    REQUIRE(container.size() == 1000);
    REQUIRE(!container.empty());

    for (std::uint32_t i = 0; i < 1000; i++)
    {
        REQUIRE(container[i] == 2 * i);
    }

    std::uint32_t i = 0;
    for (const auto& point : container)
    {
        REQUIRE(point == 2 * i);
        i++;
    }
}

TEST_CASE("Add and remove data")
{
    Container<int> container;

    REQUIRE(container.empty());
    REQUIRE(container.capacity() == 10);
    test::addData(container, 1000);
    REQUIRE(!container.empty());
    REQUIRE(container.size() == 1000);

    int i = 0;
    for (const auto& data : container)
    {
        REQUIRE(data == 2 * i);
        i++;
    }
    REQUIRE(i == 1000);

    REQUIRE(container[50] == 100);
    REQUIRE(container[51] == 102);
    REQUIRE(container[52] == 104);
    REQUIRE(container[53] == 106);

    container.remove(51);

    REQUIRE(container.size() == 999);
    REQUIRE(container[50] == 100);
    REQUIRE(container[51] == 104);
    REQUIRE(container[52] == 106);

    container.insert(222, 51);
    REQUIRE(container.size() == 1000);
    REQUIRE(container[51] == 222);
    REQUIRE(container[52] == 104);
    REQUIRE(container[53] == 106);

    container.insert(999, 0);
    REQUIRE(container.size() == 1001);
    REQUIRE(container[0] == 999);
    REQUIRE(container[1] == 0);
}

TEST_CASE("Constructors")
{
    Container<int> container1;
    Container<int> container2;
    Container<int> container3;

    REQUIRE(container1.empty());
    REQUIRE(container2.empty());
    REQUIRE(container3.empty());

    test::addData(container1, 1000);
    REQUIRE(!container1.empty());
    for (int i = 0; i < 1000; i++)
    {
        REQUIRE(container1[i] == 2 * i);
    }

    container2 = container1;
    REQUIRE(!container2.empty());
    for (int i = 0; i < 1000; i++)
    {
        REQUIRE(container2[i] == 2 * i);
    }

    container3 = static_cast<Container<int>&&>(container1);
    REQUIRE(!container3.empty());
    for (int i = 0; i < 1000; i++)
    {
        REQUIRE(container3[i] == 2 * i);
    }

    REQUIRE(container1.empty());
    REQUIRE(container1.size() == 0);

    Container<int> container4(container3);
    REQUIRE(!container4.empty());
    for (int i = 0; i < 1000; i++)
    {
        REQUIRE(container4[i] == 2 * i);
    }

    Container<int> container5(static_cast<Container<int>&&>(container4));
    REQUIRE(!container5.empty());
    for (int i = 0; i < 1000; i++)
    {
        REQUIRE(container5[i] == 2 * i);
    }
    REQUIRE(container4.empty());
}

TEST_CASE("Accessing elements")
{
    Container<int> container;
    test::addData(container, 1000);
    REQUIRE(!container.empty());
    for (int i = 0; i < 1000; i++)
    {
        REQUIRE(container[i] == 2 * i);
    }

    REQUIRE(container[999] == 1998);
    REQUIRE(container.at(999) == 1998);

    container[999] = 3;

    REQUIRE(container[999] == 3);

    container.remove(999);

    try
    {
        container[999];
        REQUIRE(false);
    }
    catch (const char* str)
    {
        REQUIRE(std::string(str) == "Index out of scope");
    }
}

TEST_CASE("Invalid construction")
{
    test::CStyleArrayVariant<double> array(1000);
    double* invalidArray = nullptr;
    try
    {
        Container<double> container(invalidArray, 100);
    }
    catch (const char* str)
    {
        REQUIRE(std::string(str) == "Invalid array");
    }
}

TEST_CASE("Multidimensional containers")
{
    Container<Container<int>> matrix(2);
    REQUIRE(!matrix.empty());
    REQUIRE(matrix.size() == 2);
    for (auto& container : matrix)
    {
        test::addData(container, 1000);
        REQUIRE(!container.empty());
        for (int i = 0; i < 1000; i++)
        {
            REQUIRE(container[i] == 2 * i);
        }
    }
}

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

TEST_CASE("STL actions on Container")
{
    calgopp::types::Point points[] = {{1, 14},
                                      {2, 13},
                                      {10, 5},
                                      {15, 0},
                                      {4, 11},
                                      {5, 10},
                                      {3, 12},
                                      {6, 9},
                                      {7, 8},
                                      {11, 4},
                                      {12, 3},
                                      {8, 7},
                                      {9, 6},
                                      {14, 1},
                                      {13, 2}};
    calgopp::types::Container<calgopp::types::Point> container(points, 15);

    // Sorting
    std::sort(container.begin(),
              container.end(),
              [](const calgopp::types::Point& lhs, const calgopp::types::Point& rhs) -> bool { return lhs.x < rhs.x; });

    for (std::uint32_t i = 0; i < 15; i++)
    {
        REQUIRE(container[i].x == i + 1);
        REQUIRE(container[i].y == 15 - container[i].x);
    }

    std::sort(container.begin(),
              container.end(),
              [](const calgopp::types::Point& lhs, const calgopp::types::Point& rhs) -> bool { return lhs.y < rhs.y; });

    for (std::uint32_t i = 0; i < 15; i++)
    {
        REQUIRE(container[i].x == 15 - container[i].y.real);
        REQUIRE(container[i].y == i);
    }
}
