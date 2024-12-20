

# Bigint：Efficient way to handle common arithmetic operations on big integers.

By Zuoxiang Bu
Email: buz2@mcmaster.ca

- [**Project Introduction**](#project-introduction)
  - [**Goals**](#goals)
  - [**Repository Structure**](#repository-structure)
  - [**Compiling and Compatibility**](#compiling-and-compatibility)
  - [**Overview of Core Functions**](#overview-of-core-functions)

- [**Key Design Concept**](#key-design-concept)
  - [**Storage Structure**](#storage-structure)
  - [**Sign Representation**](#sign-representation)
  - [**Storage Examples**](#storage-examples)

- [**Class Description and Core Algorithm**](#class-description-and-core-algorithm)
  - [**Constructors**](#constructors)
  - [**Operator Overloading**](#operator-overloading)
    - [**Assignment Operators**](#assignment-operators)
    - [**Arithmetic Operators**](#arithmetic-operators)
    - [**Increment and Decrement Operators**](#increment-and-decrement-operators)
    - [**Output Operators**](#output-operators)
  - [**Public Methods**](#public-methods)

- [**License**](#license)

## Project Introduction
### Goals

In C++, built-in integer types such as `int64_t` are limited in their scope. `int64_t` is 64 bits, for the range of -9223372036854775808 to 9223372036854775807. However, this data range is insufficient in some situation. So this project aims to realize an efficient arbitrary-precision integer (bigint) class that can handle common arithmetic operations (addition, subtraction, multiplication, division, modulo, etc.) on big integers beyond the range of ordinary integers(eg. int64_t), making it easy for users to manipulate arbitrary precision integers as if they were using C++'s built-in int type.

### Compiling and Compatibility

This project bigint written in C++, and the development environment of the project is Windows 11 + Clang 18.1.8 + C++23, and the environment has been comprehensively tested. Make sure your compiler supports the C++23 standard.

### Overview of Core Functions
- Addition (+, +=): Adds two big integers, such as `bigint c = a + b`, the result is a + b.
- Subtraction (-, -=): Calculates a subtraction operation on two big integers, such as `bigint c = a-b`, and the result is a - b.
- Multiplication (*, *=): Calculates the product of two big integers, such as `bigint c = a * b` amd the result is a * b.
- Division (/, /=): Calculates the quotient of two big integers, such as `bigint c = a/b` and the result is a/b.
- Modulo (%, %=): Calculates the modulo of two big integers, such as `bigint c = a % b` and the result is a % b .
- Power operation (pow): Calculates the b power of a, such as bigint `c = pow(a, b)` and the result is a^b.
- Increment/decrement (++, --): Performs prefix/post increment and decrement operations, such as `++a`, which means `a` is increased by 1.
- Comparison operation (==, !=, >, <, >=, <=) : Compares the size relationships of big integers, such as `bool res = a > b` which compares whether `a` is greater than `b`.
- Stream operator (<<): Supports output operations for big integers, such as `std::cout << a`. Output big integer `a`.

---

## Key Design Concept

### Storage Structure
- Reverse Storage: vec is a private dynamic array (std::vector<uint8_t>), where each element represents a single decimal digit. Each digit of the big integer (0-9) is stored as a uint8_t in the std::vector. The digits are stored in reverse order.

### Sign Representation

In this project, it's important to handle the sign properly. So in this project uses the method of storing signs separately. Use the `is_Positive` bool variable to represent the sign of big integers, where `true` represents positive numbers and `false` represents negative numbers. For the special case of zero, it's always treated as a positive number and set to `true`. Also we can use the unary operator `-` to change sign, reversing the value of the `is_Positive`.

### Storage Examples

Eg. 1. Store the `bigint` object 12345678
Number: 12345678
Storage sequence (vec) : [8, 7, 6, 5, 4, 3, 2, 1]
`is_Positive` value: `true`

Eg. 2: Store the `bigint` object -987654321
Number: -987654321
Storage sequence (vec) : [1, 2, 3, 4, 5, 6, 7, 8, 9]
`is_Positive` value: `false`

Eg. 3: Store the `bigint` object 0
Number: 0
Storage sequence: [0]
`is_Positive` value: `true`

---
## Class Description and Core Algorithm
**Note: All of the following code blocks are simple examples only, and may need to be adjusted in practice. For example, the following preprocessing prerequisites are required, which will not be discussed separately in the following example code block.**
```cpp
#include <iostream>   
#include <sstream>    
#include "bigint.hpp" 
```

### Constructors

- **`bigint()`**：Default constructor that creates a `bigint` object with a value of `0`.。
  ```cpp
  bigint a;
  ```
  The above code creates a `bigint` object `a` with an initial value of 0, with the sign `is_Positive = true`.

- **`bigint(int64_t)`**：Construct `bigint` object from `int64_t` integers.
  ```cpp
  bigint b(1111111111);
  bigint c(-2222222222);
  ```
  With this constructor, `b` will be initialized to 1111111111 and `c` will be initialized to -2222222222.

- **`bigint(std::string)`**：Construct a `bigint` object from a string.
  ```cpp
  bigint d("111111111111111111111111");
  ```
  The above code initializes `d` to 111111111111111111111111.
  **Note** : If the string contains invalid characters (such as letter), a `std::invalid_argument` exception is thrown.
  
- **`bigint(const bigint &)`**：Copy constructor, copied from another bigint object.
  ```cpp
  bigint e(d);
  ```
  The above code copies the value of the bigint `d` and assigns it to `e`.

---

### Operator Overloading

#### Assignment Operators

- **`operator=(const bigint &)`**：Assigns the value of another `bigint` object to the current object.
  ```cpp
  bigint a;
  bigint b("121212");
  a = b;
  ```
  `a` will be assigned the value of `b` (121212).

- **`operator=(int64_t)`**：Assigns the value of a 64-bit integer to the current `bigint` object.
  ```cpp
  bigint a;
  a = 121212;
  ```
  `a` will be assigned the value 121212.

- **`operator=(std::string)`**：Assigns the value of the string to the current `bigint` object.
  ```cpp
  bigint a;
  a = "121212;
  ```
  `a` will be assigned the value 121212.
  
---

#### Arithmetic Operators

- **Addition Operator（ `operator+=(const bigint &)` and`operator(const bigint &, const bigint &)` ）**

  **Concepts and Principles:**
  The addition operators `operator+=` and `operator+` allow the addition of two big integers (of type bigint). The key idea of addition is similar to "column by column addition", which means adding the numbers of two big integers starting from the unit place and handling the carry-over accordingly. If the sum of numbers at a particular position is bigger than or equal to 10, the number of that unit is kept at that position and the carry is added to the next higher position. In addition, additions involving positive and negative numbers require special handling. If two numbers have different signs, then the operation becomes subtraction.
  The most challenging part of the implementation is dealing with carry. Here's a simple explanation: the row A and B are big integers, and temp is a carry indicator.
  ```
  // This is not code, it's just a convenient explanation.
     A2  A1  A0
    +    B1  B0
    -----------------
     C2  C1  C0
     Ci = Ai + Bi + temp
  ```

  `operator+=`

  This is a "addition assignment operator", i.e. `a += b` means adding b to a. Traverse each bit of `this->vec` and `rhs.vec`, adding the values of each bit using the logic of vertical addition. If the sum of the current bit is greater than 9, the `temp` carry is passed to the next bit. Finally, remove the leading zeros.
  `operator+`
  Reuse the `operator+=` to build. Creates a new temporary bigint, adds the two operands, and returns the result.
**Examples:**
  ```cpp
  bigint a("111111");
  bigint b("222222");
  a += b;  // This changes the value of a to 333333.
  ```

  ```cpp
  bigint a("99999");
  bigint b("1");
  bigint c = a + b; // Carry occurs: This changes the value of c to a + b = 99999 + 1 = 100000.
  ```

- **Subtraction Operator（ `operator-=(const bigint &)`and`operator-(const bigint &, const bigint &)` ）**
  **Concepts and Principles:**

  The subtraction operators `operator-` and `operator-=`  allow subtraction on two big integers (of type bigint). Its concept is similar to "vertical subtraction", starting from the unit digit bit by bit, if the subtract is less than the subtract, you need to borrow from the high. Subtract each of the two big integers from the lowest digit in turn. If the current digit is less than the subtrahend, borrow 1 from the higher digit and +10 from the current digit. If the left operand is less than the right operand, the sign of the result becomes negative.
  The most challenging part of the implementation is the handling of borrows, and the following is a simple expression: the row A and B are big integers, and temp is a borrow indicator.
  ```
  // This is not code, it's just a convenient explanation.
        A2   A1   A0  
      - B2   B1   B0  
    ------------------------
        C2   C1   C0  
    
  Ci = Ai - Bi - temp
  if Ci < 0:
      Ci = Ci + 10  // Borrow from higher digit
      temp = 1      // Indicate that a borrow occurred
  else:
      temp = 0      // No borrow occurred
  ```

  `operator-=`
  This is a "subtraction assignment operator", i.e. `a -= b` means subtracting `b` from `a`. Go through `this->vec` and `rhs.vec`, subtract the subtraction from the subtraction. If the subtrahend of a digit is less than the subtraction, borrow 1 from the higher digit and add 10 to the value of the current digit. In terms of signs, if a < b, swap a and b and set the symbol to negative. Finally,  remove the leading zeros to ensure that there are no leading zeros.

  `operator+`
  Reuse `operator-=` to build. Creates a new temporary bigint, subtracts the two operands, and returns the result.
  **Examples:**
  ```cpp
  bigint a("111111");
  bigint b("222222");
  a -= b; //This changes the value of a to a - b = 111111-222222 = -111111
  ```

  ```cpp
  bigint a("10000");
  bigint b("9999");
  bigint c = a - b; //Borrow occurs: This changes the value of c to a - b = 10000-9999 = 1
  ```

- **Multiplication Operator（ `operator*=(const bigint &)`and`operator*(const bigint &, const bigint &)` ）**
  **Concepts and Principles:**
  The operation of multiplication of big integers is similar to vertical multiplication, but because each digit of big integers is stored in the vec vector, and the unit digit is stored in index 0 and the ten bit is stored in index 1, it needs to be adjusted slightly. Multiply each digit of the operand X and Y, adding the product to the corresponding position in the result. Each digit of the product may be greater than 10, and the value of the higher digit needs to be carried to the higher digit. Z[i + j] += X[i] * Y[j], which means that the product of X[i] and Y[j] should be placed in Z[i + j] and Z[i + j + 1]. In terms of sign, if the two operands have the same sign, the result is positive, otherwise it is negative.
  The most challenging part of the implementation is the handling of carry, and the following is a simple expression: X and Y are big integers, temp is the mark of carry.
  ```
    // This is not code, it's just a convenient explanation.
    Z[i+j] += X[i] * Y[j]
    if Z[i+j] >= 10，then
      Z[i+j+1] += Z[i+j] / 10
      Z[i+j] = Z[i+j] % 10
  ```
  `operator*=`
  This is a "multiplication assignment operator", i.e. `a *= b` multiplies `a` by `b` and stores the result in a. Each digit in `this ->vec` is multiplied by each digit in the `rhs. Vec`, the product is stored in `res_vec[i + j]`. If the result is 10 or more, the carry is added to the next higher position. The sign of the result is based on the sign of a and b. Finally, remove leading zero and the result is updated in `*this`.
  ```cpp
  // Core parts are as follows
      for (size_t i = 0; i < vec.size(); ++i)
      {
          for (size_t j = 0; j < rhs.vec.size(); ++j)
          {
              res_vec[i + j] = static_cast<uint64_t>(res_vec[i + j] + vec[i] * rhs.vec[j]);
          }
      }

      // Handle carry and store the result in result.vec
      uint64_t temp = 0;
      for (size_t i = 0; i < res_vec.size(); ++i)
      {
          uint64_t current_val = res_vec[i] + temp;               // Add carry
          result.vec[i] = static_cast<uint8_t>(current_val % 10); // Store the least significant digit
          temp = current_val / 10;                                // Calculate the new carry
      }
  ```
  `operator*`
  Reuse `operator*=` to build. Creates a new temporary bigint, multiplies the two operands, and returns the result.
  **Examples:**
  ```cpp
  #include <iostream>
  #include "bigint.hpp"
  bigint a("11111");
  bigint b("-10000");
  a *= b; // This changes the a value to a * b = 11111 * -10000 = -111110000.
  ```

  ```cpp
  #include <iostream>
  #include "bigint.hpp"
  bigint a("11111");
  bigint b("10000");
  bigint c = a * b; // This changes the value of c to a * b = 111110000
  ```

- **Division Operator（ `operator/=(const bigint &)`and`operator/(const bigint &, const bigint &)` ）**
  **Concepts and Principles:**
  The operation of big integer division is similar to manual vertical long division. The basic idea is to determine the parts of the quotient by repeatedly trying to subtract different power multiples of 10 of the divisor from the dividend. When the subtraction is successful, the corresponding quotient contribution (10^cnt) is recorded, and when the subtraction fails, the divisor is retracted until all possible subtraction attempts are completed, then obtaining the final quotient C and remainder D, such that:
  Given the dividend A and the divisor B, our goal is to compute the quotient C and the remainder D, satisfying:
  A = B * C + D ( 0 ≤ D < B )
    
  `operator/=`
  This is a "division assignment operator", i.e. a /= b divide a by b and stores the result in a. Use a `divider` to indicate the current `divisor`, start with a doubling of the divisor and gradually multiply it by 10 (expand by a factor of 10) (use `pow()`). Each time the dividend `* this` is subtracted from the current divider, if `* this>=divider`', the division multiple of this part is recorded by `cnt`, indicating the multiple by which the dividend can be divisible by this divider. If `∗this < divider`, reset the `divider` and start with a smaller division unit. In terms of sign, if the dividend and the divisor have different signs, then the sign of the result is negative.  Finally, `trim()` is used to remove possible leading zeros in the quotient and dividend. The core code is as follows:
  ```cpp
  // Core parts are as follows
    bigint ret(0); // Store the result
    bigint divider(rhs);
    bigint positive_val(rhs);

    bigint cnt = 0; // Keeps track of the current power of 10
    while (*this > bigint::s_zero)
    {
        if (*this >= divider) 
        {
            *this -= divider;
            ret += pow(bigint::s_ten, cnt); 
            divider *= bigint::s_ten;       
            cnt++;
            // std:: cout << "ret:" << ret.is_Positive << std::endl;
        }
        else
        {
            divider = positive_val; // Reset divider
            cnt = 0;
            if (*this < divider)
            {
                break;
            }
        }
        divider.is_Positive = true; 
    }
    ret.trim();
    ret.is_Positive = sign_indicator; 
    *this = ret;
    return *this;
  ```
  `operator/`
  Use 'operator/=' to construct. Creates a new temporary `bigint` that divides the two operands and returns the result.
**Examples**
  ```cpp
  bigint a("100000");
  bigint b("500");
  a /= b;// This changes the value of a to a/b = 100000/500 = 200.
  ```

  ```cpp
  #include <iostream>
  #include "bigint.hpp"
  bigint a("11000");
  bigint b("1000");
  bigint c = a / b; //This changes the value of c to a/b = 11
  ```

- **Modulo operator（ `operator%=(const bigint &)` and `operator%(const bigint &, const bigint &)` ）**
  **Concepts and Principles:**
  The modulo operation is used to calculate the remainder of the dividend A divided by the divisor B. If you divide A by B and the result is a quotient C and a remainder D, then the formula can be expressed as:
  A=B⋅C+D
  So D=A−B⋅C
  In this project, the implementation is done with the help of division and multiplication! The remainder is obtained from the formula A%B=A−(B×(A/B)). In fact, it is equivalent to the reuse of division and multiplication!


  `operator%=`
  This is a "division assignment operator", i.e. `a /= b` divide a by b and stores the result in a. Firstly, calculates the division with `*this/rhs`, then multiply the quotient with the divisor `*rhs`, and finally subtract the product `-=` from the original object. In terms of sign, if the result is not zero and the original object is negative, the result is kept negative. The process focuses on the reuse of existing operators!
  The core code is as follows:
  ```cpp
  // Core parts are as follows
      *this -= (*this / rhs) * rhs;                      
      if (!this->is_Positive && *this != bigint::m_zero) 
      {
          this->is_Positive = false;
      }

      return *this;
  ```

  `operator%`
  Reuse `operator%=` to build. Creates a new temporary `bigint` that divides the two operands and returns the result.
**Examples**
  ```cpp
  bigint a("100001");
  bigint b("500");
  a %= b; // This changes the value of a to a %= b = 1 .

  ```

  ```cpp
  bigint a("10002");
  bigint b("100");
  bigint c = a % b;  // This changes the value of c to 'a % b = 22
  ```
---


#### **Increment and Decrement Operators**

**Note: The principle of increment and decrement is to reuse `operator+=` and `operator-=`**

- **`operator++()`**：Prefix Increment: Increases the current bigint by 1 and returns the increased value.
  ```cpp
  bigint a("123");
  ++a; 
  std::cout << a << std::endl; // Output: 124
  ```
- **`operator++(int)()`**：Postfix Increment: Increases the current bigint by 1, but returns the pre-increment value.
  ```cpp
  bigint a("123");
  bigint result = a++; 
  std::cout << "Result: " << result << std::endl; // Output: 123 
  std::cout << "New a: " << a << std::endl; // Output: 124 
  ```
- **`operator--()`**：Prefix Decrement: Reduces the current bigint by 1, returning the reduced value.
  ```cpp
  bigint a("123");
  --a;
  std::cout << a << std::endl; // Output: 122
  ```
- **`operator--(int) `**：Postfix Decrement: Reduces the current bigint by 1, but returns the pre-increment value.
  ```cpp
  bigint a("123");
  bigint result = a--; 
  std::cout << "Result: " << result << std::endl; // Output: 123
  std::cout << "New a: " << a << std::endl; // Output: 122 
  ```
---

#### **Comparison Operators**

**Note: Once `operator==(const bigint &, const bigint &)` and `operator>(const bigint &, const bigint &)` are built, other comparison operators can reuse these two!**

- **`operator>(const bigint &, const bigint &)`**：Compares whether the left operand is greater than the right operand. Return `true` or `false`.
The Concept: Firstly, check the sign of both numbers, the positive number is always greater than the negative number.
If the two `bigint` objects have the same sign: 
For positive case, the one with more digits is larger. If the number of digits is the same, compare each digit from the highest to the lowest. For negative numbers, the one with more digits is smaller. If the number of digits is the same, compare each digit from the highest to the lowest.

  ```cpp
  bigint a("11111");
  bigint b("1111");
  bigint c("22222");

  std::cout << (a > b) << std::endl; // output: 1 (true)
  std::cout << (a > c) << std::endl; // output: 0 (false)
  ```

- **`operator==(const bigint &, const bigint &)`**：Compare two `bigint` objects for equality. Return Return `true` or `false`.
The Concept: Firstly, check whether the positive and negative signs are consistent. If they are inconsistent, return false directly. Then check that the digits of two `bigint` objects are equal, and return false if they are not. Finally, compare each digit and return false if one is not equal.

  ```cpp
  bigint a("11111");
  bigint b("11111");
  bigint c("22");

  std::cout << (a == b) << std::endl; // output: 1 (true)
  std::cout << (a == c) << std::endl; // output: 0 (false)
  ```

- **`operator!=(const bigint &, const bigint &)`**：Compare two `bigint` objects for inequality. Use `!(lhs == rhs) ` to build this function.
  ```cpp
  bigint a("11111");
  bigint b("222");

  std::cout << (a != b) << std::endl; // output: 1 (true)
  std::cout << (a != a) << std::endl; // output: 0 (false)
  ```

- **`operator<(const bigint &, const bigint &)`**：Compares whether the left operand is less than the right operand. Return `true` or `false`. Reuse the `operator >` and `operator == ` to `! (lhs >= rhs)` for this function.
  ```cpp
  bigint a("1111");
  bigint b("1000");
  bigint c("2222");

  std::cout << (a < b) << std::endl; // output: 0 (false)
  std::cout << (a < c) << std::endl; // output: 1 (true)
  ```
- **`operator>=(const bigint &, const bigint &)`**：Compares whether the left operand is greater than or equal to the right operand. Return `true` or `false`. Reuse `operator >` and `operator ==` to build `lhs > rhs || lhs == rhs` for this function.
  ```cpp
  bigint a("111");
  bigint b("111");
  bigint c("222");

  std::cout << (a >= b) << std::endl; // output: 1 (true)
  std::cout << (a >= c) << std::endl; // output: 1 (true)
  ```

- **`operator<=(const bigint &, const bigint &)`**：Compares whether the left operand is less than or equal to the right operand. Return `true` or `false`. Reuse `operator >` to build `! (lhs > rhs)` for this function.

  ```cpp
  bigint a("111");
  bigint b("111");
  bigint c("222");

  std::cout << (a <= b) << std::endl; // output: 1 (true)
  std::cout << (c <= a) << std::endl; // output: 1 (true)
  ```

---

#### **Output Operators**

- **`operator<<(std::ostream &, const bigint &)`**：Use to output the contents of `bigint` to the output stream `std::cout`. The build concept is to output each digit stored in `vec` from high to low, and if the number is negative, then add a negative sign to the first.
  ```cpp
  bigint a("121212");
  std::cout << a << std::endl; // This will output '121212'
  ```

---

### **Public Methods**

- **get_value()**： Converts the vector `vec` of the `bigint` object to a `string`, and decides whether to add a negative sign at the beginning of the string based on `is_Positive`. Traverse `vec` reversely, converting each digit to a character and appending it to the string.

  ```cpp
  bigint a("111111");
  std::string value = a.get_value(); // "111111"
  ```

- **trim()**：Use to remove the leading zero of `bigint`. Traverse the vector `vec`, removing the last zeros in `vec` until there are only one digit left or until there are no more zeros.
  ```cpp
  bigint a("000111");
  a.trim();
  std::cout << a << std::endl; // Output: 111
  ```

- **pow(const bigint base, const bigint exponent)**：Calculate powers of `bigint`, serving /= function.
  ```cpp
  bigint a("2");
  bigint b("10");
  bigint c = pow(a, b); // 2^10 = 1024
  ```

---

## License
This project is licensed under the terms of the MIT license.

