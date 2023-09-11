#pragma once
#include "Student_Zhuchkov.h"
#include "Headman_Zhuchkov.h"
#include <vector>
#include <memory>

class Group_Zhuchkov {
private:
    vector<Student_Zhuchkov*> listStudents;
    
public:
    Group_Zhuchkov();
    int createId();
    void addStudent();
    void printList();
    void writeListToFile();
    void readListFromFile();
    void removeList();
    void addHeadman();
};

