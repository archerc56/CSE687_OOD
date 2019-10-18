# CSE 687 Project #1 - Single-User Test Harness

## Team Members:
Cade Archer, Michael Cheng, Sameer Rizvi, Bryan Ulrich

## Travis CI Build Status: [![Build Status](https://travis-ci.com/archerc56/CSE687_OOD.svg?branch=Project-1-Turn-in)](https://travis-ci.com/archerc56/CSE687_OOD)
Compiles the project using both clang and g++ compilers

## [Project Requirements:](https://github.com/archerc56/CSE687_OOD/files/3745932/Project1.Requirements.docx)
1. Shall be written in the standard C++ programming language, using the standard C++ libraries. 
2. Shall provide a TestHarness class that defines an executor method, accepting any callable object that accepts no arguments2 and returns a bool predicate to indicate success or failure. 
3. The executor method Shall invoke a passed callable object in the scope of a try block. If exceptions are thrown, the catch block you define for this method shall log test failure and the contents of the exception message. 
4. Shall support linking any number of callable objects for execution, and shall provide a mechanism for executing that sequence. 
5. Shall provide a multi-level logging mechanism, intended to show: 
o	just pass-fail status
o	application specific messages for pass and fail, along with the result
o	detailed debugging output that includes, on failure, values of application specific variables, and an optional time-date stamp
6. Shall provide a sequence of tests demonstrating all the features of your TestHarness. 


## Execution Output: 

```
**Running tests at high log level

Running Tests:
TestBadAlloc
TestBadCast
TestBadTypeID
TestBadWeakPtr
TestBadFunctionCall
TestBadException
TestAdd
TestAllocate
Functor Test

Test Results:
Test #1 failed. Test failure message: bad allocation. Test run time: 0.000912ms.
Test #2 failed. Test failure message: Bad dynamic_cast!. Test run time: 0.000921ms.
Test #3 failed. Test failure message: Attempted a typeid of nullptr pointer!. Test run time: 0.000922ms.
Test #4 failed. Test failure message: bad_weak_ptr. Test run time: 0.000923ms.
Test #5 failed. Test failure message: bad function call. Test run time: 0.000925ms.
Test #6 failed. Test failure message: Error. Test run time: 0.000926ms.
Test #7 passed. Test run time: 0.000926ms.
Test #8 passed. Test run time: 0.000926ms.
Test #9 passed. Test run time: 0.000926ms.
**Restting test suite

**Running tests at medium log level

Running Tests:
TestBadAlloc
TestBadCast
TestBadTypeID
TestBadWeakPtr
TestBadFunctionCall
TestBadException
TestAdd
TestAllocate
Functor Test

Test Results:
Test #1 failed. Test failure message: bad allocation.
Test #2 failed. Test failure message: Bad dynamic_cast!.
Test #3 failed. Test failure message: Attempted a typeid of nullptr pointer!.
Test #4 failed. Test failure message: bad_weak_ptr.
Test #5 failed. Test failure message: bad function call.
Test #6 failed. Test failure message: Error.
Test #7 passed.
Test #8 passed.
Test #9 passed.
**Restting test suite

**Running tests at low log level

Running Tests:
TestBadAlloc
TestBadCast
TestBadTypeID
TestBadWeakPtr
TestBadFunctionCall
TestBadException
TestAdd
TestAllocate
Functor Test

Test Results:
Test #1 failed.
Test #2 failed.
Test #3 failed.
Test #4 failed.
Test #5 failed.
Test #6 failed.
Test #7 passed.
Test #8 passed.
Test #9 passed.
**Restting test suite
```
