#include <iostream>
#include <cmath>
#include <stdexcept>
#include <iomanip>


class Vector3 {
private:
    double data[3];

public:
    Vector3() : data{0.0, 0.0, 0.0} {}

    Vector3(double x, double y, double z) : data{x, y, z} {}

    double& operator[](int index) {
        if (index < 0 || index >= 3) {
            throw std::out_of_range("Vector index out of bounds.");
        }
        return data[index];
    }

    const double& operator[](int index) const {
        if (index < 0 || index >= 3) {
            throw std::out_of_range("Vector index out of bounds.");
        }
        return data[index];
    }

    Vector3& operator+=(const Vector3& other) {
        data[0] += other.data[0];
        data[1] += other.data[1];
        data[2] += other.data[2];
        return *this;
    }

    Vector3& operator-=(const Vector3& other) {
        data[0] -= other.data[0];
        data[1] -= other.data[1];
        data[2] -= other.data[2];
        return *this;
    }
};

Vector3 operator+(const Vector3& v1, const Vector3& v2) {
    return Vector3(v1[0] + v2[0], v1[1] + v2[1], v1[2] + v2[2]);
}

Vector3 operator-(const Vector3& v1, const Vector3& v2) {
    return Vector3(v1[0] - v2[0], v1[1] - v2[1], v1[2] - v2[2]);
}

Vector3 operator*(const Vector3& v, double scalar) {
    return Vector3(v[0] * scalar, v[1] * scalar, v[2] * scalar);
}

Vector3 operator*(double scalar, const Vector3& v) {
    return v * scalar;
}

double dot(const Vector3& v1, const Vector3& v2) {
    return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

std::ostream& operator<<(std::ostream& os, const Vector3& v) {
    os << "(" << v[0] << ", " << v[1] << ", " << v[2] << ")";
    return os;
}

double abs(const Vector3& v) {
    return std::sqrt(dot(v, v));
}


class Matrix3 {
private:
    double data[3][3];

public:
    Matrix3() {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                data[i][j] = 0.0;
            }
        }
    }

    Matrix3(double val) : Matrix3() {
        if (val == 1.0) {
            data[0][0] = data[1][1] = data[2][2] = 1.0;
        }
    }

    Matrix3(double a00, double a01, double a02,
            double a10, double a11, double a12,
            double a20, double a21, double a22) :
            data{{a00, a01, a02}, {a10, a11, a12}, {a20, a21, a22}} {}


    double* operator[](int row) {
        if (row < 0 || row >= 3) {
            throw std::out_of_range("Matrix row index out of bounds.");
        }
        return data[row];
    }

    const double* operator[](int row) const {
        if (row < 0 || row >= 3) {
            throw std::out_of_range("Matrix row index out of bounds.");
        }
        return data[row];
    }

    Matrix3& operator+=(const Matrix3& other) {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                data[i][j] += other.data[i][j];
            }
        }
        return *this;
    }

    double det() const {
        double a = data[0][0], b = data[0][1], c = data[0][2];
        double d = data[1][0], e = data[1][1], f = data[1][2];
        double g = data[2][0], h = data[2][1], i = data[2][2];

        return a * (e * i - f * h) - b * (d * i - f * g) + c * (d * h - e * g);
    }
};

Matrix3 operator+(const Matrix3& m1, const Matrix3& m2) {
    Matrix3 result;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            result[i][j] = m1[i][j] + m2[i][j];
        }
    }
    return result;
}

Matrix3 operator*(const Matrix3& m, double scalar) {
    Matrix3 result;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            result[i][j] = m[i][j] * scalar;
        }
    }
    return result;
}

Vector3 operator*(const Matrix3& m, const Vector3& v) {
    Vector3 result;
    for (int i = 0; i < 3; ++i) {
        double sum = 0.0;
        for (int j = 0; j < 3; ++j) {
            sum += m[i][j] * v[j];
        }
        result[i] = sum;
    }
    return result;
}

Matrix3 operator*(const Matrix3& m1, const Matrix3& m2) {
    Matrix3 result;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            double sum = 0.0;
            for (int k = 0; k < 3; ++k) {
                sum += m1[i][k] * m2[k][j];
            }
            result[i][j] = sum;
        }
    }
    return result;
}

std::ostream& operator<<(std::ostream& os, const Matrix3& m) {
    os << std::fixed << std::setprecision(2);
    for (int i = 0; i < 3; ++i) {
        os << "| ";
        for (int j = 0; j < 3; ++j) {
            os << std::setw(6) << m[i][j] << (j == 2 ? "" : " ");
        }
        os << " |" << (i == 2 ? "" : "\n");
    }
    return os;
}

double abs(const Matrix3& m) {
    double sum_of_squares = 0.0;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            sum_of_squares += m[i][j] * m[i][j];
        }
    }
    return std::sqrt(sum_of_squares);
}

int main() {
    std::cout << "--- Клас Vector3 ---\n";
    Vector3 v1(1.0, 2.0, 3.0);
    Vector3 v2(4.0, 5.0, 6.0);
    double scalar = 2.5;

    std::cout << "v1: " << v1 << "\n";
    std::cout << "v2: " << v2 << "\n";

    Vector3 v_sum = v1 + v2;
    std::cout << "v1 + v2 = " << v_sum << "\n";

    Vector3 v_mul_scalar = v1 * scalar;
    std::cout << "v1 * 2.5 = " << v_mul_scalar << "\n";

    double d_prod = dot(v1, v2);
    std::cout << "Dot product (v1 * v2) = " << d_prod << "\n";

    double norm_v1 = abs(v1);
    std::cout << "Norm ||v1|| = " << norm_v1 << "\n";

    std::cout << "\n--- Клас Matrix3 ---\n";
    Matrix3 m1(
        1.0, 2.0, 3.0,
        0.0, 1.0, 4.0,
        5.0, 6.0, 0.0
    );
    Matrix3 m_identity(1.0);

    std::cout << "Матриця M1:\n" << m1 << "\n";
    std::cout << "Одинична матриця I:\n" << m_identity << "\n";

    Matrix3 m_sum = m1 + m_identity;
    std::cout << "M1 + I:\n" << m_sum << "\n";

    Matrix3 m_mult = m1 * m_identity;
    std::cout << "M1 * I:\n" << m_mult << "\n";

    Vector3 v_mult_m = m1 * v1;
    std::cout << "M1 * v1 = " << v_mult_m << "\n";

    double determinant = m1.det();
    std::cout << "Determinant of M1 (det(M1)) = " << determinant << "\n";

    double norm_m1 = abs(m1);
    std::cout << "Frobenius Norm ||M1||_F = " << norm_m1 << "\n";


    return 0;
}