#include "Student.h"

using namespace std;

Student::Student() {
    int id = -1;
    string firstName = "";
    string lastName = "";
    int age = -1;
    double GPA = -1.0;
}

void Student::setId(int idStudent) {
    id = idStudent;
}

void Student::initStudent(int idStudent) {
    setId(idStudent);

    cout << "Input firstname:\n";
    cin >> firstName;

    cout << "Input lastName:\n";
    cin >> lastName;

    cout << "Input age:\n";
    while (!(cin >> age)) cinErr("Input age:");

    cout << "Input GPA:\n";
    while (!(cin >> GPA)) cinErr("Input GPA:");
};

int Student::getId() {
    return id;
};

string Student::getFirstName() {
    return firstName;
};

string Student::getLastName() {
    return lastName;
};

int Student::getAge() {
    return age;
};

double Student::getGpa() {
    return GPA;
};

void Student::printInfo() {
    cout << "\nid: " << id << "\nfirstname: " << firstName <<
        "\nlastname: " << lastName << "\nage: " << age <<
        "\nGPA: " << GPA << "\n";
};

void Student::writeToFile(string nameFile) {
    ofstream outputFile(nameFile, ios::app);

    if (!outputFile) {
        cerr << "\nError open. Try again\n" << endl;
        return;
    }

    outputFile <<
        firstName << endl <<
        lastName << endl <<
        age << endl <<
        GPA << endl;

    outputFile.close();
}

void Student::readFromFile(string nameFile, int startRow = 0) {
    string line;
    ifstream inputFile(nameFile);

    if (!inputFile) {
        cerr << "\nError open. Try again\n" << endl;
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