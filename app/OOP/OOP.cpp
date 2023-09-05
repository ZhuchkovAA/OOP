#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>

using namespace std;

void checkCin(void* value, string title) {
    while (cin.fail()) {
        cin.clear();
        cin.ignore(32767, '\n');
        cout << "\nError!\n" << title;
        cin >> value;
    }
}

void checkNameFile(string& nameFile) {
    if (nameFile.length() >= 4) {
        string extension = nameFile.substr(nameFile.length() - 4);
        if (extension == ".txt") return;
    }
    nameFile += ".txt";
}

int createId() {
    static int id = 0;
    return id++;
};

class Student {
private:
    int id;
    string firstName;
    string lastName;
    int age;
    double GPA;

public:
    void initStudent( int valueId ) {
        id = valueId;

        cout << "Input firstname:\n";
        cin >> firstName;

        cout << "Input lastName:\n";
        cin >> lastName;

        cout << "Input age:\n";
        cin >> age;
        checkCin(&age, "Input age:");

        cout << "Input GPA:\n";
        cin >> GPA;
        checkCin(&GPA, "Input GPA:");
    };

    int getId() {
        return id;
    };

    string getFirstName() {
        return firstName;
    };

    string getLastName() {
        return lastName;
    };

    int getAge() {
        return age;
    };

    double getGpa() {
        return GPA;
    };

    void printInfo() {
        cout << "\nid: " << id << "\nfirstname: " << firstName <<
            "\nlastname: " << lastName << "\nage: " << age <<
            "\nGPA: " << GPA << "\n";
    };

    friend istream& operator>>(istream& input, Student& student) {
        input >> student.id >> student.firstName >> student.lastName >> student.age >> student.GPA;
        return input;
    }

    void writeToFile(string nameFile) {
        ofstream outputFile(nameFile, ios::app);

        if (!outputFile) {
            cerr << "\nError open. Try again\n" << endl;
            return;
        }

        outputFile << 
            id << endl <<
            firstName << endl <<
            lastName << endl <<
            age << endl <<
            GPA<< endl;

        outputFile.close(); 
    }

    void readFromFile(string nameFile, int startRow = 0) {
        string line;
        ifstream inputFile(nameFile);

        if (!inputFile) {
            cerr << "\nError open. Try again\n" << endl;
            return;
        }
        
        for (int i = 0; i < startRow * 5; i++) { getline(inputFile, line); }

        getline(inputFile, line);
        id = stoi(line);
        getline(inputFile, line);
        firstName = line;
        getline(inputFile, line);
        lastName = line;
        getline(inputFile, line);
        age = stoi(line);
        getline(inputFile, line);
        GPA = stod(line);

        inputFile.close();
    }
};

int main()
{
    int state = -1;
    vector<Student> listStudents;
    string nameFile;
    Student newStudent;

    while (state) {
        cout << "\n1 - Add Student\n2 - Print Students Info\n3 - Write to File\n4 - Read from File\n5 - Clear listStudents\n0 - Exit\nEnter number: ";
        cin >> state;
        checkCin(&state, "Enter number : ");

        switch (state) {
            case 1: {
                newStudent.initStudent(createId());
                listStudents.push_back(newStudent);
                break;
            }
            case 2: {
                for_each(listStudents.begin(), listStudents.end(), [](Student& item) {
                    item.printInfo();
                    });
                break; 
            }
            case 3: {
                cout << "Input name File: ";
                cin >> nameFile;
                checkNameFile(nameFile);
 
                ofstream outputFile(nameFile);

                if (!outputFile) { cerr << "\nError open. Try again\n" << endl; break; }

                outputFile << "";

                for_each(listStudents.begin(), listStudents.end(), [nameFile](Student& item) {
                    item.writeToFile(nameFile);
                });
                break;
            }
            case 4: {
                listStudents.clear();

                int lineCount = 0;
                string line;

                cout << "Input name File: ";
                cin >> nameFile;
                checkNameFile(nameFile);
                ifstream inputFile(nameFile);
                if (!inputFile) { cerr << "\nError open. Try again\n" << endl; break; }

                while (getline(inputFile, line)) { lineCount++; }

                for (int i = 0; i < lineCount / 5; i++) {
                    newStudent.readFromFile(nameFile, i);
                    listStudents.push_back(newStudent);
                }
                break; 
            }
            case 5: {
                listStudents.clear();
            }
            default:
                break;
            }
        }
    return 0;
}