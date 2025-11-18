#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cout << "Enter the number of scores (n ≥ 3): ";
    cin >> n;

    if (n < 3) {
        cout << "At least 3 scores are required." << endl;
        return 1;
    }

    vector<double> scores(n);
    cout << "Enter " << n << " scores:" << endl;
    for (int i = 0; i < n; ++i) {
        cin >> scores[i];
    }

    vector<double>::iterator maxIt = max_element(scores.begin(), scores.end());
    vector<double>::iterator minIt = min_element(scores.begin(), scores.end());

    scores.erase(maxIt);

    minIt = min_element(scores.begin(), scores.end());
    scores.erase(minIt);

    double sum = 0;
    for (int i = 0; i < scores.size(); ++i) {
        sum += scores[i];
    }

    double average = sum / scores.size();
    cout << "Final score for the athlete: " << average << endl;

    return 0;
}
