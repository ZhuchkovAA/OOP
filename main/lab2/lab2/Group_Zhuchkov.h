#pragma once
#include<vector>
#include"Student_Zhuchkov.h"
#include"Headman_Zhuchkov.h"

using namespace std;

class Group_Zhuchkov
{
private:
    vector<shared_ptr<Student_Zhuchkov>> group;

public:

    void addStudent();

    void addHeadman();

    void printList() const;

    void removeList();

    void readListFromFile(const CString& filename);

    void writeListToFile(const CString& filename);

};

