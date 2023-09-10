#pragma once
#include "Student_Zhuchkov.h"
#include "Headman_Zhuchkov.h"
#include <vector>
#include <memory>

class Group_Zhuchkov {
private:
    vector<Student_Zhuchkov> listStudents;
//    vector<shared_ptr<void>> listStudents;

public:
    Group_Zhuchkov();
    int createIdStudent();
    void addStudent();
    void printList();
    void writeListToFile();
    void readListFromFile();
    void removeList();
    void addHeadman();
};

