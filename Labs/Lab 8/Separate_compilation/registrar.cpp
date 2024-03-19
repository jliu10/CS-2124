
#include "registrar.h"
#include "course.h"
#include "student.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

namespace BrooklynPoly {
    ostream& operator<<(ostream& os, const Registrar& rhs) {
    os << "Registrar's Report\nCourses:" << endl;
    for (const Course* course : rhs.courses) {
        os << *course << endl;
    }
    os << "Students:" << endl;
    for (const Student* student : rhs.students) {
        os << *student << endl;
    }
    return os;
}

Registrar::Registrar() {}

size_t Registrar::findStudent(const string& name) const {
    for (size_t i = 0; i < students.size(); i++) {
        if (students[i]->getName() == name) return i;
    }
    return students.size();
}

size_t Registrar::findCourse(const string& name) const {
    for (size_t i = 0; i < courses.size(); i++) {
        if (courses[i]->getName() == name) return i;
    }
    return courses.size();
}

bool Registrar::addCourse(const string& name) {
    size_t i = findCourse(name);
    if (i < courses.size()) return false;
    courses.push_back(new Course(name));
    return true;
}

bool Registrar::addStudent(const string& name) {
    size_t i = findStudent(name);
    if (i < students.size()) return false;
    students.push_back(new Student(name));
    return true;
}

bool Registrar::enrollStudentInCourse(const string& studentName,
                           const string& courseName)
{
    size_t i = findStudent(studentName);
    size_t j = findCourse(courseName);
    if (i < students.size() && j < courses.size()) {
        students[i]->addCourse(courses[j]);
        courses[j]->addStudent(students[i]);
        return true;
    }
    return false;
}

bool Registrar::cancelCourse(const string& courseName) {
    size_t i = findCourse(courseName);
    if (i == courses.size()) return false;
    courses[i]->removeStudentsFromCourse();
    courses[i] = courses[courses.size() - 1];
    courses.pop_back();
    return true;
}

void Registrar::purge() {
    for (Course* course : courses) {
        delete course;
    }
    for (Student* student : students) {
        delete student;
    }
    courses.clear();
    students.clear();
}
}