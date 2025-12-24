
#include <iostream>

class Person
{
public:
    std::string name;
    int age;
};

int main()
{

    auto p1 = new Person();
    p1->name = "John";
    p1->age = 23;

    auto p2 = Person();
    p2.name = "Jane";
    p2.age = 19;

    return 0;
}