#define CL_HPP_TARGET_OPENCL_VERSION 210
#define CL_HPP_ENABLE_EXCEPTIONS
#include "calgopp/math/math.h"
#include "calgopp/gpu/Proxy.h"

#include <CL/cl2.hpp>

#include <string>
#include <memory>
#include <chrono>
#include <iostream>

namespace {

const std::string cPowerFunctionId = "mathPow";
const std::string cRootFunctionId = "mathRoot";

const std::string cPowGPU = {R"CLC(
    kernel void )CLC" + cPowerFunctionId + R"CLC((global float* number, global int* power, global float* ret)
    {
         unsigned int absPower = (*power) < 0 ? -(*power) : (*power);
         if (absPower == 0)
         {
             *ret = (float)(1);
             return;
         }
         if (absPower == 1)
         {
             *ret = (*power) < 0 ? (float)(1) / (float)(*number) : (float)(*number);
             return;
         }
         float token = *number;
         while (absPower > 1)
         {
             token = token * (float)(*number);
             absPower--;
         }

         *ret = (*power) < 0 ? (float)(1) / token : token;
    })CLC"};

const std::string cRootGPU = {R"CLC(
    __constant float cMultiplier = (float)(0.5);

    float abs(float number)
    {
        return number < 0 ? -number : number;
    }

    float multiplication(float currentNumber, unsigned int base)
    {
        float token = currentNumber;
        for (unsigned int i = 1; i < base; i++)
        {
            token = token * currentNumber;
        }
        return token;
    }

    void increase(float* token, const float threshold, float step, int* maxSpins, float precision, int base)
    {
        while (multiplication(*token, base) - threshold < precision)
        {
            if (*maxSpins < 0)
            {
                break;
            }
            *token += step;
            (*maxSpins)--;
        }
    };

    void decrease(float* token, const float threshold, float step, int* maxSpins, float precision, int base)
    {
        while (multiplication(*token, base) - threshold > precision)
        {
            if (*maxSpins < 0)
            {
                break;
            }
            *token -= step;
            (*maxSpins)--;
        }
    };


    kernel void )CLC" + cRootFunctionId + R"CLC((global float* number, global int* base, global float* ret, global float* epsilon)
    {
        float precision = *epsilon / (float)(10000.0);
        int maxSpins = 10000;

        float token = *epsilon;
        float jump = cMultiplier * (*number);

        while (abs(multiplication(token, *base) - *number) > precision)
        {
            if (maxSpins < 0)
            {
                break;
            }
            float multiplied = multiplication(token, *base);
            if (multiplied - *number > precision)
            {
                jump = jump * cMultiplier;
                decrease(&token, *number, jump, &maxSpins, precision, *base);
            }
            else if (multiplied - *number < precision)
            {
                jump = jump * cMultiplier;
                increase(&token, *number, jump, &maxSpins, precision, *base);
            }
            maxSpins--;
        }
        *ret = token;
    })CLC"};

class GpuFunctions
{
public:
    GpuFunctions()
    {
        calgopp::gpu::Proxy::registerFunction(cPowerFunctionId, cPowGPU);
        calgopp::gpu::Proxy::registerFunction(cRootFunctionId, cRootGPU);
    }

    calgopp::gpu::Result<float> pow(float number, int power) const
    {
        auto& proxy = calgopp::gpu::Proxy::get();

        auto context = proxy.getContext();
        auto queue = proxy.getCommandQueue();
        calgopp::gpu::Timer timer;
        timer.start();

        static cl::Buffer numberBuf(*context,  CL_MEM_USE_HOST_PTR, sizeof(float), &number);
        static cl::Buffer powerBuf(*context, CL_MEM_USE_HOST_PTR, sizeof(int), &power);
        static auto resultBuf = std::make_shared<cl::Buffer>(*context, CL_MEM_READ_WRITE, sizeof(float));

        queue->enqueueWriteBuffer(numberBuf, CL_TRUE, 0, sizeof(float), &number);
        queue->enqueueWriteBuffer(powerBuf, CL_TRUE, 0, sizeof(int), &power);

        timer.stop("Buffers allocating");

        auto functionPtr = proxy.getFunction(cPowerFunctionId);

        timer.start();
        functionPtr->setArg(0, numberBuf);
        functionPtr->setArg(1, powerBuf);
        functionPtr->setArg(2, *resultBuf);
        timer.stop("Setting arguments");

        auto event = std::make_shared<cl::Event>();

        timer.start();
        queue->enqueueNDRangeKernel(*functionPtr, cl::NullRange, cl::NullRange, cl::NullRange, {}, event.get());
        timer.stop("Enqueueing");

        return {queue, resultBuf, event};
    }

    calgopp::gpu::Result<float> root(float number, int base, float epsilon) const
    {
        auto& proxy = calgopp::gpu::Proxy::get();
        auto context = proxy.getContext();
        cl::Buffer numberBuf(*context, CL_MEM_HOST_WRITE_ONLY | CL_MEM_USE_HOST_PTR, sizeof(float), &number);
        cl::Buffer epsilonBuf(*context, CL_MEM_HOST_WRITE_ONLY | CL_MEM_USE_HOST_PTR, sizeof(float), &epsilon);
        cl::Buffer baseBuf(*context, CL_MEM_HOST_WRITE_ONLY | CL_MEM_USE_HOST_PTR, sizeof(int), &base);
        auto resultBuf = std::make_shared<cl::Buffer>(*context, CL_MEM_READ_WRITE, sizeof(float));

        auto functionPtr = proxy.getFunction(cRootFunctionId);

        functionPtr->setArg(0, numberBuf);
        functionPtr->setArg(1, baseBuf);
        functionPtr->setArg(2, *resultBuf);
        functionPtr->setArg(3, epsilonBuf);

        auto event = std::make_shared<cl::Event>();

        auto queue = proxy.getCommandQueue();

        queue->enqueueNDRangeKernel(*functionPtr, cl::NullRange, cl::NullRange, cl::NullRange, {}, event.get());

        return {queue, resultBuf, event};
    }
};

const GpuFunctions gpuFunctions;

} // namespace

namespace calgopp {
namespace math {

Fraction::Fraction(long double num)
{
    long double integral = floor(num);
    long double frac = num - integral;

    const int precision = 10000;

    int commonDivisor = gcd(int(round(frac * precision)), precision);

    m_denominator = precision / commonDivisor;
    m_numerator = int(round(frac * precision) / commonDivisor);
}

int gcd(int a, int b)
{
    if (a == 0)
    {
        return b;
    }
    if (b == 0)
    {
        return a;
    }
    return a < b ? gcd(a, b % a) : gcd(b, a % b);
}

double root(int number, unsigned int base)
{
    return root(static_cast<double>(number), static_cast<int>(base));
}

double root(long int number, unsigned int base)
{
    return root(static_cast<double>(number), static_cast<int>(base));
}

double root(double number, unsigned int base)
{
    return root(static_cast<double>(number), static_cast<int>(base));
}

double root(int number, int base)
{
    return root(static_cast<double>(number), base);
}

double root(long int number, int base)
{
    return root(static_cast<double>(number), base);
}

double root(double number, int base)
{
    double precision = epsilon() / 10000.0;
    auto multiplication = [](double currentNumber, unsigned int base) {
        double token{currentNumber};
        for (unsigned int i = 1; i < base; i++)
        {
            token = token * currentNumber;
        }
        return token;
    };
    const double cMultiplier = 0.5;
    int maxSpins = 10000;

    auto increase =
            [&multiplication, &base, &precision, &maxSpins](double& token, const double& threshold, double& step) {
                while (multiplication(token, base) - threshold < precision)
                {
                    if (maxSpins < 0)
                    {
                        break;
                    }
                    token += step;
                    maxSpins--;
                }
            };

    auto decrease =
            [&multiplication, &base, &precision, &maxSpins](double& token, const double& threshold, double& step) {
                while (multiplication(token, base) - threshold > precision)
                {
                    if (maxSpins < 0)
                    {
                        break;
                    }
                    token -= step;
                    maxSpins--;
                }
            };

    double token = epsilon();
    double jump = cMultiplier * number;

    while (abs(multiplication(token, base) - number) > precision)
    {
        if (maxSpins < 0)
        {
            break;
        }
        auto multiplied = multiplication(token, base);
        if (multiplied - number > precision)
        {
            jump = jump * cMultiplier;
            decrease(token, number, jump);
        }
        else if (multiplied - number < precision)
        {
            jump = jump * cMultiplier;
            increase(token, number, jump);
        }
        maxSpins--;
    }
    return token;
}

double pow(int number, unsigned int power)
{
    return pow(static_cast<double>(number), static_cast<int>(power));
}

double pow(long int number, unsigned int power)
{
    return pow(static_cast<double>(number), static_cast<int>(power));
}

double pow(double number, unsigned int power)
{
    return pow(static_cast<double>(number), static_cast<int>(power));
}

double pow(int number, int power)
{
    return pow(static_cast<double>(number), power);
}

double pow(long int number, int power)
{
    return pow(static_cast<double>(number), power);
}

double pow(double number, int power)
{
    unsigned int absPower = abs(power);
    if (power == 0)
    {
        return 1;
    }
    if (absPower == 1)
    {
        return power < 0 ? 1.0 / double(number) : double(number);
    }
    double token = number;
    while (absPower > 1)
    {
        token = token * double(number);
        absPower--;
    }

    return power < 0 ? 1.0 / token : token;
}

double pow(int number, double power)
{
    return pow(static_cast<double>(number), power);
}

double pow(long int number, double power)
{
    return pow(static_cast<double>(number), power);
}

double pow(double number, double power)
{
    Fraction pwrFraction(power);
    if (power < 0 && int(power) % 2 == 0 && !pwrFraction)
    {
        return pow(number, abs(power));
    }
    if (power < 0 && int(power) % 2 == 1 && !pwrFraction)
    {
        return -pow(number, abs(power));
    }

    auto rootInputResult = gpuFunctions.pow(float(number), pwrFraction.numerator());
    auto basePowResult = gpuFunctions.pow(float(number), int(floor(power)));

    float rootInput{};
    rootInputResult.get(&rootInput);

    auto fractionPowResult = gpuFunctions.root(rootInput, pwrFraction.denominator(), float(epsilon()));

    float basePow{};
    float fractionPow{};

    basePowResult.get(&basePow);
    fractionPowResult.get(&fractionPow);

    return double(basePow) * double(fractionPow);
}

} // namespace math
} // namespace calgopp
