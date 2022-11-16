#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this
// in one cpp file
#include <catch2/catch_all.hpp>

#include "calgopp/signal/Signal.h"
#include "calgopp/types/Peak.h"
#include "calgopp/types/Point.h"

#include "test/utils/helpers.h"

#include <vector>
#include <utility>
#include <iostream>
#include <tuple>
#include <array>
#include <list>
#include <variant>
#include <memory>
#include <cmath>

void addPoints(calgopp::signal::Signal& signal, std::uint32_t amount, bool reset = false)
{
    static std::uint32_t last = 0;
    if (reset)
    {
        last = 0;
    }

    for (std::uint32_t i = 0; i < amount; i++)
    {
        signal += types::Point{last + i, last + i + 10};
    }
    last += amount;
}

void removePoints(calgopp::signal::Signal& signal, std::uint32_t amount)
{
    while (amount > 0 && !signal.empty())
    {
        signal.remove(signal.size() - 1);
        amount--;
    }
}

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
    test::ContainerVariant variant;

    SECTION("Vector of doubles") { variant = test::vectorInput<double>(); }

    SECTION("Vector of integers") { variant = test::vectorInput<int>(); }

    SECTION("Vector of floats") { variant = test::vectorInput<float>(); }

    //    SECTION("Array of doubles") { variant = test::arrayInput<double>(); }
    //
    //    SECTION("Array of integers") { variant = test::arrayInput<int>(); }
    //
    //    SECTION("Array of floats") { variant = test::arrayInput<float>(); }

    auto signal = std::make_unique<calgopp::signal::Signal>();
    REQUIRE(signal->empty());

    switch (variant.index())
    {
        case 0:
        {
            signal = std::make_unique<calgopp::signal::Signal>(std::get<std::vector<double>>(variant));
            break;
        }
        case 1:
        {
            signal = std::make_unique<calgopp::signal::Signal>(std::get<std::vector<int>>(variant));
            break;
        }
        case 2:
        {
            signal = std::make_unique<calgopp::signal::Signal>(std::get<std::vector<float>>(variant));
            break;
        }

            //        case 3:
            //        {
            //            signal = std::make_unique<calgopp::signal::Signal>(std::get<std::array<double,
            //            1000>>(variant)); break;
            //        }
            //        case 4:
            //        {
            //            signal = std::make_unique<calgopp::signal::Signal>(std::get<std::array<int, 1000>>(variant));
            //            break;
            //        }
            //        case 5:
            //        {
            //            signal = std::make_unique<calgopp::signal::Signal>(std::get<std::array<float,
            //            1000>>(variant)); break;
            //        }
        default: break;
    }

    REQUIRE(signal->size() == 1000);
    REQUIRE(!signal->empty());

    for (std::uint32_t i = 0; i < 1000; i++)
    {
        REQUIRE((*signal)[i].x == i);
        REQUIRE((*signal)[i].y == 2 * i);
        REQUIRE((*signal)[i] == calgopp::types::Point{i, 2 * i});
    }

    std::uint32_t i = 0;
    for (const auto& point : *signal)
    {
        REQUIRE(point.x == i);
        REQUIRE(point.y == 2 * i);
        REQUIRE(point == calgopp::types::Point{i, 2 * i});
        i++;
    }
}

TEST_CASE("Signal creation from C style arrays")
{
    auto signal = std::make_unique<calgopp::signal::Signal>();
    REQUIRE(signal->empty());

    SECTION("Integer array")
    {
        test::CStyleArrayVariant<int> cStyleArray(1000);
        signal = std::make_unique<calgopp::signal::Signal>(static_cast<int*>(cStyleArray), 1000);
    }

    SECTION("Double array")
    {
        test::CStyleArrayVariant<double> cStyleArray(1000);
        signal = std::make_unique<calgopp::signal::Signal>(static_cast<double*>(cStyleArray), 1000);
    }

    SECTION("Float array")
    {
        test::CStyleArrayVariant<float> cStyleArray(1000);
        signal = std::make_unique<calgopp::signal::Signal>(static_cast<float*>(cStyleArray), 1000);
    }

    REQUIRE(signal->size() == 1000);
    REQUIRE(!signal->empty());

    for (std::uint32_t i = 0; i < 1000; i++)
    {
        REQUIRE((*signal)[i].x == i);
        REQUIRE((*signal)[i].y == 2 * i);
        REQUIRE((*signal)[i] == calgopp::types::Point{i, 2 * i});
    }

    std::uint32_t i = 0;
    for (const auto& point : *signal)
    {
        REQUIRE(point.x == i);
        REQUIRE(point.y == 2 * i);
        REQUIRE(point == calgopp::types::Point{i, 2 * i});
        i++;
    }
}

TEST_CASE("Appending points")
{
    calgopp::signal::Signal signal;
    REQUIRE(signal.empty());

    addPoints(signal, 1);
    REQUIRE(!signal.empty());
    REQUIRE(signal[0].x == 0);
    REQUIRE(signal[0].y == 10);

    addPoints(signal, 5);

    REQUIRE(signal.size() == 6);
    REQUIRE(signal[3].x == 3);
    REQUIRE(signal[3].y == 13);

    addPoints(signal, 5);

    REQUIRE(signal.size() == 11);

    addPoints(signal, 4000);

    REQUIRE(signal.size() == 4011);
    REQUIRE(signal[1200].x == 1200);
    REQUIRE(signal[1200].y == 1210);
}

TEST_CASE("Erasing points")
{
    calgopp::signal::Signal signal;
    REQUIRE(signal.empty());

    addPoints(signal, 4000, true);
    REQUIRE(!signal.empty());
    REQUIRE(signal.size() == 4000);
    REQUIRE(signal[1200].x == 1200);
    REQUIRE(signal[1200].y == 1210);

    REQUIRE(signal[3999] == types::Point{3999, 4009});

    removePoints(signal, 10);

    REQUIRE(signal.size() == 3990);

    try
    {
        signal[3999];
    }
    catch (const char* str) // NOLINT
    {
        REQUIRE(std::string(str) == "Index out of scope");
    }
}

TEST_CASE("Signal tests")
{
    calgopp::types::PeakType peakType{calgopp::types::PeakType::eHigh};
    std::vector<types::Point> rawDataset;
    std::vector<types::Peak> expectedPeaks;
    types::Container<types::Peak> detectedPeaks;
    SECTION("Highs") { peakType = calgopp::types::PeakType::eHigh; }

//    SECTION("Lows") { peakType = calgopp::types::PeakType::eLow; }

    for (std::uint32_t i = 1; i < 5; i++)
    {
        for (std::uint32_t j = 1; j < 4; j++)
        {
            for (std::uint32_t k = 0; k < 3; k++)
            {
                double datasetSize = pow(100, i);
                double distance = j * 5;
                double height = k * 0.1;
                REQUIRE(test::testDataset("/tmp/dataset_generator.py",
                                          "/tmp/dataset.json",
                                          std::uint32_t(datasetSize),
                                          height,
                                          distance,
                                          peakType) == 0);
                rawDataset = test::getRawDataset("/tmp/dataset.json");
                expectedPeaks = test::getPeaks("/tmp/dataset.json");
                auto signal = calgopp::signal::Signal(calgopp::types::Container<types::Point>(rawDataset));
                detectedPeaks = signal.peaks(peakType, height, distance);
                CHECK(detectedPeaks.size() == expectedPeaks.size());
                for (std::uint32_t l = 0; l < expectedPeaks.size(); l++)
                {
                    REQUIRE(expectedPeaks[l].y == detectedPeaks[l].y);
                    REQUIRE(expectedPeaks[l].x == detectedPeaks[l].x);
                }
            }
        }
    }
}
