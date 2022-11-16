#pragma once

#include "calgopp/types/Container.h"

namespace calgopp::algorithm::numeric {

template <typename Type, typename It>
It findElement(It begin, It end, bool (*comparator)(const Type& elem1, const Type& elem2))
{
    auto current = begin;
    while (begin < end - 1)
    {
        if (comparator(*begin, *(begin + 1)))
        {
            current = begin;
        }
        begin++;
    }
    return current;
}

template <typename Type, typename It>
It minElement(It begin, It end)
{
    return findElement<Type, It>(begin, end, [](const Type& first, const Type& second) -> bool {
        return first <= second;
    });
}

template <typename Type, typename It>
It maxElement(It begin, It end)
{
    return findElement<Type, It>(begin, end, [](const Type& first, const Type& second) -> bool {
        return first >= second;
    });
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

} // namespace calgopp::algorithm::numeric
