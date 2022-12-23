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
	};
}
