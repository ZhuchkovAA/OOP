#include "Group_Zhuchkov.h"

#include <algorithm>

Group_Zhuchkov::Group_Zhuchkov() {
    vector<shared_ptr<Student_Zhuchkov>> listStudents = {};
}

int Group_Zhuchkov::createId() {
    if (!listStudents.size()) return 0;
    shared_ptr<Student_Zhuchkov> lastStudent = listStudents.back();

    return (lastStudent->getId());
};

void Group_Zhuchkov::addStudent() {
    shared_ptr<Student_Zhuchkov> newStudent = make_shared<Student_Zhuchkov>();
    newStudent->initStudent(createId());

    listStudents.push_back(newStudent);
}

void Group_Zhuchkov::addHeadman() {
    shared_ptr<Headman_Zhuchkov> newHeadman = make_shared<Headman_Zhuchkov>();
    newHeadman->initHeadman(createId());

    listStudents.push_back(newHeadman);
}

void Group_Zhuchkov::printList() {
    for (shared_ptr<Student_Zhuchkov> Student : listStudents) {
        Student->printInfo();
    };
}

void Group_Zhuchkov::writeListToFile() {
    string nameFile;

    cout << "Введите имя файла: ";
    cin >> nameFile;
    checkNameFile(nameFile);

    ofstream outputFile(nameFile);

    if (!outputFile) { cerr << "\nОшибка. Попробуйте заново\n" << endl; return; }

    outputFile << "";

    for (shared_ptr<Student_Zhuchkov> Student : listStudents)
        Student -> writeToFile(nameFile);
}

void Group_Zhuchkov::readListFromFile() {
    shared_ptr<Student_Zhuchkov> newStudent = make_shared<Student_Zhuchkov>();
    string nameFile;
    string line;
    int lineCount = 0;

    cout << "Введите имя файла: ";
    cin >> nameFile;
    checkNameFile(nameFile);

    ifstream inputFile(nameFile);
    if (!inputFile) { cerr << "\nОшибка. Попробуйте заново\n" << endl; return; }


    while (inputFile >> line) {
        if (line == "0") 

        newStudent -> readFromFile(nameFile, i * 5);
        newStudent -> setId(createId());

        listStudents.push_back(newStudent);
    }
}

void Group_Zhuchkov::removeList() {
    listStudents.clear();
}
