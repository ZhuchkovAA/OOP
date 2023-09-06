#include "Group.h"

#include <algorithm>

Group::Group() {
    vector<Student> listStudents = {};
}

int Group::createIdStudent() {
    if (listStudents.size()) return listStudents[listStudents.size() - 1].getId() + 1;
    return 0;
};

void Group::addStudent() {
    Student newStudent;

    newStudent.initStudent(createIdStudent());
    listStudents.push_back(newStudent);
};

void Group::printList() {
    for_each(listStudents.begin(), listStudents.end(), [](Student& item) {
        item.printInfo();
        });
}

void Group::writeListToFile() {
    string nameFile;

    cout << "Input name File: ";
    cin >> nameFile;
    checkNameFile(nameFile);

    ofstream outputFile(nameFile);

    if (!outputFile) { cerr << "\nError open. Try again\n" << endl; return; }

    outputFile << "";

    for_each(listStudents.begin(), listStudents.end(), [nameFile](Student& item) {
        item.writeToFile(nameFile);
        });
}

void Group::readListFromFile() {
    Student newStudent;
    string nameFile;
    string line;
    int lineCount = 0;

    listStudents.clear();

    cout << "Input name File: ";
    cin >> nameFile;
    checkNameFile(nameFile);

    ifstream inputFile(nameFile);
    if (!inputFile) { cerr << "\nError open. Try again\n" << endl; return; }

    while (getline(inputFile, line)) { lineCount++; }

    for (int i = 0; i < lineCount / 5; i++) {
        newStudent.readFromFile(nameFile, i * 5);
        listStudents.push_back(newStudent);
    }
}

void Group::removeList() {
    listStudents.clear();
}