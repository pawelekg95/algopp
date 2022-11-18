#pragma once

#include "calgopp/types/Container.h"

namespace calgopp::algorithm::numeric {

const long double cEpsilon = 0.0000000001;

struct LessComparator
{
    template <typename Type>
    bool operator()(const Type& lhs, const Type& rhs)
    {
        return lhs < rhs;
    }
};

struct GreaterComparator
{
    template <typename Type>
    bool operator()(const Type& lhs, const Type& rhs)
    {
        return lhs > rhs;
    }
};

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

template <typename It>
It minElement(It begin, It end)
{
    return findElement(begin, end, LessComparator());
}

template <typename It>
It maxElement(It begin, It end)
{
    return findElement(begin, end, GreaterComparator());
}

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

template <typename Type>
Type abs(const Type& number)
{
    return number < 0 ? -number : number;
}

template <typename Type>
Type min()
{}

} // namespace calgopp::algorithm::numeric
