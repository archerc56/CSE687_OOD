#include "Functor.h"

bool Functor::operator()() const
{
    std::cout << "test" << std::endl;
    return true;
}