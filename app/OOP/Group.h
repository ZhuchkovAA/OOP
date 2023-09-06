#pragma once
#include "Student.h"
#include <vector>

class Group {
private:
    vector<Student> listStudents;

public:
    Group();
    int createIdStudent();
    void addStudent();
    void printList();
    void writeListToFile();
    void readListFromFile();
    void removeList();
};

