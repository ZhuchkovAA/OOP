#pragma once
#include "Student_Zhuchkov.h"
#include <vector>

class Group_Zhuchkov {
private:
    vector<Student_Zhuchkov> listStudents;

public:
    Group_Zhuchkov();
    int createIdStudent();
    void addStudent();
    void printList();
    void writeListToFile();
    void readListFromFile();
    void removeList();
};

