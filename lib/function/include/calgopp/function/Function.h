#pragma once

#include "calgopp/types/Complex.h"

namespace calgopp::function {

template <typename Functor>
class Function
{
public:
    Function(Functor functor)
        : m_functor(functor)
    {}

    types::Complex operator()(double argument) { return m_functor(argument); }

protected:
    Functor m_functor;
};

} // namespace calgopp::function
