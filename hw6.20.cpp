#include <iostream>
using namespace std;

unsigned int removeBit(unsigned int n, int i) {
    unsigned int lower = n & ((1U << i) - 1);

    unsigned int upper = (n >> (i + 1)) << i;

    return upper | lower;
}

int main() {
    unsigned int n;
    int i;

    cout << "Enter nat number n: ";
    cin >> n;
    cout << "Enter i (starting from 0): ";
    cin >> i;

    if (i < 0 || i >= 32) {
        cout << "Invalid bit index." << endl;
        return 1;
    }

    unsigned int result = removeBit(n, i);
    cout << "Result after removing bit " << i << ": " << result << endl;

    return 0;
}
