#pragma once

#include "calgopp/types/Point.h"
#include "calgopp/types/Peak.h"

#include <vector>
#include <optional>
#include <tuple>

using namespace calgopp;

namespace test {

struct PeakToPeakInfo
{
    std::vector<types::Peak>::iterator lastPeak;
    std::vector<types::Peak>::iterator currentPeak;
    std::vector<types::Peak>::iterator nextPeak;

    std::uint32_t beginIndex{};
    std::uint32_t middleIndex{};
    std::uint32_t endIndex{};

    long double beginValue{};
    long double endValue{};
    long double middleValue{};
    long double preMidStep{0.01};
    long double postMidStep{0.01};
};

void print(const PeakToPeakInfo& range);

std::tuple<std::vector<long double>, std::vector<long double>> prepareDataset(std::vector<types::Peak> peaks,
                                                                              std::uint32_t distance = 1);

std::vector<types::Peak>
calculateExpectedPeaks(const std::vector<types::Peak>& input, std::uint32_t distance, types::PeakType type);

} // namespace test
