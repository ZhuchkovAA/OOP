#pragma once
#include "Student_Zhuchkov.h"

class Headman_Zhuchkov:
    public Student_Zhuchkov
{
private:
	CString phoneNumber;
public:
	DECLARE_SERIAL(Headman_Zhuchkov)
	Headman_Zhuchkov() {};

	virtual ~Headman_Zhuchkov() {};

	void input() override;
	void output() override;

	virtual void Serialize(CArchive& ar);
};

