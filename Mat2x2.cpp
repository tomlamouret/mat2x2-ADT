//
//  Mat2x2.cpp
//  COMP5421_A3
//
//  Created by Tom Lamouret on 2021-07-09.
//

#include "Mat2x2.hpp"
#include <iostream>
#include <iomanip>
#include <cmath>

// BIG FIVE
Mat2x2::Mat2x2(double a, double b, double c, double d): a{a}, b{b}, c{c}, d{d} {};
Mat2x2::Mat2x2(const array<double, 4> & y): a{y[0]}, b{y[1]}, c{y[2]}, d{y[3]} {}; // using std::array;
Mat2x2::Mat2x2(const array<array<double, 2>, 2>& x): a{x[0][0]}, b{x[0][1]}, c{x[1][0]}, d{x[1][1]} {}; // using std::array;
Mat2x2::Mat2x2(const initializer_list<double> l) { // using std::initializer_list;
    std::initializer_list<double>::iterator it = l.begin();
    if (l.size() > 0) a = *it++;
    else a = b = c = d = 0;
    if (l.size() > 1) b = *it++;
    else b = c = d = 0;
    if (l.size() > 2) c = *it++;
    else c = d = 0;
    if (l.size() > 3) d = *it++;
    else d = 0;
};

// SOME FUNCTIONS
double Mat2x2::norm() const {return sqrt(a*a+b*b+c*c+d*d);}; // returns the norm of the calling object
Mat2x2 Mat2x2::inverse() const {return (1/det()) * Mat2x2(d, -b, -c, a);}; // returns the inverse of the calling object
double Mat2x2::det() const {return a * d - b * c;}; // returns the determinant of the calling object

// MEMBER OPERATOR OVERLOADING
Mat2x2& Mat2x2::operator+=(const Mat2x2& rhs) { // addition assignment operator overloading
    a = a + rhs.a;
    b = b + rhs.b;
    c = c + rhs.c;
    d = d + rhs.d;
    return *this;
};
Mat2x2& Mat2x2::operator-=(const Mat2x2& rhs) { // substraction assignment operator overloading
    a = a - rhs.a;
    b = b - rhs.b;
    c = c - rhs.c;
    d = d - rhs.d;
    return *this;
};
Mat2x2& Mat2x2::operator*=(const Mat2x2& rhs) { // multiplication assignment operator overloading
    double new_a = a * rhs.a + b * rhs.c;
    double new_b = a * rhs.b + b * rhs.d;
    double new_c = rhs.a * c + rhs.c * d;
    double new_d = rhs.b * c + d * rhs.d;
    a = new_a;
    b = new_b;
    c = new_c;
    d = new_d;
    return *this;
};
Mat2x2& Mat2x2::operator/=(const Mat2x2& rhs) { // division assignment operator overloading
    *this *= rhs.inverse();
    return *this;
};
Mat2x2& Mat2x2::operator+=(const double& rhs) { // addition assignment operator overloading
    a = a + rhs;
    b = b + rhs;
    c = c + rhs;
    d = d + rhs;
    return *this;
};
Mat2x2& Mat2x2::operator-=(const double& rhs) { // substraction assignment operator overloading
    *this = -(rhs - *this);
    return *this;
};
Mat2x2& Mat2x2::operator*=(const double& rhs) { // multiplication assignment operator overloading
    a = a * rhs;
    b = b * rhs;
    c = c * rhs;
    d = d * rhs;
    return *this;
};
Mat2x2& Mat2x2::operator/=(const double& rhs) { // division assignment operator overload
    if (rhs == 0)
        throw std::runtime_error("Math error: Attempted to divide by Zero\n");
    a = a * (1.0 / rhs);
    b = b * (1.0 / rhs);
    c = c * (1.0 / rhs);
    d = d * (1.0 / rhs);
    return *this;
};
Mat2x2& Mat2x2::operator++() { // prefix increment operator overloading
    *this += 1.0;
    return *this;
};
const Mat2x2 Mat2x2::operator++(int) { // postfix increment operator overloading
    Mat2x2 temp {*this};
    ++(*this);
    return temp;
};
Mat2x2& Mat2x2::operator--() { // prefix decrement operator overloading
    *this -= 1.0;
    return *this;
};
const Mat2x2 Mat2x2::operator--(int) { // postfix decrement operator overloading
    Mat2x2 temp {*this};
    --(*this);
    return temp;
};
Mat2x2 Mat2x2::operator+() { // unary plus operator overloading
    return Mat2x2{abs(a), abs(b), abs(c), abs(d)};
};
Mat2x2 Mat2x2::operator-() { // unary minus operator overloading
    Mat2x2 temp{*this};
    temp *= -1.0;
    return temp;
};

Mat2x2 Mat2x2::operator^(int k) { // XOR operator overloading; returns the Mat2x2 object resulting from raising it to the power k
    Mat2x2 temp;
    if (k < 0) temp = inverse();
    else temp = *this;
    for (int i = 1; i < abs(k); ++i)
        if (k < 0) temp *= inverse();
        else temp *= *this;
    return temp;
};
const double& Mat2x2::operator[](size_t index) const { // returns an element of the matrix found at a specific index
    if (index == 0) return a;
    else if (index == 1) return b;
    else if (index == 2) return c;
    else if (index == 3) return d;
    else throw std::invalid_argument("index out of bounds");
};
double& Mat2x2::operator[](size_t index) { // returns an element of the matrix found at a specific index
    if (index == 0) return a;
    else if (index == 1) return b;
    else if (index == 2) return c;
    else if (index == 3) return d;
    else throw std::invalid_argument("index out of bounds");
};

Mat2x2::operator bool() const { // returns whether or not the invoking object has inverse
    if (abs(det()) > tolerance) return true;
    else return false;
};

// FUNCTION OBJECTS
double Mat2x2::operator()() const {return norm();} // returns the norm of the invoking Mat2x2 object
double& Mat2x2::operator()(size_t r, size_t c) {  // returns an lvalue reference to the entry at row r and column c
    if (r < 1 || r > 2) throw std::invalid_argument("row index out of bounds");
    if (c < 1 || c > 2) throw std::invalid_argument("column index out of bounds");
    if (r == 1)
        if (c == 1) return a;
        else return b;
    else
        if (c == 1) return this->c;
        else return d;
};

// STATIC MEMBERS
double Mat2x2::tolerance = 0.000001;
void Mat2x2::setTolerance(double tol) {tolerance = tol;};
double Mat2x2::getTolerance() {return tolerance;};

// NON-MEMBER OPERATOR OVERLOADING
ostream& operator<<(ostream& sout, const Mat2x2& m) { // insertion operator overloading
    sout << std::fixed << std::setprecision(2) << "[" << m[0] << ", " << m[1] << ", " << m[2] << ", " << m[3] << "]";
    return sout;
};
istream& operator>>(istream& sin, Mat2x2& m) { // extraction operator overloading
    double a, b, c, d;
    if (sin >> a >> b >> c >> d) {
        m[0] = a;
        m[1] = b;
        m[2] = c;
        m[3] = d;
    }
    return sin;
};

Mat2x2 operator+(const Mat2x2& lhs, const Mat2x2& rhs) { // addition operator overloading
    Mat2x2 temp {lhs};
    temp += rhs;
    return temp;
};
Mat2x2 operator-(const Mat2x2& lhs, const Mat2x2& rhs) { // substraction operator overloading
    Mat2x2 temp {lhs};
    temp -= rhs;
    return temp;
};
Mat2x2 operator*(const Mat2x2& lhs, const Mat2x2& rhs) { // multiplication operator overloading
    Mat2x2 temp {lhs};
    temp *= rhs;
    return temp;
};
Mat2x2 operator/(const Mat2x2& lhs, const Mat2x2& rhs) { // division operator overloading
    Mat2x2 temp {lhs};
    temp /= rhs;
    return temp;
};

Mat2x2 operator+(const Mat2x2& lhs, const double& rhs) { // addition operator overloading
    Mat2x2 temp {lhs};
    temp += rhs;
    return temp;
};
Mat2x2 operator-(const Mat2x2& lhs, const double& rhs) { // substraction operator overloading
    Mat2x2 temp {lhs};
    temp -= rhs;
    return temp;
};
Mat2x2 operator*(const Mat2x2& lhs, const double& rhs) { // multiplication operator overloading
    Mat2x2 temp {lhs};
    temp *= rhs;
    return temp;
};
Mat2x2 operator/(const Mat2x2& lhs, const double& rhs) { // division operator overloading
    Mat2x2 temp {lhs};
    temp /= rhs;
    return temp;
};

Mat2x2 operator+(const double& lhs, const Mat2x2& rhs) { // addition operator overloading
    Mat2x2 temp {rhs};
    temp += lhs;
    return temp;
};
Mat2x2 operator-(const double& lhs, const Mat2x2& rhs) { // substraction operator overloading
    Mat2x2 temp {lhs-rhs[0], lhs-rhs[1], lhs-rhs[2], lhs-rhs[3]};
    return temp;
};
Mat2x2 operator*(const double& lhs, const Mat2x2& rhs) { // multiplication operator overloading
    Mat2x2 temp {rhs};
    temp *= lhs;
    return temp;
};
Mat2x2 operator/(const double& lhs, const Mat2x2& rhs) { // division operator overloading
    Mat2x2 temp {rhs.inverse()};
    temp *= lhs;
    return temp;
};

bool operator<(const Mat2x2& lhs, const Mat2x2& rhs) { // less than operator overloading
    if (operator!=(lhs, rhs) && lhs.norm() < rhs.norm()) return 1;
    else return 0;
};
bool operator<=(const Mat2x2& lhs, const Mat2x2& rhs) { // less than or equal to operator overloading
    return operator<(lhs, rhs) || operator==(lhs, rhs);
};
bool operator>(const Mat2x2& lhs, const Mat2x2& rhs) { // greater than operator overloading
    if (operator!=(lhs, rhs) && lhs.norm() > rhs.norm()) return 1;
    else return 0;
};
bool operator>=(const Mat2x2& lhs, const Mat2x2& rhs) { // greater than or equal operator overloading
    return operator>(lhs, rhs) || operator==(lhs, rhs);
};
bool operator==(const Mat2x2& lhs, const Mat2x2& rhs) { // equal to operator overloading
    Mat2x2 temp = lhs - rhs;
    if (temp.norm() <= Mat2x2::getTolerance()) return 1;
    else return 0;
};
bool operator!=(const Mat2x2& lhs, const Mat2x2& rhs) { // not equal to operator overloading
    return !operator==(lhs, rhs);
};
