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

public:
    Student_Zhuchkov() {
        this-> id = -1;
        this-> firstName = "";
        this-> lastName = "";
        this-> age = -1;
        this-> GPA = -1;
    };

    Student_Zhuchkov(int id, string firstName, string lastName, int age, double GPA) {
        this-> id = id;
        this-> firstName = firstName;
        this-> lastName = lastName;
        this-> age = age;
        this-> GPA = GPA;
    };

    int getId();
    string getFirstName();
    string getLastName();
    int getAge();
    double getGpa();

    void setId(int idStudent);
    void initStudent(int idStudent);
    void printInfo();
    void writeToFile(string nameFile);
    void readFromFile(string nameFile, int startRow);
};

