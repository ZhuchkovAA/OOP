#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>

using namespace std;

#include "Utils.h"
#include "Group.h"


int main()
{
    int state = -1;
    Group group;

    while (state) {
        cout << "\n1 - Add Student\n2 - Print listStudents\n3 - Write to File\n4 - Read from File\n5 - Clear listStudents\n0 - Exit\nEnter number: ";
        cin >> state;
        checkCin(&state, "Enter number : ");

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