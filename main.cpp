#include "TestHarness.cpp"

bool test_Bad_Alloc();
void test_Bad_cast();
void test_Bad_exception();
void test_Bad_typeid();
void test_Bad_function_call();
void test_Bad_weak_ptr();

int main()
{
	
	TestHarness th;

	th.add_Test_to_Suite(test_Bad_Alloc);

    Functor F;
	//F();
	th.add_Test_to_Suite(F);

	th.execute();

	std::cout << th.to_String();

	return 0;
}


bool test_Bad_Alloc()
{
	std::cout << "test_Bad_Alloc" << std::endl;
	std::bad_alloc exception;
	throw exception;
}

void test_Bad_cast()
{

}

void test_Bad_exception()
{

}

void test_Bad_typeid()
{

}

void test_Bad_function_call()
{

}

void test_Bad_weak_ptr()
{

}