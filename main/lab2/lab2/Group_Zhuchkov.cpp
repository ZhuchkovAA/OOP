#include "pch.h"
#include "Group_Zhuchkov.h"
#include "Student_Zhuchkov.h"
#include "Headman_Zhuchkov.h"

using namespace std;

void Group_Zhuchkov::addStudent()
{ 
    shared_ptr <Student_Zhuchkov> student = make_shared<Student_Zhuchkov>();
    student->input();
    group.push_back(student);
}

void Group_Zhuchkov::addHeadman() {
    shared_ptr <Headman_Zhuchkov> headman = make_shared<Headman_Zhuchkov>();
    headman->input();
    group.push_back(headman);
}

void Group_Zhuchkov::printList() const {
    if (group.size())
    {
        cout << "Все студенты:" << endl << endl;
        for (auto &student : group) {
            student.get()->output();
        }
    }
    else
    {
        cout << "\nВ группе нет студентов!" << endl;
    }
}

void Group_Zhuchkov::writeListToFile(const CString& filename)
{
    CFile f;
    if (f.Open(filename, CFile::modeCreate | CFile::modeWrite)) {
        CArchive ar(&f, CArchive::store);

        ar << (int)group.size();
        for (auto& student : group) {
            ar << student.get();
        }

        ar.Close();
        f.Close();
    }
    else
        std::cout << "Файла нет" << std::endl;
}

void Group_Zhuchkov::readListFromFile(const CString& filename)
{
    group.clear();

    CFile f;
    if (f.Open(filename, CFile::modeRead))
    {
        CArchive ar(&f, CArchive::load);

        int size;
        ar >> size;

        for (int i = 0; i < size; i++) {
            Student_Zhuchkov* student;
            ar >> student;
            shared_ptr<Student_Zhuchkov> account(student);
            group.push_back(account);
        }
        ar.Close();
        f.Close();
    }
    else {
        std::cout << "Файла нет." << std::endl;
    }
}

void Group_Zhuchkov::removeList() {
    group.clear();
}
