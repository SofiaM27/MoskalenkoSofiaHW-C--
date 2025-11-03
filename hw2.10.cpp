#include <iostream>
#include <cmath>
using namespace std;

double radiansToDegrees(double radians) {
    return radians * 180.0 / M_PI;
}

double calculateAngle(double a, double b, double c) {
    return acos((a*a + b*b - c*c) / (2 * a * b));
}

int main() {
    double a, b, c;

    cout << "Enter the lengths sides(a, b, c): ";
    cin >> a >> b >> c;

    if (a + b <= c || a + c <= b || b + c <= a) {
        cout << "Not." << endl;
        return 1;
    }

    double alpha_rad = calculateAngle(b, c, a);
    double beta_rad  = calculateAngle(a, c, b);
    double gamma_rad = calculateAngle(a, b, c);

    double alpha_deg = radiansToDegrees(alpha_rad);
    double beta_deg  = radiansToDegrees(beta_rad);
    double gamma_deg = radiansToDegrees(gamma_rad);

    // Вивід результатів
    cout << "\nКути трикутника:" << endl;
    cout << "Альфа: " << alpha_rad << " рад ≈ " << alpha_deg << "град" << endl;
    cout << "Бета:  " << beta_rad  << " рад ≈ " << beta_deg  << "град" << endl;
    cout << "Гамма: " << gamma_rad << " рад ≈ " << gamma_deg << "град" << endl;

    return 0;
}
