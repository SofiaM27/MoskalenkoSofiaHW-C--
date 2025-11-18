#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, m;
    cout << "Enter number of rows (n): ";
    cin >> n;
    cout << "Enter number of columns (m): ";
    cin >> m;

    vector<vector<double>> matrix(n, vector<double>(m));
    cout << "Enter matrix elements row by row:" << endl;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> matrix[i][j];


    vector<vector<double>> newMatrix;
    for (int i = 0; i < matrix.size(); ++i) {
        newMatrix.push_back(matrix[i]);

        if (i % 2 == 0) {
            vector<double> newRow(m, 0.0);
            newMatrix.push_back(newRow);
        }
    }


    cout << "Modified matrix:" << endl;
    for (int i = 0; i < newMatrix.size(); ++i) {
        for (int j = 0; j < m; ++j) {
            cout << newMatrix[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
