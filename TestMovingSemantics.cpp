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
				int v[3] = {1,2,3};
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

		
			void printRef(int& i) { tlog << "\nlvalue ref=" << i;  }	// param is lvalue ref
			void printRef(int&& i) { tlog << "\n rvalue ref=" << i; }  // param is rvalue ref

			class MyVector {

				double* arr_; // a big array
			public:
				int size;

				MyVector(int s=5) {
					tlog << "\n calling constructor...";
					size = s;
					arr_ = new double[size];
					for (int i = 0; i < size; i++) {
						arr_[i] = i * 10.0;
					}
				}
				MyVector(const MyVector& rhs) { //copy constructor - expensive deep copy
					tlog << "\n calling copy constructor...";
					size =rhs.size;
					arr_ = new double[size];
					for (int i = 0; i < size; i++) { arr_[i] = rhs.arr_[i]; }
				}

				MyVector(MyVector&& rhs) { // move constructor - shallow copy
					tlog << "\n calling move constructor...";
					size = rhs.size;
					arr_ = rhs.arr_;
					rhs.arr_ = nullptr;
				}

				~MyVector() { delete arr_; }
			};

			void foo(MyVector v) { tlog << "\nmyvector size=" << v.size; };
			MyVector createMyVector() { return MyVector();  };

			
		TEST_METHOD(test_moving_semantics) {
			//rvalue reference - useful for overloading copy constructor and copy assignment operator to archieve move semantics
			int a = 5;
			int& b = a; // b is lvalue referernce
			
			printRef(a);	// call with lvalue ref
			printRef(6);	// call with rvalue ref

			//--------------------------------------------------
			MyVector reusable = createMyVector();
			foo(reusable); // this will call the copy constrcutor

			//foo(createMyVector()); // rvalue as param, call move constructor  (not called  by copy elision)
			foo(std::move(reusable));  // call move constructor


			// move semantics is implemented for all STL container, 
			// so passing -by value can be used for STL containers

		}



		template<typename T>
		void relay(T arg) {	//argument forwarding to foo
			foo(arg);
		}

		// perfect forwarding
		// 1. no costly and unnecessary copy construction is made
		// 2. rvalue is forwarded as rvalue, lvalue is forwarded as lvalue

		template<typename T>
		void relayPerfect(T&& arg) {
			foo(std::forward<T>(arg));
		}
		TEST_METHOD(test_perfect_forwarding) {

			MyVector reusable = createMyVector();
			relay(reusable); // param is lvalue
			relay(createMyVector()); // param is rvalue

			relayPerfect(reusable); // param is lvalue
			relayPerfect(createMyVector()); // param is rvalue


			// explaination
			/* reference collapsing rules in c++ 11
			* 1. T& & => T&
			* 2. T& && => T&
			* 3.T&& & => T&
			* 4. T&& && => T&& 
			*/

			




		}
		template <class T>
		struct remote_reference;
		remove_reference<int&>::type i; // int i;
		remove_reference<int>::type i; // int i;

		//   T&& arg; is r-reference when arg is r value
		//   T&& arg; is l-reference when arg is l value
		// so && is an universal reference when 1)  T is a template type, 
			// 2) type deduction (reference collapsing ) happens to T (T is a function template type, not a class template type)
		
		/* summary
		*  r Value reference used for 
		*  1) move semantics	std::move<T>(arg);				- turn arg into R value type
		*  2) perfect forwarding	std::forward<T>(arg);		- turn arg to type of T&&  (static_cast)
		*/

	};
}
