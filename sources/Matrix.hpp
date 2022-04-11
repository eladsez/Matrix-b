#include <iostream>
#include <vector>


namespace zich {
    class Matrix {
    private:
        int row, column;// row. column
        std::vector<double> mat;

        int count_all() const;
        int count_char(std::string str, char to_count);

    public:
        Matrix(std::vector<double> values, int r, int c);

        Matrix operator+(const Matrix &other) const;

        Matrix operator-(const Matrix &other) const;

        Matrix operator*(const Matrix &other) const;

        Matrix operator*(double num) const;

        Matrix operator-();

        Matrix operator+();

        Matrix &operator++(); // prefix adding

        Matrix operator++(int); // postfix adding

        Matrix &operator--(); // prefix sub

        Matrix operator--(int); // postfix sub

        Matrix &operator+=(const Matrix &other);

        Matrix &operator-=(const Matrix &other);

        Matrix &operator*=(const Matrix &other);

        Matrix &operator*=(double num);

        bool operator==(const Matrix &other) const;

        bool operator!=(const Matrix &other) const;

        bool operator>=(const Matrix &other) const;

        bool operator<=(const Matrix &other) const;

        bool operator<(const Matrix &other) const;

        bool operator>(const Matrix &other) const;

        friend Matrix operator*(int num, Matrix mat);

        friend std::istream &operator>>(std::istream &in, Matrix &mat);

        friend std::ostream &operator<<(std::ostream &out, const Matrix &mat);
    };

}
