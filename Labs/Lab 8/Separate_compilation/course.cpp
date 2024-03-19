#include "course.h"
#include "course.h"
#include "student.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

namespace BrooklynPoly {

ostream& operator<<(ostream& os, const Course& rhs) {
    os << rhs.name << ": ";
    if (rhs.students.size() == 0) os << "No students";
    else {
            for (const Student* student: rhs.students) {
            os << student->getName() << " ";
        }
    }
    return os;
}
  
Course::Course(const string& courseName) : name(courseName) {};

const string& Course::getName() const { return name; }

bool Course::addStudent(Student* newStudent) {
    for (const Student* student : students) {
        if (student == newStudent) return false;
    }
    students.push_back(newStudent);
    return true;
}

void Course::removeStudentsFromCourse() {
    for (Student* student : students) {
        student->removeFromCourse(this);
    }
    students.clear();
    cout << "Bye students!!" << endl;
}

}