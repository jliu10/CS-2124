/*
  rec05.cpp
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Section {
     friend ostream& operator<<(ostream& os, const Section& section);
private:
     class TimeSlot {
          friend ostream& operator<<(ostream& os, const TimeSlot& timeslot);
     public:
          TimeSlot(const string& i_day, unsigned int time) : day(i_day), startTime(time) {}

          // Return day
          const string& getDay() const {
               return day;
          }

          // Return time
          unsigned int getTime() const {
               return startTime;
          }

     private:
          string day;
          unsigned int startTime;
     };
     class Student {
          friend ostream& operator<<(ostream& os, const Student& student);
     public:
          Student(const string& i_name) : name(i_name), grades(14, -1) {}

          // Return name
          const string& getName() const {
               return name;
          }

          // Modify grades
          void setGrades(int grade, int week) {
               grades[week - 1] = grade;
          }
     private:
          string name;
          vector<int> grades;
     };
     friend ostream& operator<<(ostream& os, const Section::TimeSlot& timeslot);
     friend ostream& operator<<(ostream& os, const Section::Student& student);
public:
     Section(const string& i_name, const string& i_day, unsigned int time) : name(i_name), timeslot(i_day, time) {};

     // Destructor
     ~Section() {
          cout << "Section " << name << " is being deleted" << endl;
          for (Student* student : students) {
               cout << "Deleting " << student->getName() << endl;
               delete student;
          }
     }

     // Copy constructor
     Section(const Section& section) : name(section.name), timeslot(section.timeslot) {
          for (const Student* student : section.students) {
               students.push_back(new Student( *student ));
          }
     }

     // Add student
     void addStudent(const string& studentName) {
          students.push_back(new Student(studentName));
     }

     // Add grade
     void addGrade(const string& student_name, int grade, int week) {
          // Find student in list
          size_t i = 0;
          while (i < students.size()) {
               if ( students[i]->getName() == student_name ) {
                    break;
               }
               i++;
          }

          students[i]->setGrades(grade, week);
     }

     void reset() {
          cout << "Section " << name << " is being deleted" << endl;
          for (Student* student : students) {
               cout << "Deleting " << student->getName() << endl;
               delete student;
          }
          students.clear();
     }

private:
     string name;
     TimeSlot timeslot;
     vector<Student*> students;
};

ostream& operator<<(ostream& os, const Section& section) {
     os << "Section: " << section.name << ", " << section.timeslot << ", Students: " << endl;
     if (section.students.size() == 0) {
          os << "None";
     } else {
          for (const Section::Student* student : section.students) {
               os << *student << endl;
          }
     }
     os << endl;
     return os;
}

ostream& operator<<(ostream& os, const Section::TimeSlot& timeslot) {
     os << "Time slot: " << "[Day: " << timeslot.day << ", Start time: ";
     if (timeslot.startTime <= 11) {
          os << timeslot.startTime << "am";
     } else {
          os << timeslot.startTime - 12 << "pm";
     }
     os << "]";
     return os;
}

ostream& operator<<(ostream& os, const Section::Student& student) {
     os << "Name: " << student.name << ", Grades: ";
     for (int grade : student.grades) {
          os << grade << " ";
     }
     return os;
}

class LabWorker {
     friend ostream& operator<<(ostream& os, const LabWorker& worker);
public:
     LabWorker(const string& i_name) : name(i_name) {}

     // Return name
     const string& getName() const {
          return name;
     }

     // Return section
     const Section* getSection() const {
          return section;
     }

     // Add section
     void addSection(Section& new_section) {
          section = &new_section;
     }

     // Add grade
     void addGrade(const string& student_name, int grade, int week) {
         section->addGrade(student_name, grade, week);
     }

private:
     string name;
     Section* section;
};

ostream& operator<<(ostream& os, const LabWorker& worker) {
     os << worker.name << " ";
     if (!worker.section) {
          os << "does not have a section";
     } else {
          os << "has " << *(worker.section);
     }
     os << endl;
     return os;
}


// Test code
void doNothing(Section sec) { cout << sec << endl; }

int main() {

    cout << "Test 1: Defining a section\n";
    Section secA2("A2", "Tuesday", 16);
    cout << secA2 << endl;

    cout << "\nTest 2: Adding students to a section\n";
    secA2.addStudent("John");
    secA2.addStudent("George");
    secA2.addStudent("Paul");
    secA2.addStudent("Ringo");
    cout << secA2 << endl;

    cout << "\nTest 3: Defining a lab worker.\n";
    LabWorker moe( "Moe" );
    cout << moe << endl;

    cout << "\nTest 4: Adding a section to a lab worker.\n";
    moe.addSection( secA2 );
    cout << moe << endl;

    cout << "\nTest 5: Adding a second section and lab worker.\n";
    LabWorker jane( "Jane" );
    Section secB3( "B3", "Thursday", 11 );
    secB3.addStudent("Thorin");
    secB3.addStudent("Dwalin");
    secB3.addStudent("Balin");
    secB3.addStudent("Kili");
    secB3.addStudent("Fili");
    secB3.addStudent("Dori");
    secB3.addStudent("Nori");
    secB3.addStudent("Ori");
    secB3.addStudent("Oin");
    secB3.addStudent("Gloin");
    secB3.addStudent("Bifur");
    secB3.addStudent("Bofur");
    secB3.addStudent("Bombur");
    jane.addSection( secB3 );
    cout << jane << endl;

    cout << "\nTest 6: Adding some grades for week one\n";
    moe.addGrade("John", 17, 1);  
    moe.addGrade("Paul", 19, 1);  
    moe.addGrade("George", 16, 1);  
    moe.addGrade("Ringo", 7, 1);  
    cout << moe << endl;

    cout << "\nTest 7: Adding some grades for week three (skipping week 2)\n";
    moe.addGrade("John", 15, 3);  
    moe.addGrade("Paul", 20, 3);  
    moe.addGrade("Ringo", 0, 3);  
    moe.addGrade("George", 16, 3);  
    cout << moe << endl;

    cout << "\nTest 8: We're done (almost)! \nWhat should happen to all "
         << "those students (or rather their records?)\n";

    cout << "\nTest 9: Oh, IF you have covered copy constructors in lecture, "
         << "then make sure the following call works:\n";
    doNothing(secA2);
    cout << "Back from doNothing\n\n";

} // main
