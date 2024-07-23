#define CL_HPP_TARGET_OPENCL_VERSION 210
#define CL_HPP_ENABLE_EXCEPTIONS

#include "calgopp/gpu/Proxy.h"
#include "calgopp/signal/transform/FourierTransform.h"

#include <CL/cl2.hpp>

#include <array>
#include <string>

namespace {

const std::string cTransformId = "fourierTransform";

const std::string cFourierTransform = {
    R"CLC(
    void fourierSum(global float* reals, global float* imags, float* realResult, float* imagResult, std::int32_t k, std::int32_t N)
    {
        float tokenReal = 0;
        float tokenImag = 0;
        for (std::uint32_t n = 0; n < N; n++)
        {
            float arg = (float)(2.0) * (float)(3.14159265358979323846) * k * n / N;
            float real = cos(arg);
            float imag = -sin(arg);
            tokenReal += reals[n] * real + imags[n] * imag;
            tokenImag += reals[n] * imag + imags[n] * real;
        }
        *realResult = tokenReal;
        *imagResult = tokenImag;
    }

    kernel void )CLC" +
    cTransformId +
    R"CLC((global float* reals, global float* imags, global float* resultReals, global float* resultImags, std::uint32_t size)
    {
        std::int32_t index = get_global_id(0);
        float imag = 0;
        float real = 0;
        fourierSum(reals, imags, &real, &imag, index, size);
        resultReals[index] = real;
        resultImags[index] = imag;

    })CLC"};

} // namespace

namespace calgopp::signal::transform {

class GpuFunctions
{
public:
    GpuFunctions() { calgopp::gpu::Proxy::registerFunction(cTransformId, cFourierTransform); }

    std::array<calgopp::gpu::Result<float[]>, 2>
    transform(float valuesReal[], float valuesImag[], std::uint32_t size) const
    {
        auto& proxy = calgopp::gpu::Proxy::get();
        auto context = proxy.getContext();
        auto queue = proxy.getCommandQueue();

        cl::Buffer realsBuf(*context, CL_MEM_COPY_HOST_PTR | CL_MEM_READ_ONLY, sizeof(float) * size, valuesReal);
        cl::Buffer imagsBuf(*context, CL_MEM_COPY_HOST_PTR | CL_MEM_READ_ONLY, sizeof(float) * size, valuesImag);

        auto resultRealsBuf =
            std::make_shared<cl::Buffer>(*context,
                                         CL_MEM_WRITE_ONLY | CL_MEM_HOST_READ_ONLY | CL_MEM_ALLOC_HOST_PTR,
                                         sizeof(float) * size);
        auto resultImagsBuf =
            std::make_shared<cl::Buffer>(*context,
                                         CL_MEM_WRITE_ONLY | CL_MEM_HOST_READ_ONLY | CL_MEM_ALLOC_HOST_PTR,
                                         sizeof(float) * size);

        auto functionPtr = proxy.getFunction(cTransformId);

        functionPtr->setArg(0, realsBuf);
        functionPtr->setArg(1, imagsBuf);
        functionPtr->setArg(2, *resultRealsBuf);
        functionPtr->setArg(3, *resultImagsBuf);
        functionPtr->setArg(4, cl_uint(size));

        auto event = std::make_shared<cl::Event>();

        queue->enqueueNDRangeKernel(*functionPtr, cl::NullRange, size, cl::NullRange, {}, event.get());

        std::array<calgopp::gpu::Result<float[]>, 2> result{
            calgopp::gpu::Result<float[]>{queue, resultRealsBuf, event, size},
            calgopp::gpu::Result<float[]>{queue, resultImagsBuf, event, size}};

        return result;
    }
};

const GpuFunctions gpuFunctions;

Signal FourierTransform::process(const Signal& signal)
{
    auto size = signal.size();
    float reals[size];
    float imags[size];
    for (std::uint32_t i = 0; i < size; i++)
    {
        auto elem = signal.get(i);
        reals[i] = float(elem.y.real);
        imags[i] = float(elem.y.imag);
    }

    auto result = gpuFunctions.transform(reals, imags, size);
    result[0].get(reals);
    result[1].get(imags);
    return {reals, imags, size};
}

} // namespace calgopp::signal::transform
