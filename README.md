# CSE 687 Project #1 - Single-User Test Harness
Travis CI Build Status: [![Build Status](https://travis-ci.com/archerc56/CSE687_OOD.svg?branch=master)](https://travis-ci.com/archerc56/CSE687_OOD)

The Travis build compiles the repo using both the g++ and clang compilers

Execution Output: 

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

