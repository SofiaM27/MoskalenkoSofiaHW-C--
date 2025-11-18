#include <iostream>
#include <string>
using namespace std;

struct Seminar {
    string subject;
    string teacher;
    string groupNumber;
    string weekday;
    string time;
    string room;
};

void inputSeminar(Seminar &s) {
    cout << "Enter subject: ";
    getline(cin, s.subject);

    cout << "Enter teacher: ";
    getline(cin, s.teacher);

    cout << "Enter group number: ";
    getline(cin, s.groupNumber);

    cout << "Enter weekday: ";
    getline(cin, s.weekday);

    cout << "Enter time (e.g. 14:00–15:30): ";
    getline(cin, s.time);

    cout << "Enter room: ";
    getline(cin, s.room);
}

void printSeminar(const Seminar &s) {
    cout << "\n--- Seminar Info ---" << endl;
    cout << "Subject: " << s.subject << endl;
    cout << "Teacher: " << s.teacher << endl;
    cout << "Group: " << s.groupNumber << endl;
    cout << "Day: " << s.weekday << endl;
    cout << "Time: " << s.time << endl;
    cout << "Room: " << s.room << endl;
}

int main() {
    Seminar s;
    cout << "Enter seminar details:" << endl;
    inputSeminar(s);
    printSeminar(s);
    return 0;
}
