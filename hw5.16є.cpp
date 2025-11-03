#include <iostream>
using namespace std;

double power(double x, int k) {
    double result = 1.0;
    for (int i = 0; i < k; ++i)
        result *= x;
    return result;
}

double approximateSum(double x, double epsilon) {
    if (x <= -1 || x >= 1) {
        cout << "eror" << endl;
        return 0;
    }

    double sum = 0.0;
    int k = 0;
    double term;

    do {
        term = power(x, k);
        if (k % 2 != 0) term = -term;
        if (abs(term) >= epsilon)
            sum += term;
        ++k;
    } while (abs(term) >= epsilon);

    return sum;
}

int main() {
    double x, epsilon;

    cout << "Enter x : ";
    cin >> x;
    cout << "Enter eps: ";
    cin >> epsilon;

    if (epsilon <= 0) {
        cout << "Eror" << endl;
        return 1;
    }

    double result = approximateSum(x, epsilon);
    cout << "Approximated sum = " << result << endl;

    return 0;
}
