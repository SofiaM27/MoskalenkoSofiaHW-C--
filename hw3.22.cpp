#include <iostream>
#include <cmath>
using namespace std;

bool isInsideCylinder(double x, double y, double z, double r, double h) {
    bool withinHeight = (z >= 0 && z <= h);
    bool withinRadius = (x*x + y*y <= r*r);
    return withinHeight && withinRadius;
}

int main() {
    double x, y, z;
    double r, h;

    cout << "Enter coordinates (x, y, z): ";
    cin >> x >> y >> z;

    cout << "Enter r and h: ";
    cin >> r >> h;

    if (isInsideCylinder(x, y, z, r, h)) {
        cout << "The lies inside the cylinder." << endl;
    } else {
        cout << "The point NOT lie inside cylinder." << endl;
    }

    return 0;
}
