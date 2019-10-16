//Created: October 11, 2019 @ 11:53 PM Central Time
#ifndef FUNCTORS_H
#define FUNCTORS_H
#include <iostream>
class Functor //this is a functor which is a class that overloads operator()
{
        public:
        inline
        bool operator()() const; //overloading function call operator (operator())
};
#endif