#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void vijener(bool isToShifr = true) {
    string fileNameAt, fileNameTo, keyWord;

    cout << "Введите имя файла(из которого считывать): ";
    cin >> fileNameAt;
    ifstream inputFile(fileNameAt, ios::binary);
    if (!inputFile) {
        cerr << "Не удалось открыть файл." << endl;
        inputFile.close();
        return;
    }

    cout << "Введите имя файла(в который записывать): ";
    cin >> fileNameTo;

    if (fileNameAt == fileNameTo) {
        cout << "Выберите разные файлы.";
        return;
    }

    ofstream outputFile(fileNameTo, ios::binary);
    if (!outputFile) {
        cerr << "Не удалось открыть файл." << endl;
        outputFile.close();
        return;
    }
    outputFile << "";

    cout << "Введите кодовое слово: ";
    cin >> keyWord;

    char character, keySimbol;
    int counter = 0;

    while (inputFile.get(character)) {
        keySimbol = keyWord[counter % keyWord.size()];
        counter++;
//        isToShifr ? outputFile.put(char((int(character) + int(keySimbol)) % 256)) :  outputFile.put(char((int(character) - int(keySimbol) + 256) % 256));
        isToShifr ? outputFile.put((character + keySimbol)) : outputFile.put(char(character - keySimbol));
    }

    cout << "\nУспешно!\n";
}

int main()
{
    setlocale(LC_ALL, "Russian");
    system("chcp 1251");

    int state = -1;

    while (state) {

        cout << "\n1 - Шифратор\n2 - Дешифратор\n0 - Выход\n";
        cin >> state;

        switch (state) {
        case 1: {
            vijener();
            break;
        }
        case 2: {
            vijener(false);
            break;
        }

        default:
            break;
        }
    }
}
