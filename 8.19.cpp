#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, m;
    cout << "Enter number of rows (n): ";
    cin >> n;
    cout << "Enter number of columns (m): ";
    cin >> m;

    vector<vector<int>> matrix(n, vector<int>(m));
    cout << "Enter matrix elements row by row:" << endl;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> matrix[i][j];

    int result = 0;
    bool found = false;

    for (int i = 0; i < n; ++i) {

        int rowMax = matrix[i][0];
        int colIndex = 0;
        for (int j = 1; j < m; ++j) {
            if (matrix[i][j] > rowMax) {
                rowMax = matrix[i][j];
                colIndex = j;
            }
        }

        bool isMinInCol = true;
        for (int k = 0; k < n; ++k) {
            if (matrix[k][colIndex] < rowMax) {
                isMinInCol = false;
                break;
            }
        }

        if (isMinInCol) {
            result = rowMax;
            found = true;
            break;
        }
    }

    cout << "Result: " << (found ? result : 0) << endl;
    return 0;
}
