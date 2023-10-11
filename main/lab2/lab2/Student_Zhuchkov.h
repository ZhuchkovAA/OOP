#pragma once
#include<iostream>
#include<fstream>
#include<string>


class Student_Zhuchkov: public CObject
{
private:
	CString firstName;
	CString lastName;
	int age;
	double GPA;

public:
	DECLARE_SERIAL(Student_Zhuchkov)

    Student_Zhuchkov() {
        this->firstName = "";
        this->lastName = "";
        this->age = -1;
        this->GPA = -1;
    };

    Student_Zhuchkov(int id, CString firstName, CString lastName, int age, double GPA) {
        this->firstName = firstName;
        this->lastName = lastName;
        this->age = age;
        this->GPA = GPA;
    };

	virtual void input();
	
	virtual void output();

	virtual void Serialize(CArchive& ar);
};

