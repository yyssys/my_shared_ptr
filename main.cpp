#include "shared_ptr.h"

class Student
{
public:
    std::string name = "";
    int age = 0;

    Student(const std::string s, int a) : name(s), age(a)
    {
        std::cout << "Student 构造" << std::endl;
    }
    ~Student()
    {
        std::cout << "Student 析构" << std::endl;
    }
};

int main()
{
    auto pt1 = make_shared<Student>("ys", 18);
    shared_ptr<Student> pt2 = pt1;
    std::cout << "pt1.usecount: " << pt1.use_count() << std::endl;
    pt2 = std::move(pt1);
    return 0;
}