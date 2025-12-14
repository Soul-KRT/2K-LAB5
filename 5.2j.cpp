#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>   
#include <cctype>  
#include <windows.h>
using namespace std;

int main() {
    SetConsoleOutputCP(65001);   // вывод в UTF-8
    SetConsoleCP(65001);         // ввод в UTF-8
    setvbuf(stdout, nullptr, _IOFBF, 1000);
    setlocale(LC_ALL, "Russian");

    const char* filename = "mytext.txt";   
    ifstream f(filename);
    if (!f) {
        cerr << "Не удалось открыть файл: " << filename << endl;
        return 1;
    }

    map<string, int> freq;

    const size_t MAXLEN = 1000;
    char text[MAXLEN];

    while (f.getline(text, MAXLEN)) {
        // strtok режет строку по указанным разделителям
        char* context = nullptr;
        char* substr = strtok_s(text, " .,:-:!;?", &context);
        while (substr != nullptr) {
            string word = substr;

            // в нижний регистр
            std::transform(word.begin(), word.end(), word.begin(),
                [](unsigned char c) { return std::tolower(c); });

            if (!word.empty())
                ++freq[word];

            substr = strtok_s(nullptr, " .,:-:!;?", &context);
        }
    }

    f.close();

    // переносим подходящие слова в вектор для сортировки
    vector<pair<string, int>> words;
    for (const auto& p : freq) {
        const string& w = p.first;
        int count = p.second;
        if (w.size() > 3 && count >= 7) {
            words.push_back(p);
        }
    }

    // сортировка по убыванию частоты, при равной частоте по слову
    std::sort(words.begin(), words.end(),
        [](const auto& a, const auto& b) {
            if (a.second != b.second)
                return a.second > b.second;   // по убыванию частоты
            return a.first < b.first;         // по алфавиту
        });

    // вывод в одну строку: слово пробел частота пробел ...
    for (const auto& p : words) {
        cout << p.first << " " << p.second << " ";
    }
    cout << endl;

    return 0;
}
