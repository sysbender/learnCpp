#pragma once

#include "CppUnitTest.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;


class Tlog {

public:
	template<class T>
	Tlog& operator<<(const T& v)
	{
		std::stringstream buffer;
		buffer << v;
		Logger::WriteMessage(buffer.str().c_str());
		return *this;
	}

};
#define tlog Tlog()
