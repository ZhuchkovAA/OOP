#pragma once
#include "Student_Zhuchkov.h"

class Headman_Zhuchkov : Student_Zhuchkov {
private: 
	string phoneNumber;

public:
	void initHeadman(int idStudent);
	string getPhoneNumber();
	void setPhoneNumber(string phoneNumberHeadman);
};

