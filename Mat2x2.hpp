//
//  Mat2x2.hpp
//  COMP5421_A3
//
//  Created by Tom Lamouret on 2021-07-09.
//

#ifndef Mat2x2_hpp
#define Mat2x2_hpp

#include <stdio.h>
#include <array>

using std::array;
using std::initializer_list;
using std::ostream;
using std::istream;

class Mat2x2 {
private:
    double a; // top-left
    double b; // top-right
    double c; // bottom-left
    double d; // bottom-right
public:
    // BIG FIVE
    explicit Mat2x2(double = 0, double = 0, double = 0, double = 0);
    Mat2x2(const array<double, 4> &);          // using std::array;
    Mat2x2(const array<array<double, 2>, 2>&); // using std::array;
    Mat2x2(const initializer_list<double>);    // using std::initializer_list;
    Mat2x2(const Mat2x2&) = default; // default copy constructor
    Mat2x2(Mat2x2&&) = default; // default move constructor
    Mat2x2& operator=(const Mat2x2&) = default; // default copy assignment operator
    Mat2x2& operator=(Mat2x2&&) = default; // default move assignment operator
    ~Mat2x2() = default; // default destructor
    
    // SOME FUNCTIONS
    double norm() const; // returns the norm of the calling object
    Mat2x2 inverse() const; // returns the inverse of the calling object
    double det() const; // returns the determinant of the calling object
    
    // MEMBER OPERATOR OVERLOADING
    Mat2x2& operator+=(const Mat2x2&); // addition assignment operator overloading
    Mat2x2& operator-=(const Mat2x2&); // substraction assignment operator overloading
    Mat2x2& operator*=(const Mat2x2&); // multiplication assignment operator overloading
    Mat2x2& operator/=(const Mat2x2&); // division assignment operator overloading
    
    Mat2x2& operator+=(const double&); // addition assignment operator overloading
    Mat2x2& operator-=(const double&); // substraction assignment operator overloading
    Mat2x2& operator*=(const double&); // multiplication assignment operator overloading
    Mat2x2& operator/=(const double&); // division assignment operator overload
    
    Mat2x2& operator++(); // prefix increment operator overloading
    const Mat2x2 operator++(int); // postfix increment operator overloading
    Mat2x2& operator--(); // prefix decrement operator overloading
    const Mat2x2 operator--(int); // postfix decrement operator overloading
    Mat2x2 operator+(); // unary plus operator overloading
    Mat2x2 operator-(); // unary minus operator overloading
    
    Mat2x2 operator^(int k); // XOR operator overloading; returns the Mat2x2 object resulting from raising it to the power k
    
    const double& operator[](size_t) const; // returns an element of the matrix found at a specific index
    double& operator[](size_t); // returns an element of the matrix found at a specific index
    
    explicit operator bool() const; // returns whether or not the invoking object has inverse
    
    // FUNCTION OBJECTS
    double operator()() const; // returns the norm of the invoking Mat2x2 object
    double& operator()(size_t r, size_t c); // returns an lvalue reference to the entry at row r and column c
    
    // STATIC MEMBERS
    static double tolerance; // initial value = 1.0E-6
    static void setTolerance(double tol);
    static double getTolerance();
};

// NON-MEMBER OPERATOR OVERLOADING
ostream& operator<<(ostream&, const Mat2x2&); // insertion operator overloading
istream& operator>>(istream&, Mat2x2&); // extraction operator overloading

Mat2x2 operator+(const Mat2x2&, const Mat2x2&); // addition operator overloading
Mat2x2 operator-(const Mat2x2&, const Mat2x2&); // substraction operator overloading
Mat2x2 operator*(const Mat2x2&, const Mat2x2&); // multiplication operator overloading
Mat2x2 operator/(const Mat2x2&, const Mat2x2&); // division operator overloading

Mat2x2 operator+(const Mat2x2&, const double&); // addition operator overloading
Mat2x2 operator-(const Mat2x2&, const double&); // substraction operator overloading
Mat2x2 operator*(const Mat2x2&, const double&); // multiplication operator overloading
Mat2x2 operator/(const Mat2x2&, const double&); // division operator overloading

Mat2x2 operator+(const double&, const Mat2x2&); // addition operator overloading
Mat2x2 operator-(const double&, const Mat2x2&); // substraction operator overloading
Mat2x2 operator*(const double&, const Mat2x2&); // multiplication operator overloading
Mat2x2 operator/(const double&, const Mat2x2&); // division operator overloading

bool operator<(const Mat2x2&, const Mat2x2&); // less than operator overloading
bool operator<=(const Mat2x2&, const Mat2x2&); // less than or equal to operator overloading
bool operator>(const Mat2x2&, const Mat2x2&); // greater than operator overloading
bool operator>=(const Mat2x2&, const Mat2x2&); // greater than or equal operator overloading
bool operator==(const Mat2x2&, const Mat2x2&); // equal to operator overloading
bool operator!=(const Mat2x2&, const Mat2x2&); // not equal to operator overloading

#endif /* Mat2x2_hpp */
