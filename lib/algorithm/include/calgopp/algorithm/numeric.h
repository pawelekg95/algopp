#pragma once

#include "calgopp/types/Container.h"

namespace calgopp::algorithm::numeric {

/**
 * Epsilon constant for floating point comparisons
 */
const long double cEpsilon = 0.0000000001;

/**
 * Functor object for default less comparator
 */
struct LessComparator
{
    /**
     * Function call operator.
     * Checks if first value is smaller than second
     * @tparam Type                     Type to of arguments to compare
     * @param lhs                       Left hand argument
     * @param rhs                       Right hand argument
     * @return True if first argument is less than second, false otherwise.
     */
    template <typename Type>
    bool operator()(const Type& lhs, const Type& rhs)
    {
        return lhs < rhs;
    }
};

/**
 * Functor object for default greater comparator
 */
struct GreaterComparator
{
    /**
     * Function call operator.
     * Checks if first value is greater than second
     * @tparam Type                     Type to of arguments to compare
     * @param lhs                       Left hand argument
     * @param rhs                       Right hand argument
     * @return True if first argument is greater than second, false otherwise.
     */
    template <typename Type>
    bool operator()(const Type& lhs, const Type& rhs)
    {
        return lhs > rhs;
    }
};

/**
 * Find element in container.
 * Use comparator object that has defined function call operator to compare items
 * @tparam It                           Type of container's iterator
 * @tparam Comparator                   Type of function object with comparing logic
 * @param begin                         Iterator to the beginning of container (or range)
 * @param end                           Iterator to the end of container (or range)
 * @param comparator                    Function object to compare items
 * @return Iterator to an item that fulfils comparison requirements
 */
template <typename It, typename Comparator>
It findElement(It begin, It end, Comparator comparator)
{
    auto current = begin;
    while (begin < end - 1)
    {
        if (comparator(*begin, *(current)))
        {
            current = begin;
        }
        begin++;
    }
    return current;
}

/**
 * findElement() function with LessComparator
 * @tparam It                           Type of container's iterator
 * @param begin                         Iterator to the beginning of container (or range)
 * @param end                           Iterator to the end of container (or range)
 * @return Smallest item in container (or range)
 */
template <typename It>
It minElement(It begin, It end)
{
    return findElement(begin, end, LessComparator());
}

/**
 * findElement() function with GreaterComparator
 * @tparam It                           Type of container's iterator
 * @param begin                         Iterator to the beginning of container (or range)
 * @param end                           Iterator to the end of container (or range)
 * @return Greatest item in container (or range)
 */
template <typename It>
It maxElement(It begin, It end)
{
    return findElement(begin, end, GreaterComparator());
}

/**
 * Generates container with numbers in range from begin to <end
 * @tparam Type                         Number type
 * @param begin                         Begin of range
 * @param end                           End of range
 * @return Container with numbers
 */
template <typename Type>
types::Container<Type> range(int begin, int end)
{
    if (begin >= end)
    {
        return {};
    }
    types::Container<Type> token;
    for (int i = begin; i < end; i++)
    {
        token.append(i);
    }
    return token;
}

/**
 * Absolute operator
 * @tparam Type                         Number type
 * @param number                        Argument
 * @return Absolute value of argument
 */
template <typename Type>
Type abs(const Type& number)
{
    return number < 0 ? -number : number;
}

template <typename Type>
Type min()
{}

} // namespace calgopp::algorithm::numeric
