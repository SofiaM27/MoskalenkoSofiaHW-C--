#include <iostream>
using namespace std;

int countOnes(unsigned int x) {
    int count = 0;
    while (x) {
        count += x & 1;
        x >>= 1;
    }
    return count;
}

int countMatchingBits(unsigned int a, unsigned int b) {
    int count = 0;
    for (int i = 0; i < 32; ++i) {
        if (((a >> i) & 1) == ((b >> i) & 1))
            ++count;
    }
    return count;
}

int main() {
    unsigned int t, p;

    cout << "Enter nat number t: ";
    cin >> t;
    cout << "Enter nat number p: ";
    cin >> p;

    unsigned int commonOnes = t & p;
    int countCommonOnes = countOnes(commonOnes);

    int countAllMatching = countMatchingBits(t, p);

    cout << "Number of common 1-bits: " << countCommonOnes << endl;
    cout << "Number of matching bits (0 or 1): " << countAllMatching << endl;

    return 0;
}
