#include "Functor.h"
inline
bool Functor::operator()() const //overload operator() and return boolean
{
    std::cout << "Running Functor that should successfully execute. " << std::endl;
    return true;
}