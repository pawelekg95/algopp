#pragma once

#include "calgopp/types/Point.h"

namespace calgopp::types {

/**
 * Peak type.
 */
enum class PeakType
{
    eLow,
    eHigh
};

/**
 * Peak representation
 */
struct Peak : public Point
{
    /**
     * Default constructor.
     */
    Peak() = default;

    /**
     * Constructs peak from same numeric type of arguents
     * @tparam T                    Type of input arguments.
     * @param x                     X axis value.
     * @param y                     Y axis value.
     */
    template <typename T>
    Peak(T x, T y)
        : Point(x, y)
    {
    }

    /**
     * Constructs peak from same numeric type of arguments and specified peak type.
     * @tparam T                    Type of input arguments.
     * @param x                     X axis value.
     * @param y                     Y axis value.
     * @param type                  Peak type.
     */
    template <typename T>
    Peak(T x, T y, PeakType type)
        : Point(x, y)
        , type(type)
    {
    }

    /**
     * Constructs peak from different numeric types of arguments.
     * @tparam T                    First numeric type
     * @tparam Y                    Second numeric type
     * @param x                     X axis value.
     * @param y                     Y axis value.
     */
    template <typename T, typename Y>
    Peak(T x, Y y)
        : Point(x, y)
    {
    }

    /**
     * Constructs peak from different numeric types of arguments and specified peak type.
     * @tparam T                    First numeric type
     * @tparam Y                    Second numeric type
     * @param x                     X axis value.
     * @param y                     Y axis value.
     * @param type                  Peak type.
     */
    template <typename T, typename Y>
    Peak(T x, Y y, PeakType type)
        : Point(x, y)
        , type(type)
    {
    }

    PeakType type{PeakType::eHigh};
};

/**
 * Equality operator for lvalue reference.
 * @param lhs                       Left hand object.
 * @param rhs                       Right hand object.
 * @return True if peaks equal, false otherwise.
 */
bool operator==(const Peak& lhs, const Peak& rhs);

/**
 * Equality operator for rvalue reference.
 * @param lhs                       Left hand object.
 * @param rhs                       Right hand object.
 * @return True if peaks equal, false otherwise.
 */
bool operator==(const Peak&& lhs, const Peak&& rhs);

/**
 * Inequality operator for lvalue reference.
 * @param lhs                       Left hand object.
 * @param rhs                       Right hand object.
 * @return True if peaks are not equal, false otherwise.
 */
bool operator!=(const Peak& lhs, const Peak& rhs);

/**
 * Inequality operator for rvalue reference.
 * @param lhs                       Left hand object.
 * @param rhs                       Right hand object.
 * @return True if peaks are not equal, false otherwise.
 */
bool operator!=(const Peak&& lhs, const Peak&& rhs);

} // namespace calgopp::types
