#include <iostream>
#include <iomanip>
#include <cassert>
#include "Mat2x2.hpp"
using std::cout;
using std::cin;
using std::endl;

/*
Tests class Mat2x2 . Specifically, tests constructors, compound assignment
operator overloads, basic arithmetic operator overloads, unary +, unary -,
pre/post-increment/decrement, subscripts, function objects,
input/output operators, and relational operators.
@return 0 to indicate success.
*/

int main()
{
   const Mat2x2  ZERO;
   // must not compile, because zero is const
   //ZERO[1] = 0;
   //ZERO[2] = 0;
   //ZERO[3] = 0;
   //ZERO[4] = 0;
   const Mat2x2  IDENTITY(1, 0, 0, 1);

   // ctor that takes an std::initializer_list<double>
   Mat2x2 a = { 11, 22, 33, 44, 55, 66.5 }; // notice intentional too many initializers
   cout << "a = " << a << endl;
   assert(a == Mat2x2(11, 22, 33, 44));

   Mat2x2 b{ 111,222.7,333 };
   cout << "b = " << b << endl;
   assert(b == Mat2x2(111, 222.7, 333, 0));

   Mat2x2 c{ 1234 };
   cout << "c = " << c << endl;
   assert(c == Mat2x2(1234, 0, 0, 0));

   // a conversion constructor
   Mat2x2 d(1234);       // int -> Mat2x2 // [1234, 0, 0, 0]
   cout << "d = " << d << endl;
   assert(d == Mat2x2(1234, 0, 0, 0));

   Mat2x2  e;                           // default ctor
   cout << "e = " << e << endl;         // cout << Mat2x2 
   assert(e == ZERO);                   // Mat2x2  == Mat2x2 

   Mat2x2  f(2);                        // normal ctor with 1 arg
   cout << "f = " << f << endl;
   assert(f == Mat2x2(2, 0, 0, 0));

   Mat2x2  g(2, 3);                     // normal ctor with 2 args
   cout << "g = " << g << endl;
   assert(g == Mat2x2(2, 3, 0, 0));

   Mat2x2  h(2, 3, 8);                  // normal ctor with 3 args
   cout << "h = " << h << endl;
   assert(h == Mat2x2(2, 3, 8, 0));

   Mat2x2  m1(2.5, 3.6, 8.7, 5.8);                // normal ctor with 4 args
   Mat2x2   m1_inverse = m1.inverse();            // inverse, copy ctor

   Mat2x2  m1_inverse_times_m1 = m1_inverse * m1; // Mat2x2  * Mat2x2 
   assert(m1_inverse_times_m1 == IDENTITY);       // invariant, must hold     

   Mat2x2  m1_times_m1_inverse = m1 * m1_inverse;
   assert(m1_times_m1_inverse == IDENTITY);       // invariant, must hold

   assert(+m1 == -(-m1));                         // +Mat2x2 , -Mat2x2 
   Mat2x2  t1 = m1;
   ++m1;                                          // ++Mat2x2 
   assert(m1 == t1 + 1);
   --m1;                                          // --Mat2x2 
   assert(m1 == t1);

   Mat2x2  m1_post_inc = m1++;                    // Mat2x2 ++
   assert(m1_post_inc == t1);
   assert(m1 == t1 + 1);

   Mat2x2  m1_post_dec = m1--;                    // Mat2x2 --
   assert(m1_post_dec == t1 + 1);
   assert(m1 == t1);

   cout << "\n";
   h += Mat2x2(0, 0, 0, 5);               // Mat2x2  += Mat2x2 
   Mat2x2  m2 = h + 1.0;                  // Mat2x2  = Mat2x2 + int
   assert(m2 == Mat2x2(3, 4, 9, 6));
   cout << "m2 = " << m2 << endl;

   m2 = 1 + h;                            // Mat2x2  = double + Mat2x2;
   assert(m2 == Mat2x2(3, 4, 9, 6));

   Mat2x2  m3 = m2 - 1.0;                 // Mat2x2  = Mat2x2 - double
   assert(m3 == h);
   cout << "m3 = " << m3 << endl;

   Mat2x2  m4 = 1.0 - m3;                 // Mat2x2  = double - Mat2x2 
   cout << "m4 = " << m4 << endl;
   assert(m4 == Mat2x2(-1, -2, -7, -4));

   Mat2x2  m5 = m4 * 2.0;                 // Mat2x2  = Mat2x2 * double
   cout << "m5 = " << m5 << endl;
   assert(m5 == Mat2x2(-2, -4, -14, -8));

   Mat2x2  m6 = -1 * m5;                  // Mat2x2  = double * Mat2x2
   cout << "m6 = " << m6 << endl;
   assert(m6 == Mat2x2(2, 4, 14, 8));
   assert(m6 / -1.0 == m5);               // Mat2x2  = Mat2x2 / double
   assert(1 / m6 == 1 * m6.inverse());    // double / Mat2x2, inverse
   assert(-1.0 * m4 * 2.0 == m6);         // double * Mat2x2 * double 

   Mat2x2  m7 = m1++;                     //Mat2x2 ++
   cout << "m1 = " << m1 << endl;
   cout << "m7 = " << m7 << endl;
   assert(m7 == m1 - Mat2x2(1, 1, 1, 1)); // Mat2x2  - Mat2x2 

   Mat2x2  m8 = --m1;                     // --Mat2x2
   cout << "m1 = " << m1 << endl;
   cout << "m8 = " << m8 << endl;
   assert(m8 == m1);

   m8--;                                  // Mat2x2--
   cout << "m8 = " << m8 << endl;
   assert(m1 == 1 + m8);                  // double + Mat2x2 
   assert(m1 - 1 == m8);
   assert(-m1 + 1 == -m8);
   assert(2 * m1 == m8 + m1 + 1);
   assert(m1 * m1 == m1 * (1 + m8));

   Mat2x2  m9(123, 6, 6, 4567.89);
   cout << "m9 = " << m9 << endl;

   // subscripts (non-const)
   m9[0] = 3;
   m9[1] = 1;
   m9[2] = 7;
   m9[3] = 4;
   cout << "m9 = " << m9 << endl;
   assert(m9 == Mat2x2(3, 1, 7, 4));

   // relational operators
   double smallTol = Mat2x2::getTolerance() / 10.0;
   Mat2x2  m9Neighbor(3 - smallTol, 1 + smallTol, 7 - smallTol, 4 + smallTol);
   assert(m9 == m9Neighbor);

   double tol = Mat2x2::getTolerance();
   assert(m9 == m9);
   assert(m9 == (m9 + 0.1 * tol));
   assert(m9 == (m9 + 0.2 * tol));
   assert(m9 == (m9 + 0.3 * tol));
   assert(m9 == (m9 + 0.4 * tol));
   assert(m9 == (m9 + 0.5 * tol));
   assert(m9 != (m9 + 0.6 * tol));
   assert(m9 != (m9 + tol));

   assert(m9 < (m9 + 0.001));
   assert(m9 <= (m9 + 0.001));
   assert((m9 + 0.001) <= (m9 + 0.001));

   assert((m9 + 0.001) > m9);
   assert((m9 + 0.001) >= m9);
   assert((m9 + 0.001) >= (m9 + 0.001));

   // compound operators

   m9 += m9;
   cout << "m9 = " << m9 << endl;
   assert(m9 == 2 * Mat2x2(3, 1, 7, 4));

   Mat2x2  m10;
   m10 += (m9 / 2);
   cout << "m10 = " << m10 << endl;
   assert(m10 == Mat2x2(3, 1, 7, 4));

   m10 *= 2;
   cout << "m10 = " << m10 << endl;
   assert(m10 == m9);

   m10 /= 2;
   cout << "m10 = " << m10 << endl;
   assert(m10 == m9 / 2);

   m10 += 10;
   cout << "m10 = " << m10 << endl;
   assert(m10 == (m9 + 20) / 2);

   m10 -= 10;
   cout << "m10 = " << m10 << endl;
   assert(m10 == 0.5 * m9);

   // ctor that takes a std::array<double, 4>
   std::array<double, 4> arr = { 2, 0, 0, 2 };
   Mat2x2 m11{ arr };
   cout << "m11 = " << m11 << endl;

   // ctor that takes a std::array< std::array <double, 2>, 2>
   std::array <double, 2> row1{ 2, 0 };
   std::array <double, 2> row2{ 0, 2 };
   std::array< std::array <double, 2>, 2> mat{ row1, row2 };
   Mat2x2 m12{ mat };
   cout << "m12 = " << m12 << endl;
   assert(m12 == arr);

   // multiplications
   Mat2x2 i{ 1,2,3,4 };
   Mat2x2 j{ 2,0,1,2 };
   assert((i * j) == Mat2x2(4, 4, 10, 8));
   assert((j * i) == Mat2x2(2, 4, 7, 10));

   // inverse operation
   Mat2x2 k{ 4,7,2,6 };
   if (k) // this is how if(cin) works!
   {
      cout << "k is invertible\n";
      Mat2x2 m4aInv1 = k.inverse();
      Mat2x2 m4aInv2 = k ^ (-1); // operator ^ overload
      assert(m4aInv1 == m4aInv2);
   }
   else
   {
      cout << "k is NOT invertible\n";
   }

   Mat2x2 p{ k * k * k * k * k };
   Mat2x2 q{ k ^ (5) };
   assert(p == q);

   Mat2x2 x = Mat2x2{ 4,7,2,6 }.inverse();
   Mat2x2 y{ x * x * x * x * x };
   Mat2x2 z{ q ^ (-1) };
   assert(y == z);

   // test function objects (that is, function call operators)
   assert(k() == k.norm());

   cout << "k = " << k << endl;
   k(1, 1) = 10;
   k(1, 2) = 20;
   k(2, 1) = 30;
   k(2, 2) = 40;
   cout << "k = " << k << endl;

   try
   {
      k(3, 1) = 40;
   }
   catch (std::invalid_argument& ia)
   {
      cout << "Problem: " << ia.what() << endl;
   }

   try
   {
      k(1, 3) = 40;
   }
   catch (std::invalid_argument& ia)
   {
      cout << "Problem: " << ia.what() << endl;
   }

   //testing operator>>
   cout << "Please enter the numbers 1, 2, 3, 4.5, in that order\n\n";
   Mat2x2  input;
   cin >> input;
   cout << "input = " << input << endl;

   Mat2x2  diff = input - Mat2x2(1, 2, 3, 4.5);
   assert(diff.norm() <= tol);    // absolute value  
   assert(diff() <= tol);             // function object

   cout << "Test completed successfully!" << endl;

   return 0;
}
