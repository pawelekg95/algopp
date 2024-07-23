#include "calgopp/approximation/approximation.h"

#include "calgopp/types/Point.h"

#include <etl/algorithm.h>

namespace calgopp::approximation {

function::LinearFunction leastSquares(const signal::Signal& signal)
{
    double sumX =
        etl::accumulate(signal.begin(), signal.end(), 0.0, [](double current, const types::Point& a) -> double {
            return current + static_cast<double>(a.x);
        });
    double sumY =
        etl::accumulate(signal.begin(), signal.end(), 0.0, [](double current, const types::Point& a) -> double {
            return current + static_cast<double>(a.y);
        });
    double sumXY =
        etl::accumulate(signal.begin(), signal.end(), 0.0, [](double current, const types::Point& a) -> double {
            return current + static_cast<double>(a.x * a.y);
        });
    double sumX2 =
        etl::accumulate(signal.begin(), signal.end(), 0.0, [](double current, const types::Point& a) -> double {
            return current + static_cast<double>(a.x * a.x);
        });

    double a = ((sumX * sumY) - signal.size() * sumXY) / ((sumX * sumX) - signal.size() * sumX2);
    double b = ((sumX * sumXY) - (sumY * sumX2)) / ((sumX * sumX) - signal.size() * sumX2);

    return {a, b};
}

} // namespace calgopp::approximation
