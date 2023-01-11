#include "calgopp/gpu/Proxy.h"

namespace calgopp {
namespace gpu {

Proxy::Proxy()
{
    std::vector<cl::Platform> all_platforms;
    cl::Platform::get(&all_platforms);
    if (all_platforms.empty())
    {
        throw " No OpenCL platforms found.";
    }
    cl::Platform default_platform = all_platforms[0];
    std::vector<cl::Device> all_devices;
    default_platform.getDevices(CL_DEVICE_TYPE_ALL, &all_devices);
    if (all_devices.empty())
    {
        throw "No devices found.";
    }
    cl::Device default_device = all_devices[0];
    m_context = std::make_shared<cl::Context>(default_device);
    m_commandQueue = std::make_shared<cl::CommandQueue>(*m_context, default_device);

    m_program = std::make_shared<cl::Program>(*m_context, m_sources);

    m_program->build({default_device});

    for (auto& [functionId, functionPtr] : m_functions)
    {
        functionPtr = std::make_shared<cl::Kernel>(*m_program, functionId.c_str());
    }
}

Proxy& Proxy::get()
{
    static Proxy object;
    return object;
}

void Proxy::registerFunction(const std::string& id, const std::string& function)
{
    if (m_functions.find(id) != m_functions.end())
    {
        throw "Function already registered";
    }
    m_sources.push_back({function.c_str(), function.length()});
    m_functions[id] = nullptr;
}

std::shared_ptr<cl::Kernel> Proxy::getFunction(const std::string& id)
{
    if (m_functions.find(id) == m_functions.end())
    {
        throw "Function not found";
    }
    return m_functions[id];
}

} // namespace gpu
} // namespace calgopp