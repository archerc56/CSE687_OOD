#include "Functor.h"
inline
bool Functor::operator()() const //overload operator() and return boolean
{
    std::cout << "test" << std::endl;
    return true;
}