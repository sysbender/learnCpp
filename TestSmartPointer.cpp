#include <CppUnitTest.h>
#include <string>
#include <vector>
#include "tlog.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace SmartPointer {

	TEST_CLASS(SmartPointerClass)
	{

	public:

		TEST_METHOD(test_shared_pointer)
		{

			class Dog {
				string name_;
			public:
				Dog(string name) { tlog << "\n create Dog: name=" << name;  name_ = name; }
				Dog() { tlog << "\n create dog : nameless"; name_ = "nameless";  }
				~Dog() { tlog << "\n destroy dog : " << name_;  }
				void bark() { tlog << "\n Dog bark : " << name_; }
			};



			auto foo = []() {
				Dog* p = new Dog("Gunner");
				//delete p;  // p is a dangling pointer - undefined behavior
				p->bark(); 
				// not delete p - memory leak
			};

			// using shared pointer
			auto foo_shared = []() {
				shared_ptr<Dog> p(new Dog("sharedDog"));  // count=1, p 
				{
					shared_ptr<Dog> p2 = p;  // count =2
					p2->bark();
					tlog << "\nshared count=" << p.use_count();
				}
				p->bark();
				tlog << "\nshared count=" << p.use_count();
			};
			// p out of scope, count =0


			auto foo_shared_safe = []() {
				shared_ptr<Dog> d = make_shared<Dog>("safeDog");  // best practice, never use raw pointer
				d->bark();

			};
			foo();
			foo_shared();
			foo_shared_safe();

			//cast shared pointer:  static_pointer_cast,  dynamic_pointer_cast , const_pointer_cast


			shared_ptr<Dog> d1 = make_shared<Dog>("d1");
			shared_ptr<Dog> d2 = make_shared<Dog>("d2");
			shared_ptr<Dog> d3 = make_shared<Dog>("d3");
			shared_ptr<Dog> d4 = make_shared<Dog>("d4");

			d1 = d4;		// assign another object to shared pointer
			tlog << "\n d1 is gone? ";
			d2.reset();		// reset share pointer
			tlog << "\n d2 is gone? ";
			d3 = nullptr;	// assign to nullptr
			tlog << "\n d3 is gone? ";


			tlog << "\n === finished deleting d1,d2,d3";

		}


	};
}
