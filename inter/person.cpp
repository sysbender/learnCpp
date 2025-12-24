#include <iostream>
#include <vector>

class Person
{
protected:
    std::string first;
    std::string last;

public:
    Person() = default;
    Person(std::string firstName, std::string lastName) : first(firstName), last(lastName) {}
    // Person(std::string firstName, std::string lastName)
    // {
    //     this->first = firstName;
    //     this->last = lastName;
    // }
    void setFirstName(std::string firstName)
    {
        this->first = firstName;
    }

    void setLastName(std::string lastName)
    {
        this->last = lastName;
    }

    std::string getName()
    {
        return this->first + " " + this->last;
    }

    virtual void printInfo()
    {
        std::cout << this->getName() << std::endl;
    }

    virtual ~Person()
    {
    }
};

class Employee : public Person
{
    std::string department;

public:
    Employee(std::string firstName, std::string lastName, std::string dept) : Person(firstName, lastName), department(dept) {}
    void setDepartment(std::string dept)
    {
        this->department = dept;
    }

    std::string getDepartment()
    {
        return this->department;
    }
    void printInfo() override
    {

        std::cout << "First: " + this->first + ", last:" + this->last + " ; Department: " << this->getDepartment() << ";" << std::endl;
    }
};

int main()
{

    Person p = Person("Jane", "Little");
    p.printInfo();
    p.setFirstName("John");
    p.setLastName("Doe");
    p.printInfo();
    Person p2 = Person();

    Employee e("john", "doe", "QA");
    e.setFirstName("John");
    e.printInfo();

    std::vector<Person *> people;
    people.push_back(&p);
    people.push_back(&e);

    std::cout << "==================";
    for (Person *person : people)
    {
        person->printInfo();
    }

    return 0;
}
