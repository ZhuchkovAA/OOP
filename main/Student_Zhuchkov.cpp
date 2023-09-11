#include "Student_Zhuchkov.h"

using namespace std;

Student_Zhuchkov::Student_Zhuchkov() {
    int id = -1; 
    string firstName = "";
    string lastName = "";
    int age = -1;
    double GPA = -1.0;
}

void Student_Zhuchkov::setId(int idStudent) {
    id = idStudent;
}

void Student_Zhuchkov::initStudent(int idStudent) {
    setId(idStudent);

    cout << "������� ���:\n";
    cin >> firstName;

    cout << "������� �������:\n";
    cin >> lastName;

    cout << "������� �������:\n";
    while (!(cin >> age)) cinErr("Input age:");

    cout << "������� ������� ����:\n";
    while (!(cin >> GPA)) cinErr("Input GPA:");
};

int Student_Zhuchkov::getId() {
    return id;
};

string Student_Zhuchkov::getFirstName() {
    return firstName;
};

string Student_Zhuchkov::getLastName() {
    return lastName;
};

int Student_Zhuchkov::getAge() {
    return age;
};

double Student_Zhuchkov::getGpa() {
    return GPA;
};

void Student_Zhuchkov::printInfo() {
    cout << "\nid: " << id << "\n���: " << firstName <<
        "\n�������: " << lastName << "\n�������: " << age <<
        "\n������� ����: " << GPA << "\n";
};

void Student_Zhuchkov::writeToFile(string nameFile) {
    ofstream outputFile(nameFile, ios::app);

    if (!outputFile) {
        cerr << "\n������. ���������� ������\n" << endl;
        return;
    }

    outputFile <<
        firstName << endl <<
        lastName << endl <<
        age << endl <<
        GPA << endl;

    outputFile.close();
}

void Student_Zhuchkov::readFromFile(string nameFile, int startRow = 0) {
    string line;
    ifstream inputFile(nameFile);

    if (!inputFile) {
        cerr << "\n������. ���������� ������\n" << endl;
        return;
    }

    for (int i = 0; i < startRow; i++) { getline(inputFile, line); }

    getline(inputFile, line);
    firstName = line;
    getline(inputFile, line);
    lastName = line;
    getline(inputFile, line);
    age = stoi(line);
    getline(inputFile, line);
    GPA = stod(line);

    inputFile.close();
}