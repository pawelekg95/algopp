#pragma once

#define CL_HPP_TARGET_OPENCL_VERSION 210
#define CL_HPP_ENABLE_EXCEPTIONS

#include <CL/cl2.hpp>

#include <cstdint>
#include <map>
#include <memory>
#include <string>

namespace calgopp {
namespace gpu {

template <typename T>
class Result
{
public:
    Result(std::shared_ptr<cl::CommandQueue> commandQueue,
           std::shared_ptr<cl::Buffer> buffer,
           std::shared_ptr<cl::Event> event,
           std::uint32_t size = sizeof(T))
        : m_commandQueue(std::move(commandQueue))
        , m_buffer(std::move(buffer))
        , m_event(std::move(event))
        , m_bufferSize(size)
    {}

    void get(T* result)
    {
        if (m_event->wait() != 0)
        {
            throw "Failed to finish event";
        }
        if (m_commandQueue->enqueueReadBuffer(*m_buffer, CL_TRUE, 0, m_bufferSize, result) != 0)
        {
            throw "Failed to read from device";
        }
    }

    void get(T result)
    {
        if (m_event->wait() != 0)
        {
            throw "Failed to finish event";
        }
        if (m_commandQueue->enqueueReadBuffer(*m_buffer, CL_TRUE, 0, m_bufferSize, result) != 0)
        {
            throw "Failed to read from device";
        }
    }

private:
    std::shared_ptr<cl::CommandQueue> m_commandQueue{};
    std::shared_ptr<cl::Buffer> m_buffer{};
    std::shared_ptr<cl::Event> m_event{};
    std::uint32_t m_bufferSize;
};

class Proxy
{
public:
    static Proxy& get();

    static void registerFunction(const std::string& id, const std::string& function);

    std::shared_ptr<cl::Kernel> getFunction(const std::string& id);

    std::shared_ptr<cl::Context> getContext() { return m_context; }

    std::shared_ptr<cl::CommandQueue> getCommandQueue() { return m_commandQueue; }

private:
    Proxy();
    Proxy(const Proxy& other) = default;
    Proxy(Proxy&& other) = default;

    Proxy& operator=(const Proxy& other) = default;
    Proxy& operator=(Proxy&& other) = default;
    ~Proxy() = default;

private:
    std::shared_ptr<cl::Context> m_context{};
    static inline cl::Program::Sources m_sources;
    std::shared_ptr<cl::CommandQueue> m_commandQueue{};
    std::shared_ptr<cl::Program> m_program{};
    static inline std::map<std::string, std::shared_ptr<cl::Kernel>> m_functions;
};

} // namespace gpu
} // namespace calgopp
