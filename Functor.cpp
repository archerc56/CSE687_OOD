/**************************************************************************************************************************
CIS 687 Object Oriented Design Monday 9 PM

Authors:		Cade Archer, Micheal Cheng, Sameer Rizvi, Bryan Ulrich
File:			Functor.cpp
Contents:		Class Definition(Functor)
Description:	This file contains the class definition for the Functor class

Last Updated:	10/18/2019 9:11 AM
//**************************************************************************************************************************/
/***************************************************************************************************************************
Notes:
//**************************************************************************************************************************/
#include "Functor.h"
inline
void Functor::operator()() const //overload operator() and return boolean
{
    std::cout << "Functor Test" << std::endl;
}