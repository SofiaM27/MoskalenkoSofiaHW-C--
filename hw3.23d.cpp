#include <iostream>
using namespace std;

double sReLU(double tl, double tr, double aL, double aR, double x) {
    if (x <= tl)
        return tl + aL * (x - tl);
    else if (x < tr)
        return x;
    else
        return tr + aR * (x - tr);
}

double sReLU_derivative(double tl, double tr, double aL, double aR, double x) {
    if (x < tl)
        return aL;
    else if (x < tr)
        return 1.0;
    else
        return aR;
}

int main() {
    double tl, tr, aL, aR, x;

    cout << "Enter tl, tr, aL, aR, and x: ";
    cin >> tl >> tr >> aL >> aR >> x;

    double fx = sReLU(tl, tr, aL, aR, x);
    double dfx = sReLU_derivative(tl, tr, aL, aR, x);

    cout << "sReLU(x) = " << fx << endl;
    cout << "sReLU'(x) = " << dfx << endl;

    return 0;
}
