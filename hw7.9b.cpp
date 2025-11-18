#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Enter the number of elements n:";
    cin >> n;

    if (n <= 0) {
        cout << "n must be a natural number." << endl;
        return 1;
    }

    double minValue;
    cout << " Enter element a1:";
    cin >> minValue;

    for (int i = 2; i <= n; ++i) {
        double ai;
        cout << "Enter element a1" << i << ": ";
        cin >> ai;
        if (ai < minValue) {
            minValue = ai;
        }
    }

    cout << "Minimum value: " << minValue << endl;
    return 0;
}
