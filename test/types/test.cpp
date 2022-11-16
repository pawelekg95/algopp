#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this
// in one cpp file
#include <catch2/catch_all.hpp>

#include "calgopp/types/Container.h"

#include "test/utils/helpers.h"

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
