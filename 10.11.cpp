#include <iostream>
#include <vector>
using namespace std;

struct Person {
    string surname;
    string city;
    string street;
    string building;
    string apartment;
};

bool sameAddressDifferentCity(const Person &a, const Person &b) {
    return a.city != b.city &&
           a.street == b.street &&
           a.building == b.building &&
           a.apartment == b.apartment;
}

int main() {
    int n;
    cout << "Enter number of people: ";
    cin >> n;

    vector<Person> P(n);
    for (int i = 0; i < n; ++i) {
        cout << "Person " << i + 1 << ":\n";
        cout << "Surname: ";
        cin >> P[i].surname;
        cout << "City: ";
        cin >> P[i].city;
        cout << "Street: ";
        cin >> P[i].street;
        cout << "Building: ";
        cin >> P[i].building;
        cout << "Apartment: ";
        cin >> P[i].apartment;
    }

    bool found = false;
    for (int i = 0; i < n && !found; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (sameAddressDifferentCity(P[i], P[j])) {
                cout << "\nMatch found:\n";
                cout << P[i].surname << " from " << P[i].city << endl;
                cout << P[j].surname << " from " << P[j].city << endl;
                found = true;
                break;
            }
        }
    }

    if (!found) {
        cout << "\nNo matching residents found." << endl;
    }

    return 0;
}
