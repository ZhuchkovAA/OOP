// del /s /q /f *.exe *.dll *.ncb *.sdf *.obj *.lib *.pdb *.ipch *.pch *.idb *.bsc *.exp *.ilk *.aps *.log *.tlog *.db

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>

using namespace std;

#include "Utils.h"
#include "Group_Zhuchkov.h"

string checkType(void* value) {
    return typeid(value).name();
}

int main()
{
    setlocale(LC_ALL, "Russian");
    system("chcp 1251");

    int state = -1;
    Group_Zhuchkov group;

    while (state) {
        cout << "\n1 - Добавить Студента\n2 - Вывести список Студентов\n3 - Записать в Файл\n4 - Считать из Файла\n5 - Отчистить список Студентов\n0 - Выход\nВведите число: ";

        while (!(cin >> state)) cinErr("Введите число:");

        switch (state) {
        case 1: {
            group.addStudent();
            break;
        }
        case 2: {
            group.printList();
            break;
        }
        case 3: {
            group.writeListToFile();
            break;
        }
        case 4: {
            group.readListFromFile();
            break;
        }
        case 5: {
            group.removeList();
            break;
        }
        default:
            break;
        }
    }

    return 0;
}