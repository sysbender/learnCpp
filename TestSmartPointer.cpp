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

			// customized shared pointer deleter - use shared pointer constructor instead of make_shared
			shared_ptr<Dog> dd = shared_ptr<Dog>(new Dog("CustomDog"),
				[](Dog* pDog) { tlog << "\n customized deleting Dog"; delete  pDog; }  // deleter is a lambda with a param T*
			);

			// customized deleter is a must for array shared pointer
			shared_ptr<Dog> da = shared_ptr<Dog>(new Dog[3], 
				[](Dog* p) { delete[] p; }
				);
		}


		// weak_ptr has no ownership of the pointed object
		// weak_ptr like raw pointer, but not allow delete operator
		TEST_METHOD(test_weak_pointer) {
			class Dog {
				weak_ptr <Dog> m_pFriend; // cyclic reference
			public:
				string m_name;
				Dog(string name) { tlog << "\n create Dog : " << name; m_name = name;  }
				void bark() { tlog << "\nDog barking :" << m_name; }
				~Dog() { tlog << "\n Dog destroyed :" << m_name; }
				void makeFriend(shared_ptr<Dog> f) { m_pFriend = f;  }

				// weak_ptr.lick will create a shared point to make sure : object exist and will not be deleted
				void showFrind() {
					if (!m_pFriend.expired()) {
						//check weak_pointer is valid
						tlog << "\n" << m_name << " :  my friend is " << m_pFriend.lock()->m_name;
						tlog << "\n use_count = " << m_pFriend.use_count();
					}
				}

			};

			shared_ptr<Dog> dBoy = make_shared<Dog>("dBoy");
			shared_ptr<Dog> dGirl = make_shared<Dog>("dGirl");

			dBoy->makeFriend(dGirl );
			dGirl->makeFriend(dBoy);

			dGirl->showFrind();
		}

		// unique pointer - exclusive ownership, light weight smart pointer
		TEST_METHOD(test_unique_pointer) {

			class Dog {				
			public:
				string m_name;
				Dog() { m_name = "nameless"; tlog <<  "\n create Dog : " << m_name; }
				Dog(string name) { tlog << "\n create Dog : " << name; m_name = name; }
				void bark() { tlog << "\nDog barking :" << m_name; }
				~Dog() { tlog << "\n Dog destroyed :" << m_name; }
				 
			};


			

			{
				unique_ptr<Dog> pd1(new Dog("uniqueDog1"));
				pd1->bark();
				pd1.reset(new Dog("uniqueDog2"));
				
				pd1->bark();
				Dog* pD2 = pd1.release();   // release raw pointer // shared_ptr use get
				if (!pd1) {
					tlog << "\n unique pointer is released and empty";
				}

				unique_ptr<Dog> pd3(new Dog("uniqueDog3"));
				pd1 = move(pd3);  // transfer ownership
				pd1->bark();
				pd1.reset(); // same as pd1=nullptr;


			}

			auto Consumer = [](unique_ptr<Dog> p) {
				p->bark();
			};

			auto Producer = []() {
				return unique_ptr<Dog>(new Dog("NewDog"));  // return unique pointer will auto use move semantics
			};


			unique_ptr<Dog> pd11 = Producer();
			// pd11->bark();
			Consumer(move(pd11));  // use move semantic for unique pointer param

			// unique pointer not needs customized deleter  for array as shared pointer
			unique_ptr<Dog[]> pd21(new Dog[3]);
		}

	};
}
