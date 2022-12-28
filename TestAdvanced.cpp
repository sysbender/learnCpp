#include <CppUnitTest.h>
#include <string>
#include <vector>
#include "tlog.h"
#include <mutex>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace Advanced {

	TEST_CLASS(AdvancedClass)
	{

	public:


		template <typename T> bool isConst(T& x)
		{
			return false;
		}

		template <typename T> bool isConst(T const& x)
		{
			return true;
		}
		TEST_METHOD(test_const)
		{



			// const no the left or right side of *

			// const type

			const int i1 = 1;
			int const* pi1 = &i1;   // data is const , pointer is not 
			const int* pi1_b = &i1;
			pi1++;
			// (*pi1)++;  i1 = 6;   not allow


			int i2 = 2;
			// const point type
			int* const pint2{ &i2 };  // data is not const, pointer is const
			(*pint2)++;
			// not allow : pint2++;


			const int* const pi3{ &i1 };  // both data and pointer are const
			// pi3++; 			(*pi3)++;


			// cast away const

			const int i11 = 11;

			(const_cast<int&>(i11))++;   // cast const away and change data
			tlog << "\n i11=" << i11;

			int i12 = 12;
			auto ii = static_cast<const int&>(i12);  			// cast to  const
			tlog << isConst(static_cast<const int&>(i12));



		}

		// resource acquisition is initialization
		/*
		* the only code that can be guaranteed to be executed after exception is throw
		* are the destructor of object residing on the stack
		* - resource management therefore needs to be tied to the lifespan of suitable objects in order to gain automatic deallocation and reclamation
		*/


		class Lock {
		private:
			mutex* m_pm;
		public:
			explicit Lock(mutex* pm) { pm->lock(); m_pm = pm; tlog << "\n locked"; }
			~Lock() { m_pm->unlock(); tlog << "\n unlocked"; }
		};

 
	
		TEST_METHOD(test_RAII) {
			std::mutex mu;
			{
				Lock mylock(&mu);
				// the mutex will always be released when mylock is destroyed from stack
			}			
		}


	};
}
