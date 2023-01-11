#include "test/utils/helpers.h"

#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>

#include <fstream>
#include <cstdlib>
#include <string>

namespace test {

int testDataset(const std::filesystem::path& scriptPath,
                const std::filesystem::path& outputPath,
                std::uint32_t size,
                double height,
                double distance,
                types::PeakType type)
{
    std::string command = scriptPath.string() + " -p " + outputPath.string() + " -s " + std::to_string(size) +
                          " --height " + std::to_string(height) + " -d " + std::to_string(distance) + " -t " +
                          (type == calgopp::types::PeakType::eHigh ? "high" : "low");
    return system(command.c_str()); // NOLINT cert-env33-c
}

std::vector<calgopp::types::Point> getRawDataset(const std::filesystem::path& datasetPath)
{
    std::ifstream file(datasetPath);
    rapidjson::IStreamWrapper stream(file);
    rapidjson::Document parsedConfig;
    parsedConfig.ParseStream(stream);
    assert(!parsedConfig.HasParseError());

    auto datasetArray = parsedConfig.GetObject()["dataset"].GetArray();
    std::vector<calgopp::types::Point> dataset(datasetArray.Size());
    for (std::uint32_t i = 0; i < datasetArray.Size(); i++)
    {
        dataset[i] = types::Point{i, datasetArray[i].GetFloat()};
    }
    return dataset;
}

std::vector<calgopp::types::Peak> getPeaks(const std::filesystem::path& datasetPath)
{
    std::ifstream file(datasetPath);
    rapidjson::IStreamWrapper stream(file);
    rapidjson::Document parsedConfig;
    parsedConfig.ParseStream(stream);
    assert(!parsedConfig.HasParseError());

    auto datasetArray = parsedConfig.GetObject()["peaks"].GetArray();
    auto peaksType = std::string(parsedConfig.GetObject()["peaks_type"].GetString());
    std::vector<calgopp::types::Peak> dataset(datasetArray.Size());
    for (std::uint32_t i = 0; i < datasetArray.Size(); i++)
    {
        auto pointArray = datasetArray[i].GetArray();
        dataset[i] = types::Peak{pointArray[0].GetInt(),
                                 pointArray[1].GetFloat(),
                                 peaksType == "high" ? types::PeakType::eHigh : types::PeakType::eLow};
    }
    return dataset;
}

std::vector<calgopp::types::Complex> getTransformedDataset(const std::filesystem::path& datasetPath,
                                                           Transform transform)
{
    (void) transform;
    std::ifstream file(datasetPath);
    rapidjson::IStreamWrapper stream(file);
    rapidjson::Document parsedConfig;
    parsedConfig.ParseStream(stream);
    assert(!parsedConfig.HasParseError());

    auto datasetArray = parsedConfig.GetObject()["fourier"].GetArray();
    std::vector<calgopp::types::Complex> dataset(datasetArray.Size());
    for (std::uint32_t i = 0; i < datasetArray.Size(); i++)
    {
        auto pointArray = datasetArray[i].GetArray();
        dataset[i] = types::Complex{pointArray[0].GetDouble(), pointArray[1].GetDouble()};
    }
    return dataset;
}

bool almostEqual(const types::Complex& var1, const types::Complex& var2, double threshold)
{
    double realDif = std::abs(var1.real - var2.real);
    double imagDif = std::abs(var1.imag - var2.imag);
    if (realDif > var1.real * threshold)
    {
        std::cout << "Variables real parts don't equal. Var1: " << var1.real << ", var2: " << var2.real
                  << ", difference: " << realDif << std::endl;
    }

    if (imagDif > threshold)
    {
        std::cout << "Variables imag parts don't equal. Var1: " << var1.imag << ", var2: " << var2.imag
                  << ", difference: " << imagDif << std::endl;
    }
    return realDif < threshold && imagDif < threshold;
}

} // namespace test
