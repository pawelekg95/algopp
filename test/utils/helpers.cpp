#include "test/utils/helpers.h"

#include <vector>
#include <utility>
#include <iostream>
#include <algorithm>
#include <optional>
#include <map>
#include <cmath>
#include <array>
#include <list>
#include <functional>

namespace test {

void print(const PeakToPeakInfo& range)
{
    std::cout << "Range begin: " << range.beginIndex << std::endl;
    std::cout << "Range end: " << range.endIndex << std::endl;
    std::cout << "Begin value: " << range.beginValue << std::endl;
    std::cout << "End value: " << range.endValue << std::endl;
    std::cout << "Middle index: " << range.middleIndex << std::endl;
    std::cout << "Middle value: " << range.middleValue << std::endl;
    std::cout << "Pre middle step: " << range.preMidStep << std::endl;
    std::cout << "Post middle step: " << range.postMidStep << std::endl << std::endl;
}

PeakToPeakInfo nextRangeInfo(std::vector<types::Peak>& peaks, std::optional<PeakToPeakInfo> lastRange = std::nullopt)
{
    PeakToPeakInfo newRange{};
    if (!lastRange)
    {
        newRange.lastPeak = peaks.begin();
        newRange.currentPeak = peaks.begin();
        newRange.nextPeak = newRange.currentPeak + 1;

        newRange.beginIndex = 0;
        newRange.endIndex = (*newRange.currentPeak).x;

        newRange.beginValue = 0.0;
        newRange.endValue = (*newRange.currentPeak).y;
    }
    else
    {
        newRange.lastPeak = (*lastRange).currentPeak;
        newRange.currentPeak = (*lastRange).nextPeak;
        newRange.nextPeak = newRange.currentPeak + 1;

        newRange.beginIndex = (*(newRange.lastPeak)).x;
        newRange.endIndex =
            newRange.currentPeak == peaks.end() ? (*(peaks.end() - 1)).x + 5 : (*(newRange.currentPeak)).x;

        newRange.beginValue = (*newRange.lastPeak).y;
        newRange.endValue = newRange.currentPeak == peaks.end() ? 0.0 : (*newRange.currentPeak).y;
    }

    newRange.middleIndex = newRange.beginIndex + int((newRange.endIndex - newRange.beginIndex) / 2);

    if (newRange.lastPeak->type == newRange.currentPeak->type)
    {
        if (newRange.currentPeak->type == types::PeakType::eHigh)
        {
            newRange.middleValue = std::min(newRange.beginValue, newRange.endValue) * 0.8;
        }
        else if (newRange.currentPeak->type == types::PeakType::eLow)
        {
            newRange.middleValue = std::max(newRange.beginValue, newRange.endValue) * 1.2;
        }
    }
    else
    {
        newRange.middleValue = (newRange.endValue - newRange.beginValue) / 2;
    }

    newRange.preMidStep =
        std::fabs(newRange.middleValue - newRange.beginValue) / (newRange.middleIndex - newRange.beginIndex);
    newRange.postMidStep =
        std::fabs(newRange.endValue - newRange.middleValue) / (newRange.endIndex - newRange.middleIndex);

    return newRange;
}

std::tuple<std::vector<long double>, std::vector<long double>> prepareDataset(std::vector<types::Peak> peaks,
                                                                              std::uint32_t distance)
{
    (void) distance;
    [[maybe_unused]] auto addition = [](double a, double b) { return a + b; };
    [[maybe_unused]] auto subtraction = [](double a, double b) { return a - b; };
    if (peaks.empty())
    {
        return {};
    }
    std::sort(peaks.begin(), peaks.end(), [](const types::Peak& lhs, const types::Peak& rhs) { return lhs.x < rhs.x; });

    std::vector<long double> values(peaks[peaks.size() - 1].x + 5 + int(distance / 2));
    std::vector<long double> indexes(peaks[peaks.size() - 1].x + 5 + int(distance / 2));
    auto currentRange = nextRangeInfo(peaks);
    //    print(currentRange);

    for (std::uint32_t i = 0; i < values.size(); i++)
    {
        std::function<double(double a, double b)> preMidOperator;
        std::function<double(double a, double b)> postMidOperator;
        if (i == 0)
        {
            preMidOperator = postMidOperator =
                (currentRange.currentPeak->type == types::PeakType::eLow ? addition : subtraction);
        }
        else if (currentRange.currentPeak->type == currentRange.lastPeak->type)
        {
            preMidOperator = (currentRange.currentPeak->type == types::PeakType::eLow ? addition : subtraction);
            postMidOperator = (currentRange.currentPeak->type == types::PeakType::eLow ? subtraction : addition);
        }
        else
        {
            preMidOperator = postMidOperator =
                (currentRange.currentPeak->type == types::PeakType::eLow ? subtraction : addition);
        }
        indexes[i] = double(i);
        if (i == currentRange.endIndex)
        {
            values[i] = currentRange.endValue;
            currentRange = nextRangeInfo(peaks, currentRange);
            //    		print(currentRange);
            continue;
        }
        if (i <= currentRange.middleIndex)
        {
            values[i] = preMidOperator((i == 0 ? 0 : values[i - 1]), currentRange.preMidStep);
        }
        else if (i > currentRange.middleIndex)
        {
            values[i] = postMidOperator((i == 0 ? 0 : values[i - 1]), currentRange.postMidStep);
        }
    }
    return {values, indexes};
}

std::vector<types::Peak>
calculateExpectedPeaks(const std::vector<types::Peak>& input, std::uint32_t distance, types::PeakType type)
{
    std::uint32_t lastPeak = (*(input.end() - 1)).x;
    auto currentIt = input.begin();
    std::vector<types::Peak> ret;
    for (std::uint32_t i = 0; i <= lastPeak; i += distance)
    {
        if ((*currentIt).x >= i + distance)
        {
            continue;
        }
        auto greatestPeak = currentIt;
        while ((*currentIt).x >= i && (*currentIt).x < i + distance)
        {
            if ((type == types::PeakType::eLow ? (*currentIt).y < (*greatestPeak).y
                                               : (*currentIt).y > (*greatestPeak).y))
            {
                greatestPeak = currentIt;
            }
            currentIt++;
        }
        ret.emplace_back(*greatestPeak);
    }
    return ret;
}

} // namespace test
