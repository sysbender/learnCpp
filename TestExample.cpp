#include <CppUnitTest.h>
#include <string>
#include <vector>
#include "tlog.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace Example {

	TEST_CLASS(ExampleClass)
	{

	public:

		TEST_METHOD(ExampleMethod)
		{
			tlog << "In Example";

		}


	};
}
