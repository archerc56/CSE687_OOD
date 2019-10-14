# Makefile
# Specify what I need in the end. One single executable
divisonExecutable : main.o TestHarness.o
# Read this as divisionExecutable depends on main.o div.o
# But how is it produced??? Hmm...using the below statement
	g++ TestHarness.o div.o -o divisonExecutable 
# starts with tab, I repeat tab
#-----------------------------------------------------------------
# But main.o is not there? So specify how it is produced.
main.o : main.cpp TestHarness.h
	g++ -c main.cpp
# Same for test.o
TestHarness.o : TestHarness.cpp TestHarness.h
	g++ -c TestHarness.cpp
