#include <iostream>
#include <string>
#include <vector>

class Department;
class Employee;

class Office; // Forward declaration for the Office class

class Floor {
public:
    Floor(int floorNumber, int officeCount)
            : floorNumber(floorNumber), officeCount(officeCount) {}

    int getFloorNumber() const {
        return floorNumber;
    }

    std::vector<Office*> offices; // Maintain a list of offices on this floor

private:
    int officeCount;
    int floorNumber;
};

class Office {
public:
    Office(int officeNumber, Floor* arr3 = nullptr)
            : officeNumber(officeNumber), employeeInOffice(nullptr) {}

    int getOfficeNumber() const {
        return officeNumber;
    }

    void setEmployee(Employee* employee) {
        employeeInOffice = employee;
    }

    Employee* getEmployee() const {
        return employeeInOffice;
    }

private:
    int officeNumber;
    Employee* employeeInOffice;
};

class Employee {
public:
    Employee(const std::string& name, int idNumber)
            : name(name), idNumber(idNumber), office(nullptr), departmentOfWork(nullptr) {}

    std::string getName() const {
        return name;
    }

    int getIdNumber() const {
        return idNumber;
    }

    void setOffice(Office* o) {
        office = o;
    }

    Office* getOffice() const {
        return office;
    }

    void setDepartment(Department* department) {
        departmentOfWork = department;
    }

    Department* getDepartment() const {
        return departmentOfWork;
    }

private:
    std::string name;
    int idNumber;
    Office* office;
    Department* departmentOfWork;
};

class Department {
public:
    Department(const std::string& name, int employeeCount)
            : name(name), employeeCount(employeeCount) {}

    std::string getName() const {
        return name;
    }

    int getEmployeeCount() const {
        return employeeCount;
    }

    void addEmployee(Employee* employee) {
        employeesInDepartment.push_back(employee);
    }

    std::vector<Employee*> getEmployees() const {
        return employeesInDepartment;
    }

private:
    std::string name;
    int employeeCount;
    std::vector<Employee*> employeesInDepartment;
};


int main() {
    std::vector<Employee*> employees;
    std::vector<Department*> departments;
    std::vector<Floor*> floors;
    std::vector<Office*> offices;

    while (true) {
        std::cout << "Choose an option:\n"
                  << "1) Add a new Employee\n"
                  << "2) Look up Employee\n"
                  << "3) List a Department\n"
                  << "4) List offices on Floor\n";
        int option;
        std::cin >> option;

        if (option == 1) {
            std::string name, departmentName;
            int idNumber, officeNumber;

            std::cout << "Enter employee name: ";
            std::cin.ignore();
            std::getline(std::cin, name);

            std::cout << "Enter employee ID number: ";
            std::cin >> idNumber;

            std::cout << "Enter department name: ";
            std::cin.ignore();
            std::getline(std::cin, departmentName);

            std::cout << "Enter office number: ";
            std::cin >> officeNumber;

            Employee* newEmployee = new Employee(name, idNumber);
            Department* department = nullptr;
            Office* office = nullptr;

            // Find or create the department
            for (Department* dep : departments) {
                if (dep->getName() == departmentName) {
                    department = dep;
                    break;
                }
            }

            if (!department) {
                department = new Department(departmentName, 0);
                departments.push_back(department);
            }

            department->addEmployee(newEmployee);
            newEmployee->setDepartment(department);

            // Find or create the office and associate the employee
            for (Office* ofc : offices) {
                if (ofc->getOfficeNumber() == officeNumber) {
                    office = ofc;
                    break;
                }
            }

            if (!office) {
                office = new Office(officeNumber);
                offices.push_back(office);
            }

            office->setEmployee(newEmployee);
            newEmployee->setOffice(office);

            employees.push_back(newEmployee);

            std::cout << "Added: " << name << ", #" << idNumber << ", works in the " << departmentName << " department in office " << officeNumber << "." << std::endl;
        } else if (option == 2) {
            int idNumber;
            std::cout << "Enter ID number: ";
            std::cin >> idNumber;

            Employee* foundEmployee = nullptr;

            for (Employee* emp : employees) {
                if (emp->getIdNumber() == idNumber) {
                    foundEmployee = emp;
                    break;
                }
            }

            if (foundEmployee) {
                std::cout << foundEmployee->getName() << ", #" << foundEmployee->getIdNumber() << ", works in the " << foundEmployee->getDepartment()->getName() << " department in office " << foundEmployee->getOffice()->getOfficeNumber() << "." << std::endl;
            } else {
                std::cout << "Employee not found." << std::endl;
            }
        } else if (option == 3) {
            std::string departmentName;
            std::cout << "Enter department name: ";
            std::cin.ignore();
            std::getline(std::cin, departmentName);

            Department* foundDepartment = nullptr;

            for (Department* dep : departments) {
                if (dep->getName() == departmentName) {
                    foundDepartment = dep;
                    break;
                }
            }

            if (foundDepartment) {
                std::cout << "Employees in the " << departmentName << " department:" << std::endl;
                for (Employee* emp : foundDepartment->getEmployees()) {
                    std::cout << emp->getName() << ", #" << emp->getIdNumber() << ", in office " << emp->getOffice()->getOfficeNumber() << std::endl;
                }
            } else {
                std::cout << "Department not found." << std::endl;
            }
        } else if (option == 4) {
            int floorNumber;
            std::cout << "Enter floor number: ";
            std::cin >> floorNumber;

            Floor* foundFloor = nullptr;

            for (Floor* flr : floors) {
                if (flr->getFloorNumber() == floorNumber) {
                    foundFloor = flr;
                    break;
                }
            }

            if (foundFloor) {
                std::cout << "Offices on Floor " << floorNumber << ":" << std::endl;
                for (Office *ofc: foundFloor->offices) {
                    Employee *emp = ofc->getEmployee();
                    if (emp) {
                        std::cout << "Office " << ofc->getOfficeNumber() << ": " << emp->getName() << ", #"
                                  << emp->getIdNumber() << " (" << emp->getDepartment()->getName() << " department)"
                                  << std::endl;
                    }
                }
            }
        }
    }
}