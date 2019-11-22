# CSE 687 Project #3 - Server Process Pools

## Team Members:
Cade Archer, Michael Cheng, Sameer Rizvi, Bryan Ulrich

## Project Requirements
1.	Shall be prepared using the latest version of Visual Studio, and written in the standard C++ programming language, using the standard C++ libraries.
2.	Shall implement a message-passing communication channel using Sockets, based on the Channel prototype found in the Repository.
3.	Shall define a Message class that provides:
    	Source and Destination addresses
      Message type
	    Author
	    Time-Date
	    String body:
      Expected to hold an XML string supplying information needed to execute a specific request.
4.	Shall define methods for sending and processing messages.
5.	Each communication EndPoint1 shall provide both a Sender and a Receiver, wrapped in a Comm class2.
6.	Shall provide a TestHarness Package that creates, at startup, a specified number of child processes. The child processes post Ready       messages to the TestHarness on startup.
7.	Shall provide a Client package that posts one or more TestRequest messages to the TestHarness. You will find it convenient to have the     TestHarness provide a BlockingQueue for TestRequests and a BlockingQueue for Ready messages. It uses a child thread to extract             messages from its Comm using getMessage(), and enqueue the message in the appropriate queue. The main TestHarness thread dequeues         these and sends the test request to the child tester that sent the Ready message3.
8.	Shall program the Executive to provide several TestRequests in quick succession to demonstrate that the process pool executes             TestRequests concurrently and that each will, on completion, post a Ready status message to the TestHarness and await the next             TestRequest message.
9.	Shall log test results, demonstrating that the requirements, above, are met.


## Execution Output: 
To test our application, we create the server and two clients. Each client runs their own set of tests defined in test1.xml and test2.xml (In the ExecutionServer folder). Client 1, listed as localhost:9891, will run the TestAdd, TestAllocate, TestBadWeakPtr test DLLs. Client 2, listed as localhost:9892, will run the TestBadFunctionCall and TestBadWeakPtr test DLLs. 

```
Executing localhost:9892's tests

Executing localhost:9891's tests

-------------------------------------------------------
 Thread ID 10252
TestBadFunctionCall
-------------------------------------------------------
 Thread ID 1332
TestBadWeakPtr
Test #1 failed. Test failure message: bad function call. Test run time: 0.000165ms.
Test #2 failed. Test failure message: bad_weak_ptr. Test run time: 0.000168ms.

Library at mem Location 79680000 Freed
Library at mem Location 79650000 Freed


-------------------------------------------------------
 Thread ID 12348
TestAdd
-------------------------------------------------------
 Thread ID 17748
TestAllocate
-------------------------------------------------------
 Thread ID 16524
TestBadWeakPtr
Test #1 passed. Test run time: 0.000207ms.
Test #2 passed. Test run time: 0.000208ms.
Test #3 failed. Test failure message: bad_weak_ptr. Test run time: 0.000215ms.

Library at mem Location 795F0000 Freed
Library at mem Location 79620000 Freed
Library at mem Location 79650000 Freed

```
