#include <iostream>
#include "Matrix.hpp"
#include <vector>
#include <string>

namespace zich {

    Matrix::Matrix(std::vector<double> values, int row, int column) {
        if (column < 1 || row < 1 || values.size() != row * column) {
            throw std::invalid_argument("matrix size must be grater then 0");
        }
        this->row = row;
        this->column = column;
        this->mat.resize((size_t)row * (size_t)column);
        for (size_t i = 0; i < row * column; ++i) {
            this->mat[i] = values[i];
        }
    }

    Matrix Matrix::operator+(const Matrix &other) const {
        if (other.column != column || other.row != row) {
            throw std::invalid_argument("invalid matrix size for operator +");
        }
        std::vector<double> plusVal((size_t)(row * column));
        for (size_t i = 0; i < row * column; ++i) {
            plusVal[i] = mat[i] + other.mat[i];
        }
        return Matrix(plusVal, row, column);
    }

    Matrix Matrix::operator-(const Matrix &other) const {
        if (other.column != column || other.row != row) {
            throw std::invalid_argument("invalid matrix size for operator -");
        }
        std::vector<double> subVal((size_t)(row * column));
        for (size_t i = 0; i < row * column; ++i) {
            subVal[i] = mat[i] - other.mat[i];
        }
        return Matrix(subVal, row, column);
    }

    Matrix Matrix::operator*(const Matrix &other) const {
        if (column != other.row) {
            throw std::invalid_argument("invalid matrix size for operator *");
        }
        std::vector<double> mulV((size_t)(row * other.column));

        for (size_t i = 0; i < row; ++i) {
            for (size_t j = 0; j < other.column; ++j) {
                mulV[i * (size_t) other.column + j] = 0;
                for (size_t k = 0; k < other.row; ++k) {
                    mulV[i * (size_t) other.column + j] +=
                            mat[i * (size_t) column + k] * other.mat[k * (size_t) other.column + j];
                }
            }
        }
        return Matrix(mulV, row, other.column);
    }

    Matrix Matrix::operator*(double num) const {
        std::vector<double> mulVal((size_t)(row * column));
        for (size_t i = 0; i < row * column; ++i) {
            mulVal[i] = mat[i] * num;
        }
        return Matrix(mulVal, row, column);
    }

    Matrix Matrix::operator-() {
        std::vector<double> Val((size_t)(row * column));
        for (size_t i = 0; i < row * column; ++i) {
            if (mat[i] == 0) {
                continue;
            }
            Val[i] = mat[i] * -1;
        }
        return Matrix(Val, row, column);
    }

    Matrix Matrix::operator+() { return *this; }

    Matrix &Matrix::operator++() {
        for (size_t i = 0; i < row * column; ++i) {
            mat[i] += 1;
        }
        return *this;
    }

    Matrix Matrix::operator++(int) {
        Matrix copy(mat, row, column); // deep copy
        for (size_t i = 0; i < row * column; ++i) {
            mat[i] += 1;
        }
        return copy;
    }

    Matrix &Matrix::operator--() {
        for (size_t i = 0; i < row * column; ++i) {
            mat[i] -= 1;
        }
        return *this;
    }

    Matrix Matrix::operator--(int) {
        Matrix copy(mat, row, column); // deep copy
        for (size_t i = 0; i < row * column; ++i) {
            mat[i] -= 1;
        }
        return copy;
    }

    Matrix &Matrix::operator+=(const Matrix &other) {
        if (other.column != column || other.row != row) {
            throw std::invalid_argument("invalid matrix size for operator +=");
        }
        for (size_t i = 0; i < row * column; ++i) {
            mat[i] += other.mat[i];
        }
        return *this;
    }

    Matrix &Matrix::operator-=(const Matrix &other) {
        if (other.column != column || other.row != row) {
            throw std::invalid_argument("invalid matrix size for operator -=");
        }
        for (size_t i = 0; i < row * column; ++i) {
            mat[i] -= other.mat[i];
        }
        return *this;
    }

    Matrix &Matrix::operator*=(const Matrix &other) {
        if (column != other.row) {
            throw std::invalid_argument("invalid matrix size for operator *=");
        }
        *this = *this * other;
        return *this;
    }

    Matrix &Matrix::operator*=(double num) {
        for (size_t i = 0; i < row * column; ++i) {
            if (mat[i] == 0) {
                continue;
            }
            mat[i] *= num;
        }
        return *this;
    }

    bool Matrix::operator==(const Matrix &other) const {
        if (other.column != column || other.row != row) {
            throw std::invalid_argument("invalid matrix size for operator ==");
        }
        for (size_t i = 0; i < row * column; ++i) {
            if (mat[i] != other.mat[i]) {
                return false;
            }
        }
        return true;
    }

    int Matrix::count_all() const {
        int count = 0;
        for (size_t i = 0; i < row * column; ++i) {
            count += mat[i];
        }
        return count;
    }

    bool Matrix::operator!=(const Matrix &other) const {
        if (other.column != column || other.row != row) {
            throw std::invalid_argument("invalid matrix size for operator ==");
        }
        for (size_t i = 0; i < row * column; ++i) {
            if (mat[i] != other.mat[i]) {
                return true;
            }
        }
        return false;
    }

    bool Matrix::operator>=(const Matrix &other) const {
        if (other.column != column || other.row != row) {
            throw std::invalid_argument("invalid matrix size for operator >=");
        }
        return other.count_all() <= this->count_all();
    }

    bool Matrix::operator<=(const Matrix &other) const {
        if (other.column != column || other.row != row) {
            throw std::invalid_argument("invalid matrix size for operator <=");
        }
        return other.count_all() >= this->count_all();
    }

    bool Matrix::operator<(const Matrix &other) const {
        if (other.column != column || other.row != row) {
            throw std::invalid_argument("invalid matrix size for operator <");
        }
        return other.count_all() > this->count_all();
    }

    bool Matrix::operator>(const Matrix &other) const {
        if (other.column != column || other.row != row) {
            throw std::invalid_argument("invalid matrix size for operator >");
        }
        return other.count_all() < this->count_all();
    }

    Matrix operator*(int num, Matrix mat) {
        std::vector<double> mulVal((size_t)(mat.row * mat.column));
        for (size_t i = 0; i < mat.row * mat.column; ++i) {
            mulVal[i] = mat.mat[i] * num;
        }
        return Matrix(mulVal, mat.row, mat.column);
    }

    int count_char(std::string str, char to_count) {
        int count = 0;

        for (size_t i = 0; i < str.size(); i++) {
            if (str[i] == to_count) {
                ++count;
            }
        }

        return count;
    }

    void valid_input(std::string mat_str) {
        bool seen = false;
        for (size_t i = 0; i < mat_str.length(); ++i) {
            if ((mat_str[i] == ']' && !seen) || (mat_str[i] == '[' && seen)) {
                throw std::invalid_argument("invalid input ] or [ for operator >>");
            }
            if (mat_str[i] == ']' && seen) {
                seen = false;
            }
            if (mat_str[i] == '[') {
                seen = true;
            }
            if ((mat_str[i] == ',' && mat_str[i - 1] != ']') ||
                (mat_str[i] == ',' && mat_str[i + 1] != ' ')) {
                throw std::invalid_argument("invalid input , for operator >>");
            }
        }
    }

    std::istream &operator>>(std::istream &in, Matrix &mat) {
        std::string mat_str;
        std::getline(in, mat_str);
        valid_input(mat_str);
        int row = count_char(mat_str, ',') + 1;
        std::vector<double> mat_v;
        for (size_t i = 0, j = 0; i < mat_str.length(); j = ++i) {
            while (isdigit(mat_str[i]) != 0) {
                ++i;
            }
            if (i != j) {
                mat_v.push_back(std::stod(mat_str.substr(j, i - j)));
            }
        }
        mat = Matrix(mat_v, row, int(mat_v.size()) / row);
        return in;
    }

    std::ostream &operator<<(std::ostream &out, const Matrix &mat) {
        for (size_t i = 0; i < mat.row; ++i) {
            out << "[";
            for (size_t j = 0; j < mat.column; ++j) {
                out << mat.mat[(size_t) mat.column * i + j];
                if (j != mat.column - 1) {
                    out << " ";
                }
            }
            out << "]";
            if (i != mat.row - 1) {
                out << "\n";
            }
        }
        return out;
    }
}
