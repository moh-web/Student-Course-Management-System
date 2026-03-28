#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

// ================= BASE CLASS =================
class Person {
protected:
    string name;

public:
    Person(string n = "") : name(n) {}
    string getName() const { return name; }
};

// ================= DERIVED CLASS =================
class Student : public Person {
private:
    int id;
    double gpa;
    set<string> courses; // prevents duplicates

public:
    Student(int id, string name, double gpa)
        : Person(name), id(id), gpa(gpa) {
    }

    int getId() const { return id; }
    double getGpa() const { return gpa; }

    void addCourse(const string& course) {
        courses.insert(course);
    }

    void showCourses() const {
        if (courses.empty()) {
            cout << "No courses enrolled.\n";
            return;
        }
        for (const auto& c : courses)
            cout << "- " << c << endl;
    }

    void display() const {
        cout << "ID: " << id
            << " | Name: " << name
            << " | GPA: " << gpa << endl;
    }
};

// ================= SYSTEM CLASS =================
class StudentSystem {
private:
    vector<Student> students;

    // Helper: find student by ID
    vector<Student>::iterator findStudent(int id) {
        return find_if(students.begin(), students.end(),
            [id](const Student& s) { return s.getId() == id; });
    }

public:
    void addStudent() {
        int id;
        string name;
        double gpa;

        cout << "Enter ID: ";
        cin >> id;

        if (findStudent(id) != students.end()) {
            cout << "❌ ID already exists!\n";
            return;
        }

        cout << "Enter Name: ";
        cin >> name;

        cout << "Enter GPA (0 - 4): ";
        cin >> gpa;

        if (gpa < 0.0 || gpa > 4.0) {
            cout << "❌ Invalid GPA!\n";
            return;
        }

        students.emplace_back(id, name, gpa);
        cout << "✅ Student added successfully.\n";
    }

    void removeStudent() {
        int id;
        cout << "Enter ID to remove: ";
        cin >> id;

        auto it = findStudent(id);
        if (it == students.end()) {
            cout << "❌ Student not found.\n";
            return;
        }

        students.erase(it);
        cout << "✅ Student removed.\n";
    }

    void searchStudent() {
        int id;
        cout << "Enter ID to search: ";
        cin >> id;

        auto it = findStudent(id);
        if (it == students.end()) {
            cout << "❌ Not found.\n";
            return;
        }

        it->display();
    }

    void displayAll() {
        if (students.empty()) {
            cout << "No students available.\n";
            return;
        }

        for (const auto& s : students)
            s.display();
    }

    void enrollCourse() {
        int id;
        string course;

        cout << "Enter Student ID: ";
        cin >> id;

        auto it = findStudent(id);
        if (it == students.end()) {
            cout << "❌ Student not found.\n";
            return;
        }

        cout << "Enter Course Name: ";
        cin >> course;

        it->addCourse(course);
        cout << "✅ Course added.\n";
    }

    void showCourses() {
        int id;
        cout << "Enter Student ID: ";
        cin >> id;

        auto it = findStudent(id);
        if (it == students.end()) {
            cout << "❌ Student not found.\n";
            return;
        }

        it->showCourses();
    }

    void sortByGPA() {
        sort(students.begin(), students.end(),
            [](const Student& a, const Student& b) {
                return a.getGpa() > b.getGpa();
            });

        cout << "✅ Students sorted by GPA.\n";
    }
};

// ================= MAIN =================
int main() {
    StudentSystem system;
    int choice;

    do {
        cout << "\n===== Student Management System =====\n";
        cout << "1. Add Student\n";
        cout << "2. Remove Student\n";
        cout << "3. Search Student\n";
        cout << "4. Display All Students\n";
        cout << "5. Enroll Student in Course\n";
        cout << "6. Show Student Courses\n";
        cout << "7. Sort Students by GPA\n";
        cout << "8. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
        case 1: system.addStudent(); break;
        case 2: system.removeStudent(); break;
        case 3: system.searchStudent(); break;
        case 4: system.displayAll(); break;
        case 5: system.enrollCourse(); break;
        case 6: system.showCourses(); break;
        case 7: system.sortByGPA(); break;
        case 8: cout << "Exiting...\n"; break;
        default: cout << "❌ Invalid choice.\n";
        }

    } while (choice != 8);

    return 0;
}