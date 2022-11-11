#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this
// in one cpp file
#include <catch2/catch_all.hpp>

#include "calgopp/signal/Signal.h"
#include "calgopp/types/Peak.h"
#include "calgopp/types/Point.h"
#include "calgopp/signal/factory.h"

#include "test/utils/helpers.h"

#include <vector>
#include <utility>
#include <iostream>
#include <tuple>
#include <array>
#include <list>
#include <variant>
#include <memory>

using ContainerVariant = std::variant<std::vector<double>,
                                      std::vector<int>,
                                      std::vector<float>,
                                      std::array<double, 1000>,
                                      std::array<int, 1000>,
                                      std::array<float, 1000>>;

template <typename T>
std::vector<T> vectorInput()
{
    std::vector<T> token(1000);
    for (std::uint32_t i = 0; i < 1000; i++)
    {
        token[i] = 2 * i;
    }
    return token;
}

template <typename T>
std::array<T, 1000> arrayInput()
{
    std::array<T, 1000> token{};
    for (std::uint32_t i = 0; i < 1000; i++)
    {
        token[i] = 2 * i;
    }
    return token;
}

static std::vector<types::Peak> cSmallDataset = {{4, 60}, {8, 65}, {11, 53}, {15, 70}};
static std::vector<types::Peak> cMediumDataset = {
    {4, 60},    {8, 65},   {11, 53},  {15, 70},   {18, 71},  {23, 55},  {27, 44},   {31, 61},
    {36, 67},   {40, 80},  {43, 78},  {47, 79},   {50, 56},  {57, 54},  {60, 47},   {68, 51},
    {76, 45.5}, {80, 78},  {83, 81},  {88, 85},   {95, 92},  {99, 112}, {105, 102}, {110, 89},
    {112, 95},  {128, 54}, {145, 13}, {221, 4.5}, {224, 15}, {228, 21}, {233, 25}};
static std::vector<types::Peak> cBigDataset = {
    {4, 60},    {8, 65},   {11, 53},  {15, 70},   {18, 71},   {23, 55},  {27, 44},  {31, 61},    {36, 67},
    {40, 80},   {43, 78},  {47, 79},  {50, 56},   {57, 54},   {60, 47},  {68, 51},  {76, 45.5},  {80, 78},
    {83, 81},   {88, 85},  {95, 92},  {99, 112},  {105, 102}, {110, 89}, {112, 95}, {128, 54},   {145, 13},
    {221, 4.5}, {224, 15}, {228, 21}, {233, 25},  {235, 71},  {239, 55}, {244, 44}, {247, 61},   {255, 67},
    {269, 80},  {274, 78}, {277, 79}, {280, 56},  {291, 54},  {299, 47}, {303, 51}, {306, 45.5}, {320, 78},
    {324, 81},  {328, 85}, {339, 92}, {355, 112}, {375, 102}, {380, 89}, {389, 95}, {395, 54},   {398, 13},
    {402, 4.5}, {405, 15}, {409, 21}, {450, 25}};

TEST_CASE("Points tests")
{
    calgopp::types::Point a{10, 20};
    calgopp::types::Point b{10, 25};
    REQUIRE(a != b);
    b.y = 20;
    REQUIRE(a == b);
    REQUIRE(a + b == calgopp::types::Point{20, 40});
    a += b;
    REQUIRE(a == calgopp::types::Point{20, 40});
    a -= {20, 40};
    REQUIRE(a == calgopp::types::Point{0, 0});
}

TEST_CASE("Peaks tests")
{
    calgopp::types::Peak a{10, 20, calgopp::types::PeakType::eLow};
    calgopp::types::Peak b{10, 25, calgopp::types::PeakType::eHigh};
    REQUIRE(a != b);
    b.y = 20;
    REQUIRE(a != b);
    b.type = calgopp::types::PeakType::eLow;
    REQUIRE(a == b);
    REQUIRE(a + b == calgopp::types::Peak{20, 40, calgopp::types::PeakType::eLow});
    a += b;
    REQUIRE(a == calgopp::types::Peak{20, 40, calgopp::types::PeakType::eLow});
    a -= {20, 40};
    REQUIRE(a == calgopp::types::Peak{0, 0, calgopp::types::PeakType::eLow});
}

TEST_CASE("Signal creation from STL containers")
{
    ContainerVariant variant;

    SECTION("Vector of doubles") { variant = vectorInput<double>(); }

    SECTION("Vector of integers") { variant = vectorInput<int>(); }

    SECTION("Vector of floats") { variant = vectorInput<float>(); }

    SECTION("Array of doubles") { variant = arrayInput<double>(); }

    SECTION("Array of integers") { variant = arrayInput<int>(); }

    SECTION("Array of floats") { variant = arrayInput<float>(); }

    std::cout << "Variant: " << variant.index() << std::endl;
    auto signal = std::make_unique<calgopp::signal::Signal>();
    REQUIRE(signal->empty());

    switch (variant.index())
    {
        case 0:
        {
            signal = std::make_unique<calgopp::signal::Signal>(std::get<std::vector<double>>(variant).data(), 1000);
            break;
        }
        case 1:
        {
            signal = std::make_unique<calgopp::signal::Signal>(std::get<std::vector<int>>(variant).data(), 1000);
            break;
        }
        case 2:
        {
            signal = std::make_unique<calgopp::signal::Signal>(std::get<std::vector<float>>(variant).data(), 1000);
            break;
        }

        case 3:
        {
            signal =
                std::make_unique<calgopp::signal::Signal>(std::get<std::array<double, 1000>>(variant).data(), 1000);
            break;
        }
        case 4:
        {
            signal = std::make_unique<calgopp::signal::Signal>(std::get<std::array<int, 1000>>(variant).data(), 1000);
            break;
        }
        case 5:
        {
            signal = std::make_unique<calgopp::signal::Signal>(std::get<std::array<float, 1000>>(variant).data(), 1000);
            break;
        }
    }

    REQUIRE(signal->size() == 1000);
    REQUIRE(!signal->empty());

    for (std::uint32_t i = 0; i < 1000; i++)
    {
        REQUIRE((*signal)[i].x == i);
        REQUIRE((*signal)[i].y == 2 * i);
        REQUIRE((*signal)[i] == calgopp::types::Point{double(i), double(2 * i)});
    }

    std::uint32_t i = 0;
    for (const auto& point : *signal)
    {
        REQUIRE(point.x == i);
        REQUIRE(point.y == 2 * i);
        REQUIRE(point == calgopp::types::Point{double(i), double(2 * i)});
        i++;
    }
}

// TEST_CASE("Signal tests")
//{
//    auto setPeaksType = [](std::vector<calgopp::types::Peak>& peaks, calgopp::types::PeakType type) {
//        for (auto& peak : peaks)
//        {
//            peak.type = type;
//        }
//    };
//    std::vector<calgopp::types::Peak> inputPeaks;
//    std::vector<calgopp::types::Peak> detectedPeaks;
//    std::vector<calgopp::types::Peak> expectedPeaks;
//    std::vector<long double> values;
//    std::vector<long double> indexes;
//    calgopp::types::PeakType type{};
//    std::uint32_t distance = 1;
//    auto height = std::numeric_limits<double>::min();
//    std::vector<calgopp::types::Point> rawDataset;
//    SECTION("Small dataset")
//    {
//        inputPeaks = cSmallDataset;
//        SECTION("Highs")
//        {
//            type = calgopp::types::PeakType::eHigh;
//            setPeaksType(inputPeaks, type);
//            std::tie(values, indexes) = test::prepareDataset(inputPeaks);
//            SECTION("Distance - 1") { expectedPeaks = test::calculateExpectedPeaks(inputPeaks, distance, type); }
//            SECTION("Distance - 5")
//            {
//                distance = 5;
//                expectedPeaks = test::calculateExpectedPeaks(inputPeaks, distance, type);
//            }
//            SECTION("Distance - 10")
//            {
//                distance = 10;
//                expectedPeaks = test::calculateExpectedPeaks(inputPeaks, distance, type);
//            }
//        }
//        SECTION("Lows")
//        {
//            type = calgopp::types::PeakType::eLow;
//            setPeaksType(inputPeaks, type);
//            std::tie(values, indexes) = test::prepareDataset(inputPeaks);
//            SECTION("Distance - 1") { expectedPeaks = test::calculateExpectedPeaks(inputPeaks, distance, type); }
//            SECTION("Distance - 5")
//            {
//                distance = 5;
//                expectedPeaks = test::calculateExpectedPeaks(inputPeaks, distance, type);
//            }
//            SECTION("Distance - 10")
//            {
//                distance = 10;
//                expectedPeaks = test::calculateExpectedPeaks(inputPeaks, distance, type);
//            }
//        }
//    }
//
//    SECTION("Medium dataset")
//    {
//        inputPeaks = cMediumDataset;
//        SECTION("Highs")
//        {
//            type = calgopp::types::PeakType::eHigh;
//            setPeaksType(inputPeaks, type);
//            std::tie(values, indexes) = test::prepareDataset(inputPeaks);
//            SECTION("Distance - 1") { expectedPeaks = test::calculateExpectedPeaks(inputPeaks, distance, type); }
//            SECTION("Distance - 5")
//            {
//                distance = 5;
//                expectedPeaks = test::calculateExpectedPeaks(inputPeaks, distance, type);
//            }
//            SECTION("Distance - 10")
//            {
//                distance = 10;
//                expectedPeaks = test::calculateExpectedPeaks(inputPeaks, distance, type);
//            }
//        }
//        SECTION("Lows")
//        {
//            type = calgopp::types::PeakType::eLow;
//            setPeaksType(inputPeaks, type);
//            std::tie(values, indexes) = test::prepareDataset(inputPeaks);
//            SECTION("Distance - 1") { expectedPeaks = test::calculateExpectedPeaks(inputPeaks, distance, type); }
//            SECTION("Distance - 5")
//            {
//                distance = 5;
//                expectedPeaks = test::calculateExpectedPeaks(inputPeaks, distance, type);
//            }
//            SECTION("Distance - 10")
//            {
//                distance = 10;
//                expectedPeaks = test::calculateExpectedPeaks(inputPeaks, distance, type);
//            }
//        }
//    }
//
//    SECTION("Big dataset")
//    {
//        inputPeaks = cBigDataset;
//        SECTION("Highs")
//        {
//            type = calgopp::types::PeakType::eHigh;
//            setPeaksType(inputPeaks, type);
//            std::tie(values, indexes) = test::prepareDataset(inputPeaks);
//            SECTION("Distance - 1") { expectedPeaks = test::calculateExpectedPeaks(inputPeaks, distance, type); }
//            SECTION("Distance - 5")
//            {
//                distance = 5;
//                expectedPeaks = test::calculateExpectedPeaks(inputPeaks, distance, type);
//            }
//            SECTION("Distance - 10")
//            {
//                distance = 10;
//                expectedPeaks = test::calculateExpectedPeaks(inputPeaks, distance, type);
//            }
//        }
//        SECTION("Lows")
//        {
//            type = calgopp::types::PeakType::eLow;
//            setPeaksType(inputPeaks, type);
//            std::tie(values, indexes) = test::prepareDataset(inputPeaks);
//            SECTION("Distance - 1") { expectedPeaks = test::calculateExpectedPeaks(inputPeaks, distance, type); }
//            SECTION("Distance - 5")
//            {
//                distance = 5;
//                expectedPeaks = test::calculateExpectedPeaks(inputPeaks, distance, type);
//            }
//            SECTION("Distance - 10")
//            {
//                distance = 10;
//                expectedPeaks = test::calculateExpectedPeaks(inputPeaks, distance, type);
//            }
//        }
//    }
//    calgopp::signal::Signal signal(values, indexes);
//    std::string typeString = type == calgopp::types::PeakType::eLow ? "lows" : "highs";
//    INFO("Type: " + typeString);
//    INFO("Distance: " << distance);
//    INFO("Height: " << height);
//
//    detectedPeaks = signal.peaks(type, distance, height);
//    CHECK(expectedPeaks.size() == detectedPeaks.size());
//    for (std::uint32_t i = 0; i < detectedPeaks.size(); i++)
//    {
//        CHECK(expectedPeaks[i].x == detectedPeaks[i].x);
//        CHECK(expectedPeaks[i].y == detectedPeaks[i].y);
//    }
//}
