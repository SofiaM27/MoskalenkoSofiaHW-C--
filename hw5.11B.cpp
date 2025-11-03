#include <iostream>
using namespace std;

double powerOfTwo(int k) {
    double result = 1.0;
    for (int i = 0; i < k; ++i)
        result *= 2;
    return result;
}

double computeSum(int n) {
    double sum = 0.0;
    double a_k = 1.0; // a_1
    double a_prev = 1.0; // a_2

    for (int k = 1; k <= n; ++k) {
        if (k == 1 || k == 2) {
            a_k = 1.0;
        } else {
            double factor = 1.0 + 1.0 / powerOfTwo(k);
            a_k = a_prev * factor;
        }

        sum += k / a_k;
        a_prev = a_k;
    }

    return sum;
}

int main() {
    int n;
    cout << "Enter n: ";
    cin >> n;

    if (n < 1) {
        cout << "n must be ≥ 1." << endl;
        return 1;
    }

    double result = computeSum(n);
    cout << "S" << n << " = " << result << endl;

    return 0;
}
