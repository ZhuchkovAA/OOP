#include "Utils.h"

#include <iostream>
#include <string>

using namespace std;

void checkCin(void* value, string title) {
    while (cin.fail()) {
        cin.clear();
        cin.ignore(32767, '\n');
        cout << "\nError!\n" << title;
        cin >> value;
    }
};

void checkNameFile(string& nameFile) {
    if (nameFile.length() >= 4) {
        string extension = nameFile.substr(nameFile.length() - 4);
        if (extension == ".txt") return;
    }
    nameFile += ".txt";
}