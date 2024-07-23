#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this
// in one cpp file
#include "calgopp/signal/Signal.h"
#include "calgopp/signal/transform/FourierTransform.h"
#include "calgopp/types/Peak.h"
#include "calgopp/types/Point.h"
#include "test/utils/helpers.h"

#include <catch2/catch_all.hpp>

#include <array>
#include <cmath>
#include <iostream>
#include <list>
#include <memory>
#include <utility>
#include <variant>
#include <vector>

class OverallTimerWatcher // NOLINT
{
public:
    ~OverallTimerWatcher() { std::cout << "Total time elapsed (us): " << m_overallWatcher << std::endl; }

    const OverallTimerWatcher& operator+=(std::uint64_t timer) const
    {
        m_overallWatcher += timer;
        std::cout << "Timer added (us): " << timer
                  << " from test case: " << Catch::getResultCapture().getCurrentTestName() << std::endl;
        return *this;
    }

private:
    mutable std::uint64_t m_overallWatcher{};
};

class TimerTracker // NOLINT
{
public:
    explicit TimerTracker(const OverallTimerWatcher& overallTimerWatcher)
        : m_overallTimerWatcher(overallTimerWatcher)
    {
        m_timer.start();
    }

    ~TimerTracker() { m_overallTimerWatcher += m_timer.getElapsedMicroseconds(); }

private:
    const OverallTimerWatcher& m_overallTimerWatcher;
    Catch::Timer m_timer;
};

const OverallTimerWatcher overallTimer;

void addPoints(calgopp::signal::Signal& signal, std::uint32_t amount, bool reset = false) // NOLINT
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

void removePoints(calgopp::signal::Signal& signal, std::uint32_t amount) // NOLINT
{
    while (amount > 0 && !signal.empty())
    {
        signal.remove(signal.size() - 1);
        amount--;
    }
}

TEST_CASE("Complex")
{
    calgopp::types::Complex a{10, 0};
    calgopp::types::Complex b{10, 0};
    REQUIRE(a == b);
    a.imag = 25.6;
    REQUIRE(a != b);
    REQUIRE(b * b == calgopp::types::Complex{100, 0});
    REQUIRE(calgopp::types::Complex{100, 0} == math::pow(b, 2));
    calgopp::types::Complex c{0, -1};
    REQUIRE(c * c == calgopp::types::Complex{-1, 0});
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

    SECTION("Vector of doubles")
    {
        variant = test::vectorInput<double>();
    }

    SECTION("Vector of integers")
    {
        variant = test::vectorInput<int>();
    }

    SECTION("Vector of floats")
    {
        variant = test::vectorInput<float>();
    }

    SECTION("Array of doubles")
    {
        variant = test::arrayInput<double>();
    }

    SECTION("Array of integers")
    {
        variant = test::arrayInput<int>();
    }

    SECTION("Array of floats")
    {
        variant = test::arrayInput<float>();
    }

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

        case 3:
        {
            signal = std::make_unique<calgopp::signal::Signal>(std::get<std::array<double, 1000>>(variant));
            break;
        }
        case 4:
        {
            signal = std::make_unique<calgopp::signal::Signal>(std::get<std::array<int, 1000>>(variant));
            break;
        }
        case 5:
        {
            signal = std::make_unique<calgopp::signal::Signal>(std::get<std::array<float, 1000>>(variant));
            break;
        }
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

TEST_CASE("Signal tests - peaks")
{
    calgopp::types::PeakType peakType{calgopp::types::PeakType::eHigh};
    std::vector<types::Point> rawDataset;
    std::vector<types::Peak> expectedPeaks;
    etl::vector<types::Peak, MAX_SIGNAL_SIZE> detectedPeaks;

    auto peakDetected = [&expectedPeaks](const calgopp::types::Peak& peak) -> bool {
        bool peakDetectedCorrectly = std::find(expectedPeaks.begin(), expectedPeaks.end(), peak) != expectedPeaks.end();
        if (!peakDetectedCorrectly)
        {
            std::cout << "Detected peak not found in expected peaks. Index: " << peak.x << ", value: " << peak.y
                      << std::endl;
        }
        return peakDetectedCorrectly;
    };

    SECTION("Highs")
    {
        peakType = calgopp::types::PeakType::eHigh;
    }

    SECTION("Lows")
    {
        peakType = calgopp::types::PeakType::eLow;
    }

    std::uint32_t truePositivePredictions{};
    std::uint32_t allDetectedPredictions{};
    std::uint32_t expectedPredictions{};

    for (std::uint32_t size = 1; size < 3; size++)
    {
        for (std::uint32_t distanceMultiplier = 1; distanceMultiplier < 4; distanceMultiplier++)
        {
            for (std::uint32_t heightMultiplier = 0; heightMultiplier < 3; heightMultiplier++)
            {
                double datasetSize = pow(100, size);
                std::uint32_t distance = distanceMultiplier * 5;
                double height = heightMultiplier * 0.1;
                auto currentPath = std::filesystem::canonical("/proc/self/exe").parent_path();
                REQUIRE(test::testDataset(currentPath / "dataset_generator.py",
                                          currentPath / "dataset.json",
                                          std::uint32_t(datasetSize),
                                          height,
                                          distance,
                                          peakType) == 0);
                rawDataset = test::getRawDataset(currentPath / "dataset.json");
                expectedPeaks = test::getPeaks(currentPath / "dataset.json");
                auto signal = calgopp::signal::Signal(rawDataset);
                detectedPeaks = signal.peaks(peakType, height, distance);
                expectedPredictions += expectedPeaks.size();
                for (const auto& detectedPeak : detectedPeaks)
                {
                    allDetectedPredictions++;
                    truePositivePredictions += static_cast<std::uint32_t>(peakDetected(detectedPeak));
                }
            }
        }
    }
    CHECK(static_cast<double>(truePositivePredictions) / static_cast<double>(allDetectedPredictions) > 0.98);
    CHECK(static_cast<double>(allDetectedPredictions) / static_cast<double>(expectedPredictions) > 0.8);

    std::cout << "true positive / all detected predictions: "
              << static_cast<double>(truePositivePredictions) / static_cast<double>(allDetectedPredictions)
              << std::endl;
    std::cout << "detected predictions / expected predictions: "
              << static_cast<double>(allDetectedPredictions) / static_cast<double>(expectedPredictions) << std::endl;
}

TEST_CASE("Transforms")
{
    TimerTracker tracker(overallTimer);
    auto currentPath = std::filesystem::canonical("/proc/self/exe").parent_path();
    REQUIRE(test::testDataset(currentPath / "dataset_generator.py", currentPath / "dataset.json", 1000) == 0);
    auto rawDataset = test::getRawDataset(currentPath / "dataset.json");
    auto modelTransformedDataset =
        test::getTransformedDataset(currentPath / "dataset.json", test::Transform::eFastFourier);
    calgopp::signal::transform::FourierTransform fourierTransform;
    std::cout << "Processing signal" << std::endl;
    auto testedTransformedDataset = fourierTransform.process(calgopp::signal::Signal{rawDataset});
    std::cout << "Signal processed" << std::endl;
    CHECK(testedTransformedDataset.size() == modelTransformedDataset.size());

    for (std::uint32_t i = 0; i < modelTransformedDataset.size(); i++)
    {
        CHECK(test::almostEqual(testedTransformedDataset[i].y,
                                modelTransformedDataset[i],
                                0.001 * calgopp::math::abs(modelTransformedDataset[i])));
    }
}

TEST_CASE("Empty signal")
{
    calgopp::signal::Signal signal;
    REQUIRE(signal.empty());
    try
    {
        signal[1];
        REQUIRE(false);
    }
    catch (const char* str) // NOLINT
    {
        REQUIRE(true);
    }
    auto peaks = signal.peaks();
    REQUIRE(peaks.empty());
    peaks.push_back({1, 2});
    peaks = signal.peaks();
    REQUIRE(peaks.empty());
    peaks.push_back({2, 3});
    peaks = signal.peaks();
    REQUIRE(peaks.empty());
    peaks.push_back({3, 4});
    peaks = signal.peaks();
    REQUIRE(peaks.empty());
}

TEST_CASE("Signal with zeros")
{
    // NOLINTNEXTLINE
    calgopp::types::Point points[] = {{1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}, {8, 0}, {9, 0}, {10, 0}};
    calgopp::signal::Signal signal(points, 10); // NOLINT
    auto peaks = signal.peaks();
    REQUIRE(peaks.empty());
}
