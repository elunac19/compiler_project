#include <iostream>
#include <string>

struct Employee {
    std::string name;
    double salary;
    void increaseSalary(double increase) {
        salary += increase;
    }
};

int main() {
    Employee emp;
    emp.name = "John Doe";
    emp.salary = 50000;

    std::cout << "Employee name: " << emp.name << "\n";
    std::cout << "Salary before increase: " << emp.salary << "\n";

    emp.increaseSalary(5000);

    std::cout << "Salary after increase: " << emp.salary << "\n";

    return 0;
}