#include "CppUnitTest.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "tlog.h"
#include <cassert>

#define tlog Tlog()


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace LearnCpp
{
	TEST_CLASS(LearnCpp)
	{
	public:
		TEST_METHOD(initializer_list) {
            ///////////////////////1 - 1. initializer list //////////////////////
// -----------------------   c++ 03 initializer list

            int arr03[4] = { 3, 2, 4, 5 };
            vector<int> v03;
            v03.push_back(3);
            v03.push_back(2);
            v03.push_back(4);
            v03.push_back(5);

            // ===================== c++ 11 extend to other, all the stl container

            vector<int> v11 = { 3, 4, 1, 9 }; // calling inittializer_lsit constructor

            // ====================== define your own initalizer_list constructor

            class MyVector
            {
                vector<int> m_vec;

            public:
                MyVector(const std::initializer_list<int>& v)
                {
                    for (std::initializer_list<int>::iterator itr = v.begin(); itr != v.end(); ++itr)
                    {
                        m_vec.push_back(*itr);
                    }
                }
            };

            MyVector v1 = { 0, 2, 3, 4 };
            MyVector v2{ 0, 2, 3, 4 };

            /////////////////////////////////2  uniform initialization/////////////////
            // c++ 03  uniform initialization search order
            /*
            1. initializer_list constructor
            2. regular constructor that takes the appropriete parameter
            3. aggregate initalizer
            */

            class Dog
            {
            public:
                int age; //  3rd

                Dog(int a)
                { // 2nd
                    age = a;
                }

                Dog(const std::initializer_list<int>& vect)
                { // 1st
                    age = *(vect.begin());
                }
            };
		}
		TEST_METHOD(test_AutoType)
		{
			std::string name = "Bill";
			Logger::WriteMessage("foo");

			////////////////////////////////// auto type//////////////////////////////////////

			vector<int> vauto = { 7,8,9,0 };

			// c++ 03
			for (vector<int>::iterator it = vauto.begin(); it != vauto.end(); it++) {
				tlog << *it << "\t"; 
 
			} 
 
			tlog << "\n";
			// c++ 11
			for (auto it = vauto.begin(); it != vauto.end(); ++it) {
				tlog << *it << "\t";
			}
 

		}

		TEST_METHOD(test_foreach) {
			vector<int> v = { 2,3,4,5 };
			// cpp 03
			for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
				tlog << *it << " | ";
			}

			tlog << "\n";


				// cpp 11


                for (int& i : v) {  // change value
                    i += 100;
                }

				for (int i : v) { // works with class has begin() and end()
					tlog << i << "\t";
				}

		}

		void foo(int i) { tlog << "int ===== " << i; }
		void foo(char* pc) {
            if (pc) {
                tlog << " char ======" << *pc;
            }
            else {
                tlog << " char ======" << " nullptr ";
            }
             
        }

        TEST_METHOD(test_nullptr) {


            foo(NULL);  // cpp  03 , NULL is int 0
            foo(nullptr); // cpp 11 , nullptr
        }

        TEST_METHOD(test_enum_class) {
            //03 enum - global
            enum color {red, green, blue};
            tlog << "\n red=" << red;
            //11 enum class - scoped
            enum class shape {square, circle};
            tlog << "\n square=" <<  static_cast<std::underlying_type_t<shape>>(shape::square);

        }

        TEST_METHOD(test_assert) {
            //03 - run time assert
            assert( 1==1);

            // 11 - static_assert : compile time
            static_assert(sizeof(int) == 4, " 4 byte int");


        }

        TEST_METHOD(test_delegating_constructor) {
            // cpp 03 not support call another constructor from constructor like java
            // cpp 11
            class Dog {
                string name;
                int age = 0;
            public:
                
                Dog( string name, int age) : name(name), age(age){} // member-initializer

                Dog(string name) :
                    Dog(name , 0)
                {
                    /*
                    * When you delegate the member initialization to another constructor, 
                    there is an assumption that the other constructor initializes the object completely, 
                    including all members (i.e. including the lines member in your example).
                    You can't therefore initialize any of the members again.
                    */
                }
            };
        }

        TEST_METHOD(test_override_virtual_function) {
            // override - avoid inadvertently create new function in derived classes
            class Dog  {
                virtual void bark(int) {};
            };

            class GoodDog : Dog{
                void bark(int) override {};
            };
        }

        TEST_METHOD(test_force_default_constructor) {
            class Dog {                
            public:
                string name = "dog";
                Dog( string name) :name(name){}
                Dog() = default;
            };

            Dog d1;
            tlog << "default dog name: " << d1.name;

        }

        TEST_METHOD(test_delete_function) {
            class Dog {
            public:
                Dog(int age) {};
                Dog(double age) = delete;           //not allow
                Dog& operator=(const Dog&) = delete; //not allow copy constructor
            };

            Dog d= Dog(3);

        }

        // constexpr - compute at compile time not run time
        constexpr int MeaningOfLife(int a, int b) { return a * b; }

        TEST_METHOD(test_constexpr) {		

			const int meaningOfLife = MeaningOfLife(6, 7);

        }


        // lambda as parameter
		template<typename func>
		void filter(func f, vector<int> vec) {
            tlog << "\n";
            for (auto i : vec) {
                if (f(i)) {
                    tlog << i << "\t";
                }
            }
		}


        TEST_METHOD(test_lambda) {

            // anonymous lambda function 
            tlog << "give me a seven = " << [](int x, int y) { return x + y;  }(3, 4) << "\n";

            // named lambda function
            auto f = [](int x, int y) { return x + y;  };
            tlog << "give me a five =" << f(2, 3);

            vector<int> vec{ 1,2,3,4,5,6,7,8,9,0 };


            // functional programming
            filter([](int x) {return x % 2 == 0;  }, vec);
            int y = 5;
            filter([&y](int x) {return x >= y;  }, vec);   // capture the local variable


        }

	};
}
