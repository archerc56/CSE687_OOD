#include "Functor.h"
inline
bool Functor::operator()() const
{
    std::cout << "test" << std::endl;
}