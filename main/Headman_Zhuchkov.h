#pragma once
#include "Student_Zhuchkov.h"

class Headman_Zhuchkov : public Student_Zhuchkov {
private: 
	string phoneNumber;

public:
	Headman_Zhuchkov() : Student_Zhuchkov() {};
	void initHeadman(int idStudent);
	string getPhoneNumber();
	void setPhoneNumber(string phoneNumber);
	void printInfo() override;
	void writeToFile(string nameFile) override;
	friend ifstream& operator>>(ifstream& input, Headman_Zhuchkov& newHeadman);
};

