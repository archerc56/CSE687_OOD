/**************************************************************************************************************************
CIS 687 Object Oriented Design Monday 9 PM

Authors:		Cade Archer, Micheal Cheng, Sameer Rizvi, Bryan Ulrich
File:			Functor.h
Contents:		Class Declaration(Functor)
Description:	This file contains a class Functor that implements the () to make this a callable
				object.  Functor is used to test our test harness.

Last Updated:	10/18/2019 9:08 AM
//**************************************************************************************************************************/
/***************************************************************************************************************************
Notes:
//**************************************************************************************************************************/
#ifndef FUNCTORS_H
#define FUNCTORS_H
#include <iostream>
class Functor //this is a functor which is a class that overloads operator()
{
        public:
        inline
        void operator()() const; //overload function call operator (operator())
};
#endif