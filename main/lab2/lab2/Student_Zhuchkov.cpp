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
	cout << "������� ��� ��������: ";
	cin.ignore();
	getline(cin, firstName);
	this->firstName = firstName.c_str();
	cout << "������� ������� ��������: ";
	cin.ignore();
	getline(cin, lastName);
	this->lastName = lastName.c_str();
	cout << "������� ������� ��������: ";
	while (!(cin >> age)) cinErr("������������ ������. ������� �������: ");
	this->age = age;
	cout << "������� ������� ���� ��������: ";
	while (!(cin >> GPA)) cinErr("������������ ������. ������� ������� ����: ");
	this->GPA = GPA;
}

void Student_Zhuchkov::output()
{
	cout  << "���: " << this->firstName << endl;
	cout << "�������: " << this->lastName << endl;
	cout << "�������: " << this->age << endl;
	cout << "������� ����: " << this->GPA << endl << endl;
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

