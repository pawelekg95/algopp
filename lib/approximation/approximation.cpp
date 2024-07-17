#include "calgopp/approximation/approximation.h"

#include "calgopp/algorithm/algorithm.h"
#include "calgopp/types/Point.h"

namespace calgopp::approximation {

function::LinearFunction leastSquares(signal::Signal& signal)
{
    double sumX = algorithm::numeric::sum(signal.begin(), signal.end(), 0.0, [](const types::Point& a) -> double {
        return double(a.x);
    });
    double sumY = algorithm::numeric::sum(signal.begin(), signal.end(), 0.0, [](const types::Point& a) -> double {
        return double(a.y);
    });
    double sumXY = algorithm::numeric::sum(signal.begin(), signal.end(), 0.0, [](const types::Point& a) -> double {
        return double(a.x * a.y);
    });
    double sumX2 = algorithm::numeric::sum(signal.begin(), signal.end(), 0.0, [](const types::Point& a) -> double {
        return double(a.x * a.x);
    });

    double a = ((sumX * sumY) - signal.size() * sumXY) / ((sumX * sumX) - signal.size() * sumX2);
    double b = ((sumX * sumXY) - (sumY * sumX2)) / ((sumX * sumX) - signal.size() * sumX2);

    return {a, b};
}

} // namespace calgopp::approximation
