#include "pch.h"
#include "Student_Zhuchkov.h"
#include "Utils.h"


IMPLEMENT_SERIAL(Student_Zhuchkov, CObject, 0)

using namespace std;

void Student_Zhuchkov::input()
{
	string firstName, lastName;
	int age;
	double GPA;
	cout << "Введите имя студента: ";
	cin.ignore();
	getline(cin, firstName);
	this->firstName = firstName.c_str();
	cout << "Введите фамилию студента: ";
	cin.ignore();
	getline(cin, lastName);
	this->lastName = lastName.c_str();
	cout << "Введите возраст студента: ";
	while (!(cin >> age)) cinErr("Неправильные данные. Введите возраст: ");
	this->age = age;
	cout << "Введите средний балл студента: ";
	while (!(cin >> GPA)) cinErr("Неправильные данные. Введите средний балл: ");
	this->GPA = GPA;
}

void Student_Zhuchkov::output()
{
	cout  << "Имя: " << this->firstName << endl;
	cout << "Фамилия: " << this->lastName << endl;
	cout << "Возраст: " << this->age << endl;
	cout << "Средний балл: " << this->GPA << endl << endl;
}

void Student_Zhuchkov::Serialize(CArchive& ar) {

	if (ar.IsStoring()) {
		ar << firstName
			<< lastName
			<< age
			<< GPA;
	}
	else {
		ar >> firstName
			>> lastName
			>> age
			>> GPA;
	}
}

