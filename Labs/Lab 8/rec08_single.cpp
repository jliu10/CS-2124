/*
  rec08_starter.cpp
  Starter Code for required functionality
  Yes, of course, you may add other methods.
  And no, this won't compile. You have to implement the methods and
  fix the cyclic association.
 */
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Student;

class Course {
    friend ostream& operator<<(ostream& os, const Course& rhs);
public:
    // Course methods needed by Registrar
    Course(const string& courseName);
    const string& getName() const;
    bool addStudent(Student*);
    // Tell the students that they are no longer in the course
    void removeStudentsFromCourse(); 
private:
    string name;
    vector<Student*> students;
};
class Student {
    friend ostream& operator<<(ostream& os, const Student& rhs);
public:
    // Student methods needed by Registrar
    Student(const string& name);
    const string& getName() const;
    bool addCourse(Course*);
    // Student method needed by Course::removeStudentsFromCourse
    void removeFromCourse(Course*);
private:
    string name;
    vector<Course*> courses;
};
class Registrar {
    friend ostream& operator<<(ostream& os, const Registrar& rhs);
public:
    Registrar();
    // Creates a new course, if none with that name
    bool addCourse(const string&);
    // Creates a new student, if none with that name
    bool addStudent(const string&);
    // If the student and the course exist, then enroll the student.
    bool enrollStudentInCourse(const string& studentName,
                               const string& courseName);
    // Unenroll the students from the course and remove the course
    // from the Registrar.
    bool cancelCourse(const string& courseName);
    // Get rid of everything!!!
    void purge();
private:
    size_t findStudent(const string&) const;
    size_t findCourse(const string&) const;
    vector<Course*> courses;
    vector<Student*> students;
};
int main() {
    Registrar registrar;
    cout << "No courses or students added yet\n";
    cout << registrar << endl;
     
    cout << "AddCourse CS101.001\n";
    registrar.addCourse("CS101.001");
    cout << registrar << endl;
    cout << "AddStudent FritzTheCat\n";
    registrar.addStudent("FritzTheCat");
    cout << registrar << endl;
    cout << "AddCourse CS102.001\n";
    registrar.addCourse("CS102.001");
    cout << registrar << endl;
    cout << "EnrollStudentInCourse FritzTheCat CS102.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS102.001");
    cout << "EnrollStudentInCourse FritzTheCat CS101.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS101.001");
    cout << registrar << endl;
    cout << "EnrollStudentInCourse Bullwinkle CS101.001\n";
    cout << "Should fail, i.e. do nothing, "
         << "since Bullwinkle is not a student.\n";
    registrar.enrollStudentInCourse("Bullwinkle", "CS101.001");
    cout << registrar << endl;
    cout << "CancelCourse CS102.001\n";
    registrar.cancelCourse("CS102.001");
    cout << registrar << endl;
   
    /*
    // [OPTIONAL - do later if time]
    cout << "ChangeStudentName FritzTheCat MightyMouse\n";
    registrar.changeStudentName("FritzTheCat", "MightyMouse");
    cout << registrar << endl;  
    cout << "DropStudentFromCourse MightyMouse CS101.001\n";
    registrar.dropStudentFromCourse("MightyMouse", "CS101.001");
    cout << registrar << endl;  
    cout << "RemoveStudent FritzTheCat\n";
    registrar.removeStudent("FritzTheCat");
    cout << registrar << endl;  
    */
    cout << "Purge for start of next semester\n";
    registrar.purge();
    cout << registrar << endl;
}

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