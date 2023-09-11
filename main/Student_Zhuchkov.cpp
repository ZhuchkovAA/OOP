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

    cout << "Введите имя:\n";
    cin >> firstName;

    cout << "Введите фамилию:\n";
    cin >> lastName;

    cout << "Введите возраст:\n";
    while (!(cin >> age)) cinErr("Input age:");

    cout << "Введите средний балл:\n";
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
    cout << "\n# " << id + 1 << "\nИмя: " << firstName <<
        "\nФамилия: " << lastName << "\nВозраст: " << age <<
        "\nСредний балл: " << GPA << "\n";
};

void Student_Zhuchkov::writeToFile(string nameFile) {
    ofstream outputFile(nameFile, ios::app);

    if (!outputFile) {
        cerr << "\nОшибка. Попробуйте заново\n" << endl;
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

void Student_Zhuchkov::readStudentFromFile(string nameFile) {
    string line;
    ifstream inputFile(nameFile);

    if (!inputFile) {
        cerr << "\nОшибка. Попробуйте заново\n" << endl;
        return;
    }

    isHeadman = false;
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

ifstream& operator>>(ifstream& input, Student_Zhuchkov& student) {
    input >> student.id >> student.firstName >> student.lastName >> student.age >> student.GPA;
    return input;
};