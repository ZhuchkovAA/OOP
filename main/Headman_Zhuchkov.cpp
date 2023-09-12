#include "Headman_Zhuchkov.h"

string Headman_Zhuchkov::getPhoneNumber() {
	return phoneNumber;
};

void Headman_Zhuchkov::setPhoneNumber(string phoneNumber) {
	this-> phoneNumber = phoneNumber;
};

void Headman_Zhuchkov::initHeadman(int idStudent) {
	initStudent(idStudent);

	cout << "Введите номер телефона: ";
	cin >> phoneNumber;
};

void Headman_Zhuchkov::printInfo() {
	cout << "\n# " << getId() + 1 << "\nИмя: " << getFirstName() <<
		"\nФамилия: " << getLastName() << "\nВозраст: " << getAge() <<
		"\nСредний балл: " << getGpa() << "\nНомер телефона:" << getPhoneNumber() << "\n";
};

void Headman_Zhuchkov::writeToFile(string nameFile) {
    ofstream outputFile(nameFile, ios::app);

    if (!outputFile) {
        cerr << "\nОшибка. Попробуйте заново\n" << endl;
        return;
    }

    outputFile <<
        getIsHeadman() <<  <<
        getFirstName() << endl <<
        getLastName() << endl <<
        getAge() << endl <<
        getGpa() << endl <<
        getPhoneNumber();

    outputFile.close();
};

ifstream& operator>>(ifstream& input, shared_ptr<Headman_Zhuchkov>& Headman) {
    Headman-> setIsHeadman(true);
    string firstName, lastName, phoneNumber;
    int age;
    double GPA;

    input >> firstName >> lastName >> age >> GPA >> phoneNumber;

    Headman-> setFirstName(firstName);
    Headman-> setLastName(lastName);
    Headman-> setAge(age);
    Headman-> setGpa(GPA);
    Headman-> setPhoneNumber(phoneNumber);

    return input;
}