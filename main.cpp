#include "Executive.h"

int main()
{
	Executive e;

	e.harnessLoader("test.xml");
	e.runHarness();
	e.clearHarness();

	return 0;
}

