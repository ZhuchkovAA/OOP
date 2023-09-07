#include "Utils.h"

#include <iostream>
#include <string>

using namespace std;

void cinErr(const string title) {
    cin.clear();
    cin.ignore(32767, '\n');
    cout << "\nError!\n" << title;
}

void checkNameFile(string& nameFile) {
    if (nameFile.length() >= 4) {
        string extension = nameFile.substr(nameFile.length() - 4);
        if (extension == ".txt") return;
    }
    nameFile += ".txt";
}