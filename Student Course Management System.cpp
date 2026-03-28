#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

// ================= Person =================
class Person {
protected:
    string name;

public:
    Person(string n = "") {
        name = n;
    }

    string getName() {
        return name;
    }
};

// ================= Student =================
class Student : public Person {
private:
    int id;
    double gpa;
    set<string> courses; // 

public:
    Student(int i, string n, double g) : Person(n) {
        id = i;
        gpa = g;
    }

    int getId() {
        return id;
    }

    double getGpa() {
        return gpa;
    }

    void display() {
        cout << "ID: " << id << " | Name: " << name << " | GPA: " << gpa << endl;
    }

    void addCourse(string course) {
        courses.insert(course);
    }

    void showCourses() {
        if (courses.empty()) {
            cout << "No courses.\n";
            return;
        }

        for (string c : courses) {
            cout << "- " << c << endl;
        }
    }
};

// ================= Functions =================

int findStudent(vector<Student>& students, int id) {
    for (int i = 0; i < students.size(); i++) {
        if (students[i].getId() == id) {
            return i;
        }
    }
    return -1;
}


void addStudent(vector<Student>& students) {
    int id;
    string name;
    double gpa;

    cout << "Enter ID: ";
    cin >> id;

    if (findStudent(students, id) != -1) {
        cout << "Student already exists!\n";
        return;
    }

    cout << "Enter Name: ";
    cin >> name;

    cout << "Enter GPA (0 - 4): ";
    while (true) {
        cin >> gpa;

        if (cin.fail()) {
            cout << "Invalid input! Enter number: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        else if (gpa < 0 || gpa > 4) {
            cout << "GPA must be between 0 and 4: ";
        }
        else {
            break;
        }
    }

    students.push_back(Student(id, name, gpa));
    cout << "Student added successfully.\n";
}

//
void removeStudent(vector<Student>& students) {
    int id;
    cout << "Enter ID: ";
    cin >> id;

    int index = findStudent(students, id);

    if (index == -1) {
        cout << "Student not found.\n";
        return;
    }

    students.erase(students.begin() + index);
    cout << "Student removed.\n";
}


void searchStudent(vector<Student>& students) {
    int id;
    cout << "Enter ID: ";
    cin >> id;

    int index = findStudent(students, id);

    if (index == -1) {
        cout << "Student not found.\n";
        return;
    }

    students[index].display();
}


void displayAll(vector<Student>& students) {
    if (students.empty()) {
        cout << "No students.\n";
        return;
    }

    for (int i = 0; i < students.size(); i++) {
        students[i].display();
    }
}


void enrollCourse(vector<Student>& students) {
    int id;
    cout << "Enter ID: ";
    cin >> id;

    int index = findStudent(students, id);

    if (index == -1) {
        cout << "Student not found.\n";
        return;
    }

    cout << "Enter courses (type 'stop' to finish):\n";

    string course;
    while (true) {
        cin >> course;

        if (course == "stop") {
            break;
        }

        students[index].addCourse(course);
    }

    cout << "Courses added successfully.\n";
}


void showCourses(vector<Student>& students) {
    int id;
    cout << "Enter ID: ";
    cin >> id;

    int index = findStudent(students, id);

    if (index == -1) {
        cout << "Student not found.\n";
        return;
    }

    students[index].showCourses();
}


void sortStudents(vector<Student>& students) {
    sort(students.begin(), students.end(),
        [](Student a, Student b) {
            return a.getGpa() > b.getGpa();
        });

    cout << "Students sorted by GPA.\n";
}

// ================= MAIN =================
int main() {
    vector<Student> students;
    int choice;

    do {
        cout << "\n===== MENU =====\n";
        cout << "1. Add Student\n";
        cout << "2. Remove Student\n";
        cout << "3. Search Student\n";
        cout << "4. Display All\n";
        cout << "5. Enroll Course\n";
        cout << "6. Show Courses\n";
        cout << "7. Sort by GPA\n";
        cout << "8. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
        case 1: addStudent(students); break;
        case 2: removeStudent(students); break;
        case 3: searchStudent(students); break;
        case 4: displayAll(students); break;
        case 5: enrollCourse(students); break;
        case 6: showCourses(students); break;
        case 7: sortStudents(students); break;
        case 8: cout << "Goodbye!\n"; break;
        default: cout << "Invalid choice\n";
        }

    } while (choice != 8);

    return 0;
}
