#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <windows.h>

using namespace std;

int main() {
    SetConsoleOutputCP(65001);

    string input;
    double A, B, C;

    cout << "Введіть рядок типу: A=xxx.xxx B=xxExxx C=xxx.xxxx\n";
    getline(cin, input);

    size_t posA = input.find("A=");
    size_t posB = input.find("B=");
    size_t posC = input.find("C=");

    string strA = input.substr(posA + 2, posB - (posA + 2));
    string strB = input.substr(posB + 2, posC - (posB + 2));
    string strC = input.substr(posC + 2);

    stringstream ssA(strA), ssB(strB), ssC(strC);
    ssA >> A;
    ssB >> B;
    ssC >> C;

    double arithmeticMean = (A + B + C) / 3.0;
    double harmonicMean = 3.0 / (1.0/A + 1.0/B + 1.0/C);

    cout << fixed << setprecision(6);
    cout << "Середнє арифметичне (fixed): " << arithmeticMean << endl;
    cout << "Середнє гармонічне (fixed): " << harmonicMean << endl;

    cout << scientific << setprecision(6);
    cout << "Середнє арифметичне (scientific): " << arithmeticMean << endl;
    cout << "Середнє гармонічне (scientific): " << harmonicMean << endl;

    return 0;
}
