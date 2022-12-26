#include <CppUnitTest.h>
#include <string>
#include <vector>
#include "tlog.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace ResourceManagement {

	TEST_CLASS(TestResourceManagement)
	{

	public:



		TEST_METHOD(test_rm)
		{

			class Person {
				string* pname_;
			public:
				Person(string name) { pname_ = new string(name); tlog << "\n create person: " << name; }
				~Person() {
					if (pname_) {
						tlog << "\n deleting Person: " << *pname_;
						delete pname_;
					}
					else {
						tlog << "\n deleting Person = invalid pointer ";
					}
				}
				void printPerson() { tlog << "\n print Person : " << *pname_; }
				// solution 1: define copy constructor and copy assign operator for deep copying
				// solution 2: delete copy constructor and copy assign operator

				// use explicit clone , instead of implicit copying
				Person* clone() {
					return (new Person(*pname_));
				}
			private:

				// avoid implicit copying
				Person(const Person& rhs) {
					pname_ = new string(*rhs.pname_);
				}

				Person operator=(const Person& rhs) {
					pname_ = new string(*rhs.pname_);
				}


			};



			Person p("tom");  //
			p.printPerson();
			//Person p2(Person("t"));
			//p2.printPerson();

			// STL container need the containee to be copy constructable and copy assignable
			// workaround is to save pointer in the container
 
			vector<Person*> persons;
			persons.push_back(new Person("John"));  			//shallow copy 1. construct John, 2. make a copy 3. destroy john
			persons.back()->printPerson();
 


			tlog << "\n -----------the end";


		}

		/*
		* 1. cpp11 - =delete; cpp03 - make it private
		* 2. cpp11 - vector.emplace_back() - constructor in place without copying in container
		* 3. use shared_ptr to count , costly
		* 4. use unique_ptr, and move semantics
		
		*/

		TEST_METHOD(test_resource_management_11) {

			class Person {
				unique_ptr<string> pname_;
			public:
				Person(string name) { pname_ = make_unique<string>(name); tlog << "\n create person: " << name; }
				//~Person() {
				//	if (pname_) {
				//		tlog << "\n deleting Person: " << *pname_;
				//		delete pname_;
				//	}
				//	else {
				//		tlog << "\n deleting Person = invalid pointer ";
				//	}
				//}
				void printPerson() { tlog << "\n print Person : " << *pname_; }

				~Person() { tlog << "\n destroy Person. "; };
				Person(Person&&) = default; // if destructor is provided, explicitly add the move constructor

			};


			// emplace

			vector<Person> persons;
			persons.push_back( Person("Bill"));
			Person p2("David");
			persons.push_back(move(p2));
			persons.back().printPerson();




		}






	};
}
