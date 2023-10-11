#include "pch.h"
#include "Headman_Zhuchkov.h"

IMPLEMENT_SERIAL(Headman_Zhuchkov, Student_Zhuchkov, VERSIONABLE_SCHEMA | 0)

using namespace std;

void Headman_Zhuchkov::input() {
    string phoneNumber;
    Student_Zhuchkov::input();
    cout << "Введите номер телефона: ";
    cin.ignore();
    getline(cin, phoneNumber);
    this->phoneNumber = phoneNumber.c_str();
}


void Headman_Zhuchkov::output() {
    cout << endl;
    cout << "Староста" << endl;
    Student_Zhuchkov::output();
    cout << "Номер телефона: "
        << this->phoneNumber << endl << endl;
}

void Headman_Zhuchkov::Serialize(CArchive& ar) {

    Student_Zhuchkov::Serialize(ar);

	if (ar.IsStoring()) {
		ar << phoneNumber;
	}
	else {
        ar >> phoneNumber;
	}
}