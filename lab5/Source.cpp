#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <unordered_set>
#include <algorithm>

using namespace std;

class Student {
public:
    string name;
    string group;
    int studentId;
    int grades[4];

public:
    Student() {}

    Student(const string& name, const string& group, int studentId, const int* grades) : name(name), group(group), studentId(studentId) {
        for (int i = 0; i < 4; ++i) {
            this->grades[i] = grades[i];
        }
    }

    friend ostream& operator<<(ostream& os, const Student& student) {
        os << "Name: " << student.name << ", Group: " << student.group << ", Student ID: " << student.studentId << ", Grades: ";
        for (int i = 0; i < 4; ++i) {
            os << student.grades[i] << " ";
        }
        return os;
    }
};

class hash_fun {
public:
    size_t operator()(const Student& student) const {
        size_t fio = 0;
        for (auto sim : student.name) {
            fio += (size_t)sim;
        }
        fio += student.studentId;
        return(fio);
    }
};

bool operator == (const Student& student1, const Student& student2) {
    return (student1.name == student2.name);
}

bool operator < (const Student& student1, const Student& student2) {
    if (student1.name == student2.name) return student1.studentId < student2.studentId;
    return (student1.name < student2.name);
}


int main() {
    string name, group;
    int studentId, grades[4];
    set <Student> StudentSet;
    unordered_set <Student, hash_fun> StundetUnd;

    ifstream inputFile("input.txt");
    if (!inputFile) {
        cerr << "Unable to open input file" << endl;
        return 1;
    }
    map<int, bool> m;
    while (inputFile >> name >> group >> studentId >> grades[0] >> grades[1] >> grades[2] >> grades[3]) {
        if (m[studentId]) {
            cerr << "Error: The id of current student is not unique\n";
            return 1;
        }
        m[studentId] = true;
        StudentSet.insert(Student(name, group, studentId, grades));
        StundetUnd.insert(Student(name, group, studentId, grades));
    }
    
    ofstream outputFile("output.txt");
    if (!outputFile) {
        cerr << "Unable to open output file" << endl;
        return 1;
    }
    
    outputFile << "Set container\n";
    for (const auto& student : StudentSet) {
        outputFile << student << endl;
    }


    outputFile << "Unord container\n";
    for (const auto& student : StundetUnd) {
        outputFile << student << endl;
    }
    return 0;
}