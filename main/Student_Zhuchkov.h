#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include "Utils.h"

class Student_Zhuchkov {
private:
    int id;
    string firstName;
    string lastName;
    int age;
    double GPA;
    bool isHeadman;

public:
    Student_Zhuchkov() {
        this-> id = -1;
        this-> firstName = "";
        this-> lastName = "";
        this-> age = -1;
        this-> GPA = -1;
        this-> isHeadman = false;
    };

    Student_Zhuchkov(int id, string firstName, string lastName, int age, double GPA) {
        this-> id = id;
        this-> firstName = firstName;
        this-> lastName = lastName;
        this-> age = age;
        this-> GPA = GPA;
        this-> isHeadman = false;
    };

    int getId();
    string getFirstName();
    string getLastName();
    int getAge();
    double getGpa();
    bool getIsHeadman();

    void setId(int id);
    void setFirstName(string firstName);
    void setLastName(string lastName);
    void setAge(int age);
    void setGpa(double GPA);
    void setIsHeadman(bool isHeadman);

    void initStudent(int idStudent);
    virtual void printInfo();
    virtual void writeToFile(string nameFile);

    friend ifstream& operator>>(ifstream& input, shared_ptr<Student_Zhuchkov>& student);
};