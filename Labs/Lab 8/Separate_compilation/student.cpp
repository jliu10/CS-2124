#include "student.h"
#include "course.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

namespace BrooklynPoly {
ostream& operator<<(ostream& os, const Student& rhs) {
    os << rhs.name << ": ";
    if (rhs.courses.size() == 0) os << "No courses";
    else {
        for (const Course* course: rhs.courses) {
            os << course->getName() << " ";
        }
    }
    return os;
}

Student::Student(const string& name) : name(name) {}

const string& Student::getName() const { return name; }

bool Student::addCourse(Course* newCourse) {
    for (const Course* course : courses) {
        if (course == newCourse) return false;
    }
    courses.push_back(newCourse);
    return true;
}

// Student method needed by Course::removeStudentsFromCourse
void Student::removeFromCourse(Course* course) {
    for (size_t i = 0; i < courses.size(); i++) {
        if (courses[i] == course) {
            courses[i] = courses[courses.size() - 1];
            courses.pop_back();
        }
    }
}
}