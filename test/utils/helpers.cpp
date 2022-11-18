#include "test/utils/helpers.h"

#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>

#include <fstream>
#include <cstdlib>
#include <string>

namespace test {

int testDataset(const std::string& scriptPath,
                const std::string& outputPath,
                std::uint32_t size,
                double height,
                double distance,
                types::PeakType type)
{
    std::string command = scriptPath + " -p " + outputPath + " -s " + std::to_string(size) + " --height " +
                          std::to_string(height) + " -d " + std::to_string(distance) + " -t " +
                          (type == calgopp::types::PeakType::eHigh ? "high" : "low");
    return system(command.c_str()); // NOLINT cert-env33-c
}

std::vector<calgopp::types::Point> getRawDataset(const std::string& datasetPath)
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

std::vector<calgopp::types::Peak> getPeaks(const std::string& datasetPath)
{
    std::ifstream file(datasetPath);
    rapidjson::IStreamWrapper stream(file);
    rapidjson::Document parsedConfig;
    parsedConfig.ParseStream(stream);
    assert(!parsedConfig.HasParseError());

    auto datasetArray = parsedConfig.GetObject()["peaks"].GetArray();
    std::vector<calgopp::types::Peak> dataset(datasetArray.Size());
    for (std::uint32_t i = 0; i < datasetArray.Size(); i++)
    {
        auto pointArray = datasetArray[i].GetArray();
        dataset[i] = types::Peak{pointArray[0].GetInt(), pointArray[1].GetFloat()};
    }
    return dataset;
}

} // namespace test
