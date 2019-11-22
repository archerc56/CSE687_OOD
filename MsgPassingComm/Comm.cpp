#include "Comm.h"
#include "../Logger/Logger.h"
#include "../Utilities/Utilities.h"
#include "../ExecutionServer/Executive.cpp"
#include "../ExecutionServer/ThreadPool.cpp"
#include "../Cpp11-BlockingQueue/Cpp11-BlockingQueue.h"
#include <iostream>
#include <functional>
#include <conio.h>


using namespace MsgPassingCommunication;
using namespace Sockets;
using SUtils = Utilities::StringHelper;
void testRequest(std::string);

void printThreadID();

Executive e;
int totalRequests = 3;
int threadRequestCount = 1;
std::mutex mux;

//----< constructor sets port >--------------------------------------

Receiver::Receiver(EndPoint ep, const std::string& name) : listener(ep.port), rcvrName(name)
{
  StaticLogger<1>::write("\n  -- starting Receiver");
}
//----< returns reference to receive queue >-------------------------

BlockingQueue<Message>* Receiver::queue()
{
  return &rcvQ;
}
//----< starts listener thread running callable object >-------------

template<typename CallableObject>
void Receiver::start(CallableObject& co)
{
  listener.start(co);
}
//----< stops listener thread >--------------------------------------

void Receiver::stop()
{
  listener.stop();
}
//----< retrieves received message >---------------------------------

Message Receiver::getMessage()
{
  StaticLogger<1>::write("\n  -- " + rcvrName + " deQing message");
  return rcvQ.deQ();
}
//----< constructor initializes endpoint object >--------------------

Sender::Sender(const std::string& name) : sndrName(name)
{
  lastEP = EndPoint();  // used to detect change in destination
}
//----< destructor waits for send thread to terminate >--------------

Sender::~Sender()
{
  if (sendThread.joinable())
    sendThread.join();
}
//----< starts send thread deQ, inspect, and send loop >-------------

void Sender::start()
{
  std::function <void()> threadProc = [&]() {
    while (true)
    {
      Message msg = sndQ.deQ();

      if (msg.command() == "quit")
      {
        StaticLogger<1>::write("\n  -- send thread shutting down");
        return;
      }
      StaticLogger<1>::write("\n  -- " + sndrName + " send thread sending " + msg.name());
      std::string msgStr = msg.toString();

      if (msg.to().address != lastEP.address || msg.to().port != lastEP.port)
      {
        connecter.shutDown();
        //connecter.close();
        StaticLogger<1>::write("\n  -- attempting to connect to new endpoint: " + msg.to().toString());
        if (!connect(msg.to()))
        {
          StaticLogger<1>::write("\n can't connect");
          continue;
        }
        else
        {
          StaticLogger<1>::write("\n  connected to " + msg.to().toString());
        }
      }
      bool sendRslt = connecter.send(msgStr.length(), (Socket::byte*)msgStr.c_str());
    }
  };
  std::thread t(threadProc);
  sendThread = std::move(t);
}
//----< stops send thread by posting quit message >------------------

void Sender::stop()
{
  Message msg;
  msg.name("quit");
  msg.command("quit");
  postMessage(msg);
  connecter.shutDown();
}
//----< attempts to connect to endpoint ep >-------------------------

bool Sender::connect(EndPoint ep)
{
  lastEP = ep;
  return connecter.connect(ep.address, ep.port);
}
//----< posts message to send queue >--------------------------------

void Sender::postMessage(Message msg)
{
  sndQ.enQ(msg);
}
//----< sends binary file >------------------------------------------
/*
*  - not implemented yet
*/
bool Sender::sendFile(const std::string& fileName)
{
  return false;
}
//----< callable object posts incoming message to rcvQ >-------------
/*
*  This is ClientHandler for receiving messages and posting
*  to the receive queue.
*/
class ClientHandler
{
public:
  //----< acquire reference to shared rcvQ >-------------------------

  ClientHandler(BlockingQueue<Message>* pQ, const std::string& name = "clientHandler") : pQ_(pQ), clientHandlerName(name)
  {
    StaticLogger<1>::write("\n  -- starting ClientHandler");
  }
  //----< shutdown message >-----------------------------------------

  ~ClientHandler() 
  { 
    StaticLogger<1>::write("\n  -- ClientHandler destroyed;"); 
  }
  //----< set BlockingQueue >----------------------------------------

  void setQueue(BlockingQueue<Message>* pQ)
  {
    pQ_ = pQ;
  }
  //----< frame message string by reading bytes from socket >--------

  std::string readMsg(Socket& socket)
  {
    std::string temp, msgString;
    while (socket.validState())
    {
      temp = socket.recvString('\n');  // read attribute
      msgString += temp;
      if (temp.length() < 2)           // if empty line we are done
        break;
    }
    return msgString;
  }
  //----< reads messages from socket and enQs in rcvQ >--------------

  void operator()(Socket socket)
  {
    while (socket.validState())
    {
      std::string msgString = readMsg(socket);
      if (msgString.length() == 0)
      {
        // invalid message
        break;
      }
      Message msg = Message::fromString(msgString);
      StaticLogger<1>::write("\n  -- " + clientHandlerName + " RecvThread read message: " + msg.name());
      pQ_->enQ(msg);
      if (msg.command() == "quit")
        break;
    }
    StaticLogger<1>::write("\n  -- terminating ClientHandler thread");
  }
private:
  BlockingQueue<Message>* pQ_;
  std::string clientHandlerName;
};

Comm::Comm(EndPoint ep, const std::string& name) : rcvr(ep, name), sndr(name), commName(name) {}

void Comm::start()
{
  BlockingQueue<Message>* pQ = rcvr.queue();
  ClientHandler* pCh = new ClientHandler(pQ, commName);
  /*
    There is a trivial memory leak here.  
    This ClientHandler is a prototype used to make ClientHandler copies for each connection.
    Those are not created on the heap, and are destroyed when the connection closes.
    Only one Client handler prototype is created for each Comm object and will live until
    the end of the program.

    I will clean this up in the next version.
  */
  rcvr.start(*pCh);
  sndr.start();
}

void Comm::stop()
{
  rcvr.stop();
  sndr.stop();
}

void Comm::postMessage(Message msg)
{
  sndr.postMessage(msg);
}

Message Comm::getMessage()
{
  return rcvr.getMessage();
}

std::string Comm::name()
{
  return commName;
}

//----< test stub >--------------------------------------------------

#ifdef TEST_COMM
void ThreadProcClnt1()
{
  Comm comm(EndPoint("localhost", 9891), "client1Comm");
  comm.start();
  EndPoint serverEP("localhost", 9890);
  EndPoint clientEP("localhost", 9891);
  size_t IMax = 3;
  Message msg(serverEP, clientEP);
  msg.name("client #1 tests");
  msg.file("test1.xml");
  comm.postMessage(msg);

  Message rply = comm.getMessage();
  //::Sleep(200);
  Message stop;
  stop.name("stop");
  stop.to(serverEP);
  stop.command("stop");
  comm.postMessage(stop);
}

void ThreadProcClnt2()
{
	Comm comm(EndPoint("localhost", 9892), "client2Comm");
	comm.start();
	EndPoint serverEP("localhost", 9890);
	EndPoint clientEP("localhost", 9892);
	size_t IMax = 3;
	Message msg(serverEP, clientEP);
	msg.name("client #2 tests");
	msg.file("test2.xml");
	comm.postMessage(msg);
	Message rply = comm.getMessage();
	//::Sleep(200);
	Message stop;
	stop.name("stop");
	stop.to(serverEP);
	stop.command("stop");
	comm.postMessage(stop);
}

void testRequest(std::string request)
{
	std::unique_lock<std::mutex> lock{ mux };
	e.DLLharnessLoader(request);
	e.runHarness();
	e.displayTestResults();

	e.clearTestResults();

	e.clearHarness_andFreeDLL();

	totalRequests--;

	threadRequestCount++;
}
/*
* Server will take in XML messages, execute them, and then return the logged results
*
*/
void TestExecutorServer()
{
	EndPoint serverEP("localhost", 9890);
	Comm comm(serverEP, "serverComm");
	comm.start();
	Message msg, rply;
	rply.name("reply");
	size_t count = 0;
	ThreadPool tp(6);
	while (true)
	{
		msg = comm.getMessage();
		if (msg.command() != "stop") {
			std::cout << "Executing " + msg.from().toString() + "'s tests" << std::endl << std::endl;
		}
		tp.enqueue(std::bind(testRequest, msg.file()));
		rply.to(msg.from());
		rply.from(serverEP);
		comm.postMessage(rply);
		if (msg.command() == "stop")
		{
			break;
		}
	}
	comm.stop();
	StaticLogger<1>::flush();

}

Cosmetic cosmetic;

int main()
{
  StaticLogger<1>::attach(&std::cout);
  SocketSystem ss;

  EndPoint serverEP("localhost", 9890);
  EndPoint clientEP("localhost", 9891); 

  //Note: To fully show the of this tool, we would create separate exe's to run both threads
  //However to make testing faster, we've combined them all into a single exe

  
  std::thread t1(ThreadProcClnt1);
  t1.detach();

  std::thread t2(ThreadProcClnt2);
  t2.detach();

  //Start execution server
  TestExecutorServer();

  StaticLogger<1>::flush();

  return 0;
}
#endif
