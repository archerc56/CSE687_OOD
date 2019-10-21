# CSE 687 Project #2 - Local Test Harness
## Travis CI Build Status: [![Build Status](https://travis-ci.com/archerc56/CSE687_OOD.svg?branch=master)](https://travis-ci.com/archerc56/CSE687_OOD)
Compiles the project using both clang and g++ compilers

## Requirements:
1.	Shall be prepared using the latest version of Visual Studio, and written in the standard C++ programming language, using the standard C++ libraries.
2.	Shall use Visual Studio, Community Edition available at no cost.
3.	Shall provide packages for an Executive, TestHarness, Logger, and FileManager (if needed).
4.	Shall accept a TestRequest XML string defining one or more test elements by naming dynamic link libraries.
5.	Each test element shall contain a testDriver element and one or more testedCode elements.
6.	TestDrivers shall implement an ITest interface1 that declares a test method taking no arguments and returning a boolean value indicating test pass or failure.
7.	On receiving a TestRequest, the TestHarness shall parse the request, load the corresponding libraries, sequentially create instances of each TestDriver, and log pass-fail status of each test, along with a time-date stamp.
8.	Shall provide one or more TestRequests that conduct testing of at least three of your project packages.
9.	The Executive package shall provide processing to demonstrate that these requirements are met, by using facilities of the TestHarness.

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

