#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <limits>

using namespace std;

struct Point {
    double x, y;
};

double segmentLength(Point a, Point b) {
    return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
}

double rectanglePerimeter(Point topLeft, Point bottomRight) {
    double width = fabs(bottomRight.x - topLeft.x);
    double height = fabs(topLeft.y - bottomRight.y);
    return 2 * (width + height);
}

double circleArea(double radius) {
    return M_PI * radius * radius;
}

int main() {
    ifstream file("data/input.txt");
    if (!file.is_open()) {
        cerr << "Failed open file" << endl;
        return 1;
    }

    string line;
    double maxSegmentLength = -1;
    double maxRectanglePerimeter = -1;
    double minCircleArea = numeric_limits<double>::max();

    while (getline(file, line)) {
        stringstream ss(line);
        int type;
        ss >> type;

        if (type == 1) {
            Point a, b;
            ss >> a.x >> a.y >> b.x >> b.y;
            double len = segmentLength(a, b);
            if (len > maxSegmentLength) maxSegmentLength = len;
        } else if (type == 2) {
            Point topLeft, bottomRight;
            ss >> topLeft.x >> topLeft.y >> bottomRight.x >> bottomRight.y;
            double perim = rectanglePerimeter(topLeft, bottomRight);
            if (perim > maxRectanglePerimeter) maxRectanglePerimeter = perim;
        } else if (type == 3) {
            Point center;
            double radius;
            ss >> center.x >> center.y >> radius;
            double area = circleArea(radius);
            if (area < minCircleArea) minCircleArea = area;
        }
    }

    file.close();

    cout << "The longest segment: " << maxSegmentLength << endl;
    cout << "The largest perimeter of a rectangle: " << maxRectanglePerimeter << endl;
    cout << "The smallest area of area circle: " << minCircleArea << endl;

    return 0;
}
