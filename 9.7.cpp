#include <iostream>
#include <vector>
using namespace std;

bool isPowerOfTwo(long long x) {
    if (x < 1) return false;
    while (x % 2 == 0) x /= 2;
    return x == 1;
}

bool isPowerOfThree(long long x) {
    if (x < 1) return false;
    while (x % 3 == 0) x /= 3;
    return x == 1;
}

int main() {
    int n;
    cout << "Enter the number of elements (n): ";
    cin >> n;

    if (n <= 0) {
        cout << "n must be a natural number." << endl;
        return 1;
    }

    vector<long long> arr(n);
    cout << "Enter " << n << " natural long integers:" << endl;
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    int countTwo = 0, countThree = 0;
    for (int i = 0; i < n; ++i) {
        if (isPowerOfTwo(arr[i])) ++countTwo;
        if (isPowerOfThree(arr[i])) ++countThree;
    }

    cout << "Number of powers of 2: " << countTwo << endl;
    cout << "Number of powers of 3: " << countThree << endl;

    return 0;
}
