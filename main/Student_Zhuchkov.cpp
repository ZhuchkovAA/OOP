#include "Student_Zhuchkov.h"

using namespace std;

void Student_Zhuchkov::setId(int id) { this-> id = id; }
void Student_Zhuchkov::setFirstName(string firstName) { this->firstName = firstName; };
void Student_Zhuchkov::setLastName(string lastName) { this->lastName = lastName; };
void Student_Zhuchkov::setAge(int age) { this->age = age; };
void Student_Zhuchkov::setGpa(double GPA) { this->GPA = GPA; };
void Student_Zhuchkov::setIsHeadman(bool isHeadman) { this->isHeadman = isHeadman; };

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

    isHeadman = false;
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

bool Student_Zhuchkov::getIsHeadman() {
    return isHeadman;
};

void Student_Zhuchkov::printInfo() {
    cout << "\n# " << id + 1 << "\n���: " << firstName <<
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
        isHeadman << endl <<
        firstName << endl <<
        lastName << endl <<
        age << endl <<
        GPA << endl;

    outputFile.close();
}

ifstream& operator>>(ifstream& input, Student_Zhuchkov& Student) {
    input >> Student.id >> Student.firstName >> Student.lastName >> Student.age >> Student.GPA;
    return input;
};