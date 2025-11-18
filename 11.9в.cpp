#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ifstream F("F.txt");
    ofstream H("H.txt"), G("G.txt");


    if (!F.is_open() || !H.is_open() || !G.is_open()) {
        cerr << "error" << endl;
        return 1;
    }

    vector<int> positive, negative;
    int num;

    while (F >> num) {
        if (num > 0)
            positive.push_back(num);
        else if (num < 0)
            negative.push_back(num);
    }

    F.close();

    if (positive.size() != negative.size()) {
        cout << "error" << endl;
        return 0;
    }


    if (positive.size() < 2 || negative.size() < 2) {
        cout << "error" << endl;
        return 0;
    }


    int minPairs = min(positive.size() / 2, negative.size() / 2);

    for (int i = 0; i < minPairs; i++) {
        H << positive[2*i] << " " << positive[2*i + 1] << " ";
        H << negative[2*i] << " " << negative[2*i + 1] << " ";
    }

    H.close();

    ifstream H_read("H.txt");
    int count = 0;
    while (H_read >> num) {
        G << num << " ";
        count++;
    }
    H_read.close();


    int remainingPos = positive.size() - 2 * minPairs;
    int remainingNeg = negative.size() - 2 * minPairs;

    if (remainingPos > 0 || remainingNeg > 0) {
        cout << "last numb ";


        for (int i = 2 * minPairs; i < positive.size(); i++) {
            cout << positive[i] << " ";
        }


        for (int i = 2 * minPairs; i < negative.size(); i++) {
            cout << negative[i] << " ";
        }
        cout << endl;
    }

    cout << "done" << endl;

    return 0;
}