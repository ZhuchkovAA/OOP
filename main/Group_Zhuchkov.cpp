#include "Group_Zhuchkov.h"

#include <algorithm>

Group_Zhuchkov::Group_Zhuchkov() {
    vector<Student_Zhuchkov> listStudents = {};
}

int Group_Zhuchkov::createIdStudent() {
    if (listStudents.size()) return listStudents[listStudents.size() - 1].getId() + 1;
    return 0;
};

void Group_Zhuchkov::addStudent() {
    Student_Zhuchkov newStudent;

    newStudent.initStudent(createIdStudent());
    listStudents.push_back(newStudent);
};

void Group_Zhuchkov::printList() {
    for_each(listStudents.begin(), listStudents.end(), [](Student_Zhuchkov& item) {
        item.printInfo();
        });
}

void Group_Zhuchkov::writeListToFile() {
    string nameFile;

    cout << "Input name File: ";
    cin >> nameFile;
    checkNameFile(nameFile);

    ofstream outputFile(nameFile);

    if (!outputFile) { cerr << "\nError open. Try again\n" << endl; return; }

    outputFile << "";

    for_each(listStudents.begin(), listStudents.end(), [nameFile](Student_Zhuchkov& item) {
        item.writeToFile(nameFile);
        });
}

void Group_Zhuchkov::readListFromFile() {
    Student_Zhuchkov newStudent;
    string nameFile;
    string line;
    int lineCount = 0;

    cout << "Input name File: ";
    cin >> nameFile;
    checkNameFile(nameFile);

    ifstream inputFile(nameFile);
    if (!inputFile) { cerr << "\nError open. Try again\n" << endl; return; }

    while (getline(inputFile, line)) { lineCount++; }

    for (int i = 0; i < lineCount / 4; i++) {
        newStudent.readFromFile(nameFile, i * 4);
        newStudent.setId(createIdStudent());
        listStudents.push_back(newStudent);
    }
}

void Group_Zhuchkov::removeList() {
    listStudents.clear();
}

void Group_Zhuchkov::addHeadman() {
    initHeadman(createIdStudent())
}