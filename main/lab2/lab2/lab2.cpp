// lab2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include<Windows.h>
#include "pch.h"
#include "framework.h"
#include "lab2.h"
#include "Group_Zhuchkov.h"
#include "Utils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Единственный объект приложения

CWinApp theApp;
using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    system("chcp 1251");

    int state = -1;
    Group_Zhuchkov group;

    while (state) {
        cout << "\n1 - Добавить Студента\n2 - Добавить Старосту\n3 - Вывести полный список\n4 - Записать в Файл\n5 - Считать из Файла\n6 - Отчистить список Студентов\n0 - Выход\nВведите число: ";

        while (!(cin >> state)) cinErr("Введите число:");

        switch (state) {
        case 1: {
            group.addStudent();
            break;
        }
        case 2: {
            group.addHeadman();
            break;
        }
        case 3: {
            group.printList();
            break;
        }
        case 4: {
            cout << "Введите название файла: ";
            string filename;
            cin.ignore();
            getline(cin, filename);

            group.writeListToFile(filename.c_str());
            break;
        }
        case 5: {
            cout << "Введите название файла: ";
            string filename;
            cin.ignore();
            getline(cin, filename);

            group.readListFromFile(filename.c_str());
            break;
        }
        case 6: {
            group.removeList();
            break;
        }
        default:
            break;
        }
    }

    return 0;
}