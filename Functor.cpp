#include "Functor.h"
inline
void Functor::operator()() const //overload operator() and return boolean
{
    std::cout << "Functor Test" << std::endl;
}