#include "Headman_Zhuchkov.h"

string Headman_Zhuchkov::getPhoneNumber() {
	return phoneNumber;
};

void Headman_Zhuchkov::setPhoneNumber(string phoneNumber) {
	this-> phoneNumber = phoneNumber;
};

void Headman_Zhuchkov::initHeadman(int idStudent) {
	initStudent(idStudent);

	cout << "������� ����� ��������: ";
	cin >> phoneNumber;
};

void Headman_Zhuchkov::printInfo() {
	cout << "\n# " << getId() + 1 << "\n���: " << getFirstName() <<
		"\n�������: " << getLastName() << "\n�������: " << getAge() <<
		"\n������� ����: " << getGpa() << "\n����� ��������:" << getPhoneNumber() << "\n";
};

void Headman_Zhuchkov::writeToFile(string nameFile) {
    ofstream outputFile(nameFile, ios::app);

    if (!outputFile) {
        cerr << "\n������. ���������� ������\n" << endl;
        return;
    }

    outputFile <<
        getIsHeadman() << endl <<
        getFirstName() << endl <<
        getLastName() << endl <<
        getAge() << endl <<
        getGpa() << endl <<
        getPhoneNumber() << endl;

    outputFile.close();
};

ifstream& operator>>(ifstream& input, Headman_Zhuchkov& newHeadman) {
    newHeadman.setIsHeadman(true);
    string firstName, lastName, phoneNumber;
    int age;
    double GPA;

    input >> firstName >> lastName >> age >> GPA >> phoneNumber;

    newHeadman.setFirstName(firstName);
    newHeadman.setLastName(lastName);
    newHeadman.setAge(age);
    newHeadman.setGpa(GPA);
    newHeadman.setPhoneNumber(phoneNumber);

    return input;
}