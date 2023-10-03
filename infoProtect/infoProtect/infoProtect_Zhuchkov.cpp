#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <Windows.h>

using namespace std;

void vijener(string& inputFileName, string& keyWord, bool isToShifr, string outputFileName = "") {

    char character, keySimbol;
    int counter = 0;

    ifstream inputFile(inputFileName, ios::binary);

    if (outputFileName != "") {
        ofstream outputFile(outputFileName, ios::binary);
        outputFile << "";

        while (inputFile.get(character)) {
            keySimbol = keyWord[counter % keyWord.size()];
            counter++;
            isToShifr ? outputFile.put((character + keySimbol)) : outputFile.put(char(character - keySimbol));
        }

        cout << "\nУспешно!\n";

        outputFile.close();
    }
    else {
        while (inputFile.get(character)) {
            keySimbol = keyWord[counter % keyWord.size()];
            counter++;
            if (isToShifr)
                cout << unsigned char(character + keySimbol);
            else
                cout << unsigned char(character - keySimbol);
        }
    }

    inputFile.close();
}

void vijenerOptions(bool isToShifr = true) {
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

    cout << "Введите кодовое слово: ";
    cin >> keyWord;

    vijener(fileNameAt, keyWord, isToShifr, fileNameTo);
}

void vijenerUpload(string& cipherFileName, string& key) {

    basic_ifstream <unsigned char> inputFile;
    ofstream outputFile;

    string outputFileName;
    cout << "Введите путь к файлу для записи: " << endl;
    cin >> outputFileName;
    
    inputFile.open(cipherFileName, ios::binary);
    outputFile.open(outputFileName, ios::binary);
    
    unsigned char inchar;
    int keyIndex = 0;
    
    while (inputFile.get(inchar)) {
        unsigned char outchar = inchar - key[keyIndex % key.length()];
        // cout << outchar;
        outputFile << outchar;
        keyIndex++;
    }
    inputFile.close();
    outputFile.close();
}

void maxFrequencyN(vector<int> frequency, int N) {
    unordered_map <int, int> frequencyRef;
    for (int i = 0; i < 256; i++)
        frequencyRef.insert({ frequency[i], i });
    sort(frequency.begin(), frequency.end(), greater<int>());
    for (int i = 0; i < N; i++) cout << i + 1 << ". " << char(frequencyRef[frequency[i]]) << ", количество: " << frequency[i] << ' ' << frequencyRef[frequency[i]] << endl;
}

int mostPopular(vector<int> frequency) {
    int mostPopularIdx = 0;
    int maxFrequency = 0;
    for (int i = 0; i < frequency.size(); i++)
        if (frequency[i] > maxFrequency) {
            maxFrequency = frequency[i];
            mostPopularIdx = i;
        }
    return mostPopularIdx;
}

vector<int> getFrequency(vector<unsigned char> text, bool isShow = false) {
    vector<int> frequency(256, 0);
    for (auto simbol : text) {
        frequency[simbol]++;
    }
    if (isShow) maxFrequencyN(frequency, 5);
    return frequency;
}

float getIC(vector<unsigned char>& text, bool isShow = false) {
    vector<int> frequency;
    frequency = getFrequency(text, isShow);

    float IC = 0;
    float sum = 0;

    for (int count : frequency)
        sum += count * (count - 1);

    IC = sum / (text.size() * (text.size() - 1));
    return IC;
}

int getKeyLength(vector<unsigned char> textCipher, double etalonIC) {

    int intStart, intEnd;
    cout << "Введите диапазон символов:" << endl;
    cin >> intStart; cin >> intEnd;

    int keyLenght = 0;
    double maxIC = 1, IC = 0;

    for (int length = intStart; length <= intEnd; length++) {
        vector<unsigned char> refText;

        cout << "Анализ " << length << "-значного ключа..." << endl;
        for (int i = 0; i < textCipher.size(); i++) {
            if (i % length == 0)
                refText.push_back(textCipher[i]);
        }

        IC = getIC(refText);
        cout << "Полученый индекс соответсвия: " << IC << endl << endl;

        if ( abs(IC - etalonIC) < maxIC) {
            maxIC = IC - etalonIC;
            keyLenght = length;
        }
    }

    cout << "\nПредполагаемая длина ключа: " << keyLenght << endl;
    return keyLenght;
}

string getKey(vector<unsigned char> text, int keyLength, int mostPopular) {
    string key;
    vector<unsigned char> group;

    for (int i = 0; i < keyLength; i++) {

        for (int j = i; j < text.size(); j += keyLength) {
            group.push_back(text[j]);
        }

        vector<int> frequency = getFrequency(group);

        char likelyKeyChar;
        int maxFrequency = 0;

        for (int j = 0; j < 256; j++) {
            if (frequency[j] > maxFrequency) {
                maxFrequency = frequency[j];
                likelyKeyChar = static_cast<char>(j);
            }
        }

        key += char(likelyKeyChar - mostPopular);
        group.clear();
    }

    return key;
}

void ref() {

    string cipherFileName, etalonFileName;

    cout << "Введите имя файла с закодированным текстом: " << endl;
    cin >> cipherFileName;
    cout << "Введите имя файла с эталонным текстом: " << endl;
    cin >> etalonFileName;

    ifstream inputTextCipher(cipherFileName, ios::binary);
    vector<unsigned char> textCipher((istreambuf_iterator<char>(inputTextCipher)), istreambuf_iterator<char>());

    ifstream inputTextEtalon(etalonFileName, ios::binary);
    vector<unsigned char> textEtalon((istreambuf_iterator<char>(inputTextEtalon)), istreambuf_iterator<char>());

    string key;

    int keyLength = getKeyLength(textCipher, getIC(textEtalon, true));
    key = getKey(textCipher, keyLength, mostPopular(getFrequency(textEtalon)));
    cout << "Ключ: " << key << endl;
    // vijener(cipherFileName, key, false);
    vijenerUpload(cipherFileName, key);
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");
    system("chcp 1251");

    int state = -1;

    while (state) {

        cout << "\n1 - Шифратор\n2 - Дешифратор\n3 - 2 Лаба\n0 - Выход\n";
        cin >> state;

        switch (state) {
        case 1: {
            vijenerOptions();
            break;
        }
        case 2: {
            vijenerOptions(false);
            break;
        }
        case 3: 
            ref();
            break;
        default:
            break;
        }
    }
}
