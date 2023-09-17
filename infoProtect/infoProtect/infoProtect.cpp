#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void vijener(bool isShifr = true) {
    string fileNameAt, fileNameTo, keyWord;

    cout << "Введите имя файла(1): ";
    cin >> fileNameAt;
    ifstream inputFile(fileNameAt);
    if (!inputFile) {
        cerr << "Не удалось открыть файл." << endl;
        inputFile.close();
        return;
    }

    cout << "Введите имя файла(2): ";
    cin >> fileNameTo;
    ofstream outputFile(fileNameTo);
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
        isShifr ? outputFile.put(char((int(character) - int(keySimbol) + 128) % 128)) : outputFile.put(char((int(character) + int(keySimbol)) % 128));
    }
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
