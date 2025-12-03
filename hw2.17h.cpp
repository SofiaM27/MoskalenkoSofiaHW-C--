#include <iostream>
#include <cmath>
using namespace std;

double arctg(double x) {
    return atan(x);
}

double arctg_derivative(double x) {
    return 1.0 / (1.0 + x * x);
}

int main() {
    double x;
    cout << "Enter x: ";
    cin >> x;

    double fx = arctg(x);
    double dfx = arctg_derivative(x);

    cout << "f(x) = arctg(x) = " << fx << endl;
    cout << "f'(x) = 1 / (1 + x^2) = " << dfx << endl;

    return 0;
}
