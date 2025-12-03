#include <iostream>
using namespace std;

double power(double x, int k) {
    double result = 1.0;
    for (int i = 0; i < k; ++i)
        result *= x;
    return result;
}

unsigned long long factorial(int k) {
    unsigned long long result = 1;
    for (int i = 2; i <= k; ++i)
        result *= i;
    return result;
}

double sequence_d(double x, int k) {
    return power(x, k) / factorial(k);
}

int main() {
    double x;
    int n;

    cout << "Enter x: ";
    cin >> x;
    cout << "Enter number of terms to compute (n ≥ 1): ";
    cin >> n;

    if (n < 1) {
        cout << "Invalid input. n must be ≥ 1." << endl;
        return 1;
    }

    cout << "Sequence x_k = x^k / k!:" << endl;
    for (int k = 0; k < n; ++k) {
        cout << "x_" << k << " = " << sequence_d(x, k) << endl;
    }

    return 0;
}
