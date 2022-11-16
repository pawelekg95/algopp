#pragma once

#include "calgopp/types/Point.h"
#include "calgopp/types/Peak.h"
#include "calgopp/types/Container.h"

#include <vector>
#include <optional>
#include <tuple>
#include <variant>
#include <array>
#include <queue>
#include <deque>
#include <cstdint>
#include <string>

using namespace calgopp;

namespace test {

using ContainerVariant = std::variant<std::vector<double>,
                                      std::vector<int>,
                                      std::vector<float>,
                                      std::array<double, 1000>,
                                      std::array<int, 1000>,
                                      std::array<float, 1000>>;

template <typename InputType>
class CStyleArrayVariant // NOLINT
{
public:
    CStyleArrayVariant(std::uint32_t size)
        : m_size(size)
        , m_array(new InputType[m_size])
    {
        for (std::uint32_t i = 0; i < m_size; i++)
        {
            m_array[i] = 2 * i;
        }
    }

    operator InputType*() const { return m_array; }

    ~CStyleArrayVariant() { delete[] m_array; }

private:
    std::uint32_t m_size{};
    InputType* m_array{nullptr};
};

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

template <typename T>
void addData(types::Container<T>& container, std::uint32_t amount)
{
    for (std::uint32_t i = 0; i < amount; i++)
    {
        container.append(2 * i);
    }
}

int testDataset(const std::string& scriptPath,
                const std::string& outputPath,
                std::uint32_t size,
                double height = 0,
                double distance = 0,
                types::PeakType type = types::PeakType::eHigh);

std::vector<calgopp::types::Point> getRawDataset(const std::string& datasetPath);

std::vector<calgopp::types::Peak> getPeaks(const std::string& datasetPath);

} // namespace test
