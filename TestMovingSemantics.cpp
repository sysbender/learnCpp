#include <CppUnitTest.h>
#include <string>
#include <vector>
#include "tlog.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace MovingSemantics {

	TEST_CLASS(MovingSemanticsClass)
	{

	public:

			TEST_METHOD(Test_Rvalue_Lvalue)
		{

				// lvalue - an object has identifiable location in memory
				// rvalue - not a lvalue

				// lvalue and reference

				int i = 5;		// i is lvalue
				int& r0 = i;		
				// int& r1 = 5;  // rvalue 5 can not assign to reference
				const int& r1 = 5;   // rvalue 5 can assign to const reference

				auto square1 = [](int& x) { return x * x; };
				int s1=5;
				square1(s1);
				//square1(5);   // rvalue 5 can not use as reference

				auto square2 = [](const int& x) {return x * x;  };
				square2(5);	   // rvalue 5 can use as const reference
				square2(5);	   // rvalue 5 can use as const reference

				// lvalue can be implicitly transform to a rvalue
				int i3 = 1;
				int x3 = i3 + 2;
				int x4 = i3;

				//
				int v[3]; 
				*(v + 2) = 4; // v+2 is rvalue , but explicitly to create a lvalue by dereference


				// normally function or operator yields rvalues
				// but when they yield lvalue by return reference
				int myglobal;
				auto lfunc = [](int& i)->decltype(auto) { return i; };
				lfunc(myglobal) = 6;
				tlog << "\n myglobal = " << myglobal;

				
				v[2] = 7;	// operator [] generates lvalue

				// nomally lvalue is modifiable				
				const int c = 8;
				// c = 9;  // but const variable is an exception





				/*
				*  Specifically, decltype(e) is the following type:
				* If e is the name of a variable, i.e. an "id-expression", then the resulting type is the type of the variable.
				* Otherwise, if e evaluates to an lvalue of type T, then the resulting type is T &, and if e evaluates to an rvalue of type T, then the resulting type is T.
				*/

				
 
		}

			// rvalue reference



	};
}
