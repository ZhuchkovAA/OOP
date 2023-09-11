#include "Group_Zhuchkov.h"

#include <algorithm>

Group_Zhuchkov::Group_Zhuchkov() {
    vector<shared_ptr<void>> listStudents;
    shared_ptr<Student_Zhuchkov> objStudent = make_shared<Student_Zhuchkov>();
    shared_ptr<Headman_Zhuchkov> objHeadman = make_shared<Headman_Zhuchkov>();

    listStudents.push_back(static_pointer_cast<void>(objStudent));
    listStudents.push_back(static_pointer_cast<void>(objHeadman));
}

int Group_Zhuchkov::createId() {
    shared_ptr<void> lastElement = listStudents.back();
    if (shared_ptr<Student_Zhuchkov> newStudent = dynamic_pointer_cast<Student_Zhuchkov>(lastElement)) {
        return newStudent -> getId() + 1;
    }
    else if (shared_ptr<Headman_Zhuchkov> newHeadman = dynamic_pointer_cast<Headman_Zhuchkov>(lastElement)) {
        return newHeadman -> getId() + 1;
    }
};

void Group_Zhuchkov::addStudent() {
    shared_ptr <Student_Zhuchkov> newStudent;

    newStudent -> initStudent(createId());
    listStudents.push_back(make_shared<Student_Zhuchkov>(newStudent));
};

void Group_Zhuchkov::printList() {
    for_each(listStudents.begin(), listStudents.end(), [](shared_ptr<void>& item) {
        if (shared_ptr<Student_Zhuchkov> Student = dynamic_pointer_cast<Student_Zhuchkov>(item)) {
            Student -> printInfo();
        }
        else if (shared_ptr<Headman_Zhuchkov> Headman = dynamic_pointer_cast<Headman_Zhuchkov>(item)) {
            Headman -> printInfo();
        }
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

    for_each(listStudents.begin(), listStudents.end(), [nameFile](shared_ptr<void>& item) {
        if (shared_ptr<Student_Zhuchkov> Student = dynamic_pointer_cast<Student_Zhuchkov>(item)) {
            Student -> writeToFile(nameFile);
        }
        else if (shared_ptr<Headman_Zhuchkov> Headman = dynamic_pointer_cast<Headman_Zhuchkov>(item)) {
            Headman -> writeToFile(nameFile);
        }
    });
}

void Group_Zhuchkov::readListFromFile() {
    shared_ptr <Student_Zhuchkov> newStudent;
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
        newStudent -> readFromFile(nameFile, i * 4);
        newStudent -> setId(createId());
        listStudents.push_back(make_shared<Student_Zhuchkov>(newStudent));
    }
}

void Group_Zhuchkov::removeList() {
    listStudents.clear();
}

void Group_Zhuchkov::addHeadman() {
    shared_ptr<Headman_Zhuchkov > newHeadman;
    newHeadman -> initHeadman(createId());
    listStudents.push_back(make_shared<Headman_Zhuchkov>(newHeadman));
}