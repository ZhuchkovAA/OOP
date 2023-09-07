#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include "Utils.h"

class Student {
private:
    int id;
    string firstName;
    string lastName;
    int age;
    double GPA;

public:
    Student();
    void setId(int idStudent);
    void initStudent(int idStudent);
    int getId();
    string getFirstName();
    string getLastName();
    int getAge();
    double getGpa();
    void printInfo();
    void writeToFile(string nameFile);
    void readFromFile(string nameFile, int startRow);
};

