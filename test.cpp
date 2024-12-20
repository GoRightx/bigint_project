/**
 * @file test.cpp
 * @author Zuoxiang Bu(Student NO.:400553917) (buz2@mcmaster.ca)
 * @date 2024-12-20
 * @brief This is a bigint class test file that comprehensively tests the functions of bigint class.
 *
 * This file contains Unit tests, Integration tests, Edge cases tests, Error handling tests, Consistency tests,
 * Random tests, Stress tests, and record failures and successes.
 */

#include <iostream>   //Provides standard input/output stream (cin, cout etc.)
#include <sstream>    // Provides stringstream for converting strings and other data types
#include "bigint.hpp" // The bigint class is defined in this header file.
#include <random>     // Provide random number generation
#include <fstream>    // Provide file stream for input and output operations

/**
 * @brief Counters for tracking test results. This section maintains counters for different kinds of tests
 */

// Unit Tests Counter
int pass_unit = 0; // pass
int fail_unit = 0; // fail

// Integration Tests Counter
int pass_integration = 0; // pass
int fail_integration = 0; // fail

// Edge Cases Tests Counter
int pass_edge = 0; // pass
int fail_edge = 0; // fail

// Error Tests Counter
int pass_error = 0; // pass
int fail_error = 0; // fail

// Consistency Tests Counter
int pass_consistency = 0; // pass
int fail_consistency = 0; // fail

// Super Big Bigint Stress Tests Counter
int pass_stress = 0; // pass
int fail_stress = 0; // fail

// Comparison Tests Counter
int pass_comparison = 0;
int fail_comparison = 0;

/**
 * @brief Check function for comparing actual result and expected result of bigint.
 *
 * @param name Name of the test.
 * @param result Actual result(bigint).
 * @param goal Theoretical correct result(bigint).
 */
void check(const std::string &name, const bigint &result, const bigint &goal)
{
    if (result.get_value() == goal.get_value())
    {
        std::cout << "Pass: " << name << " The result: " << result.get_value() << " and expectation: " << goal.get_value() << " is the same" << '\n';
        ++pass_unit;
    }
    else
    {
        std::cout << "Fail: " << name << " The result: " << result.get_value() << " and expectation: " << goal.get_value() << " is DIFFERENT" << '\n';
        ++fail_unit;
    }
}

/**
 * @brief Check function for comparing actual bigint and expected string values.
 *
 * @param name Name of the test.
 * @param result Actual result (bigint).
 * @param goal Theoretical correct result (string).
 */
void check(const std::string &name, const bigint &result, const std::string &goal)
{
    if (result.get_value() == goal)
    {
        std::cout << "Pass: " << name << ". The result: " << result.get_value() << " and expectation: " << goal << " is the same" << '\n';
        ++pass_unit;
    }
    else
    {
        std::cout << "Fail: " << name << ". The result: " << result.get_value() << " and expectation: " << goal << " is DIFFERENT" << '\n';
        ++fail_unit;
    }
}

/**
 * @brief Check function for comparing actual bool and expected bool values.
 *
 * @param name Name of the test.
 * @param result Actual result (bool).
 * @param goal Theoretical correct result (bool).
 */
void check(const std::string &name, bool result, bool goal)
{
    if (result == goal)
    {
        std::cout << "Pass: " << name << " The result: " << std::boolalpha << result << " and expectation: " << goal << " is the same" << '\n';
        ++pass_unit;
    }
    else
    {
        std::cout << "Fail: " << name << " The result: " << std::boolalpha << result << " and expectation: " << goal << " is DIFFERENT" << '\n';
        ++fail_unit;
    }
}

/**
 * @brief Check whether the test passes. And this is used when actual and expected are of type string.
 *
 * @param name Name of the test.
 * @param result Actual result(string).
 * @param goal Theoretical correct result(string).
 */
void check_cout(const std::string &name, const std::string &result, const std::string &goal)
{
    if (result == goal)
    {
        std::cout << "Pass: " << name << "The result: " << result << "and expectation: " << goal << "is the same" << '\n';
        ++pass_unit;
    }
    else
    {
        std::cout << "Fail: " << name << "The result:  " << result << "and expectation: " << goal << "is DIFFERENT" << '\n';
        ++fail_unit;
    }
}

/**
 * @brief Tests the output of the << operator for bigint.
 *
 * @param name Name of the test.
 * @param result Input bigint for test (bigint).
 * @param goal Theoretical correct result (string).
 */
void check_output(const std::string &name, const bigint &result, const std::string &goal)
{
    std::ostringstream oss;
    oss << result;                     // Capture the output of the << operator
    check_cout(name, oss.str(), goal); // Use the existing string check function
}

/**
 * @brief Check function for comparing actual bigint and expected string values in an integration test.
 *
 * @param name Name of the test.
 * @param result Actual result (bigint).
 * @param goal Theoretical correct result (string).
 */
void check_integration(const std::string &name, const bigint &result, const std::string &goal)
{
    if (result.get_value() == goal)
    {
        std::cout << "Pass: " << name << ". The result: " << result.get_value() << " and expectation: " << goal << " is the same" << '\n';
        ++pass_integration;
    }
    else
    {
        std::cout << "Fail: " << name << ". The result: " << result.get_value() << " and expectation: " << goal << " is DIFFERENT" << '\n';
        ++fail_integration;
    }
}

/**
 * @brief Check function for comparing actual bigint and expected string values in an edge test.
 *
 * @param name Name of the test.
 * @param result Actual result (bigint).
 * @param goal Theoretical correct result (string).
 */
void check_edge(const std::string &name, const bigint &result, const std::string &goal)
{
    if (result.get_value() == goal)
    {
        std::cout << "Pass: " << name << ". The result: " << result.get_value() << " and expectation: " << goal << " is the same" << '\n';
        ++pass_edge;
    }
    else
    {
        std::cout << "Fail: " << name << ". The result: " << result.get_value() << " and expectation: " << goal << " is DIFFERENT" << '\n';
        ++fail_edge;
    }
}

/**
 * @brief Check function for comparing actual bigint and expected string values in an error test.
 *
 * @param name Name of the test.
 * @param result Actual result (bigint).
 * @param goal Theoretical correct result (string).
 */
void check_error(const std::string &name, const bigint &result, const std::string &goal)
{
    if (result.get_value() == goal)
    {
        std::cout << "Pass: " << name << ". The result: " << result.get_value() << " and expectation: " << goal << " is the same" << '\n';
        ++pass_error;
    }
    else
    {
        std::cout << "Fail: " << name << ". The result: " << result.get_value() << " and expectation: " << goal << " is DIFFERENT" << '\n';
        ++fail_error;
    }
}

/**
 * @brief Check function for comparing actual bigint and expected bigint values in a consistency test.
 *
 * @param name Name of the test.
 * @param result Actual result (bigint).
 * @param goal Theoretical correct result (bigint).
 */
void check_consistency(const std::string &name, const bigint &result, const bigint &goal)
{
    if (result.get_value() == goal.get_value())
    {
        std::cout << "Pass: " << name << ". The result: " << result.get_value() << " and expectation: " << goal.get_value() << " is the same" << '\n';
        ++pass_consistency;
    }
    else
    {
        std::cout << "Fail: " << name << ". The result: " << result.get_value() << " and expectation: " << goal.get_value() << " is DIFFERENT" << '\n';
        ++fail_consistency;
    }
}

/**
 * @brief Check function for comparing actual bigint and expected bigint values in stress test.
 *
 * @param name Name of the test.
 * @param result Actual result (bigint).
 * @param goal Theoretical correct result (bigint).
 */
void check_stress(const std::string &name, const bigint &result, const bigint &goal)
{
    if (result.get_value() == goal.get_value())
    {
        std::cout << "Pass: " << name << ". The result: " << result.get_value() << " and expectation: " << goal.get_value() << " is the same" << '\n';
        ++pass_stress;
    }
    else
    {
        std::cout << "Fail: " << name << ". The result: " << result.get_value() << " and expectation: " << goal.get_value() << " is DIFFERENT" << '\n';
        ++fail_stress;
    }
}

/**
 * @brief Check function to compare the actual bigint and expected bigint in comparison tests.
 *
 * @param name Name of the test.
 * @param result Actual result (bigint).
 * @param goal Theoretical correct result (bigint).
 */
void check_comparison(const std::string &name, const bigint &result, const bigint &goal)
{
    if (result.get_value() == goal.get_value())
    {
        std::cout << "Pass: " << name << " The result: " << result.get_value() << " and expectation: " << goal.get_value() << " is the same" << '\n';
        ++pass_comparison;
    }
    else
    {
        std::cout << "Fail: " << name << " The result: " << result.get_value() << " and expectation: " << goal.get_value() << " is DIFFERENT" << '\n';
        ++fail_comparison;
    }
}

// ==================================
//        Unit test
// ==================================

/**
 * @brief Test the default constructor of the bigint class
 *
 * This function tests whether the default constructor correctly initializes a bigint object to "0".
 */
void Default_Constructor()
{
    std::cout << "Default Constructor Test:\n";
    check("Default Constructor", bigint(), "0");
}

/**
 * @brief Test the integer constructor
 */
void Integer_Constructor()
{
    std::cout << "Integer Constructor Test\n";
    check("Integer Constructor", bigint(2135451234), "2135451234");
    check("Integer Constructor_negative", bigint(-1234524365), "-1234524365");
}

/**
 * @brief Test the string constructor
 */
void String_Constructor()
{
    std::cout << "String Constructor Test\n";
    check("String Constructor", bigint("12304985"), "12304985");
    check("String Constructor_negative", bigint("-1234524365"), "-1234524365");
}

/**
 * @brief Test the copy constructor of bigint.
 */
void Copy_Constructor()
{
    std::cout << "Copy Constructor Test\n";

    // Copy test: positive, negative, deep copy.
    check("Copy Constructor_positive", bigint(bigint("123123")), "123123");
    check("Copy Constructor_negative", bigint(bigint("-131313")), "-131313");
    bigint negative("-131313");
    bigint c_negative(negative);
    c_negative = bigint("0");
    check("Deep Copy", negative, "-131313");
}

/**
 * @brief Test assignment operator(operator=) for bigint.
 */
void Assignment_Operator()
{
    std::cout << "Assignment Operator Test\n";
    // basic assignment
    bigint a("13131");
    bigint b("24242");
    b = a;
    check("basic Assignment", b, "13131");

    // Self-assignment
    bigint c("42424");
    bigint &temp = c;
    c = temp; // avoid warning (Does not affect function)
    check("Self Assignment", c, "42424");

    // Assignments of different lengths
    bigint d("-11111111");
    bigint e("1222");
    e = d;
    check("Different Length Assignment", e, "-11111111");
}

/**
 * @brief Test the assignment operator for int64_t in the bigint class.
 */
void Int64_Assignment_Operator()
{
    std::cout << "\n Test Assignment Operator (int64_t)\n";

    // basic assignment: assign positive, negative, 0

    bigint a;
    a = 111222333;
    check("Assign positive number", a, "111222333");
    a = -12312312;
    check("Assign negative number", a, "-12312312");
    a = 0;
    check("Assign zero", a, "0");

    // Chained assignment
    bigint b;
    b = a = 12323;
    check("Chained assignment_a", a, "12323");
    check("Chained assignment_b", b, "12323");

    // Self-assignment
    bigint c;
    c = 121312;
    bigint &temp = c;
    c = temp;
    check("Self-assignment", c.get_value(), "121312");
}

/**
 * @brief Tests the 'operator=(const std::string&)` for bigint.
 */
void String_Assignment_Operator()
{
    std::cout << "\n Test String Assignment Operator\n";

    // Basic assignment: positive, negative, 0
    bigint a;
    a = "111111111";
    check("Positive String", a, "111111111");
    a = "-111111111";
    check("Negative String", a, "-111111111");
    a = "0";
    check("Zero String", a, "0");

    // String assignment with leading zero
    a = "000123";
    check("String with Leading Zeros", a, "123");
}

/**
 * @brief Tests the get_value() method of the bigint class.
 */
void Get_Value()
{
    std::cout << "\n Test get_value()\n";
    // Default constructor value
    bigint a;
    check("Default Constructor Value", a.get_value(), "0");

    // Negative values
    bigint b("-2");
    check("Singe Negative", b.get_value(), "-2");

    // Input with leading zero.
    bigint d("0000111");
    check("Leading Zeros", d.get_value(), "111");
}

/**
 * @brief Tests the get_positive() method of the bigint class.
 */
void Get_Positive()
{
    std::cout << "\n Test get_positive()\n";

    // Basic check: positive, negative, 0
    check("Positive Number", bigint("1111111111111").get_positive(), true);
    check("Negative Number", bigint("-11111111111").get_positive(), false);
    check("Zero", bigint("0").get_positive(), true);

    // Combine assignment test
    bigint a("111111");
    bigint &tem = a;
    a = tem;
    check("Assignment Positive", a.get_positive(), true);
    bigint b("-1111111");
    bigint &tem2 = b;
    b = tem2;
    check("Assignment Negative", b.get_positive(), false);

    // Change sign test
    bigint c("11111");
    c = "-22222222";
    check("Change to Negative", c.get_positive(), false);
    bigint d("-222222");
    d = "11111111";
    check("Change to Positive", d.get_positive(), true);

    // Change to zero test
    bigint e("456");
    e = "0";
    check("Change to Zero", e.get_positive(), true);
}

/**
 * @brief Tests the operator+= for the bigint class.
 */
void Plus_Equal_Operator()
{
    std::cout << "\n Test operator+=\n";

    // Basic test: try addition of bigint with different signs
    bigint a("10000");
    a += bigint("-11111");
    check("basic negative", a, "-1111");

    bigint b("11111");
    b += bigint("-10000");
    check("basic positive", b, "1111");

    // Zero test
    bigint c("1111111");
    c += bigint("0");
    check("Zero test_positive", c, "1111111");
    bigint d("-1111111");
    d += bigint("0");
    check("Zero test_negative", d, "-1111111");

    // Self-addition(also large numbers)
    bigint e("111111111111111111111111111");
    e += e;
    check("Self Addition", e, "222222222222222222222222222");
}

/**
 * @brief Tests the operator+ for bigint addition.
 */
void Plus_Operator()
{
    std::cout << " Test operator+\n";
    // Basic Test(also large numbers)
    bigint a("111111111111111111111111111");
    bigint b("111111111111111111111111111");
    check("Large Positive addition", a + b, "222222222222222222222222222");

    check("Negative Addition", bigint("-11111") + bigint("-11111"), "-22222");
    check("Positive + Negative Addition", bigint("11111") + bigint("-22222"), "-11111");

    // Zero test
    check("Zero addition", bigint("0") + bigint("11111"), "11111");
    check("Zero addition_2", bigint("0") + bigint("0"), "0");
}

/**
 * @brief Tests the operator-= for the bigint class.
 */
void Subtraction_Equal_Operator()
{
    std::cout << "\n Test -= Operator\n";

    // Basic test(also large numbers)
    bigint a("222222222222222222222222222222");
    a -= bigint("111111111111111111111111111111");
    check("Large Positive Subtraction", a, "111111111111111111111111111111");
    check("Negative Subtraction", (bigint("-111111") -= bigint("-111111")), "0");
    check("Positive - Negative", (bigint("111111") -= bigint("-111111")), "222222");
    check("Positive - Larger Positive", (bigint("11111") -= bigint("22222")), "-11111");
    check("Negative - Smaller Negative", (bigint("-11111") -= bigint("-22222")), "11111");
    // Self-subtraction
    check("Self Subtraction", (bigint("333333") -= bigint("333333")), "0");
    // Zero test
    check("Zero - Zero", (bigint("0") -= bigint("0")), "0");
    check("Zero - Positive", (bigint("0") -= bigint("111")), "-111");
    check("Zero - Negative", (bigint("0") -= bigint("-111")), "111");
}

/**
 * @brief Tests the overloaded subtraction operator (-).
 */
void Subtraction_Operator()
{
    std::cout << "\n Test Subtraction Operator (-)\n";
    // Basic test(also large numbers)
    bigint a("222222222222222222222222222222");
    a -= bigint("111111111111111111111111111111");
    check("Large Positive Subtraction", a, "111111111111111111111111111111");
    check("Positive - Positive", (bigint("22222") - bigint("11111")), "11111");
    check("Positive - Negative", (bigint("11111") - bigint("-11111")), "22222");
    check("Negative - Positive", (bigint("-11111") - bigint("11111")), "-22222");
    check("Negative - Negative", (bigint("-11111") - bigint("-22222")), "11111");

    // Zero test
    check("Zero - Positive", (bigint("0") - bigint("111111")), "-111111");
    check("Positive - Zero", (bigint("1111111") - bigint("0")), "1111111");
    check("Zero - Zero", (bigint("0") - bigint("0")), "0");
}

/**
 * @brief Tests the *= operator for bigint multiplication.
 */
void Multiply_Equal_Operator()
{
    std::cout << "\n Test operator*=\n";

    // Basic test(also large numbers)
    bigint a("1111111111111111");
    bigint b("1111111111111111");
    a *= b;
    check("Large Positive * Positive", a, "1234567901234567654320987654321");

    // Zero test
    check("Any Number * Zero", (bigint("123123") *= bigint("0")), "0");
    // Self-multiplication
    check("Self Multiplication", (bigint("100") *= bigint("100")), "10000");

    // Large Number * Small Number
    check("Large Number * Small Number", (bigint("11111111") *= bigint("2")), "22222222");
}

/**
 * @brief Tests the * operator for bigint multiplication.
 */
void Multiplication_Operator()
{
    std::cout << "\n Test Multiplication Operator (*)\n";

    // Basic test (also large numbers)
    bigint a("1111111111111111");
    bigint b("1111111111111111");
    check("Large Positive * Positive", (a * b), "1234567901234567654320987654321");
    check("Negative * Positive", (bigint("-1000") * bigint("50")), "-50000");

    // Zero test
    check("Any Number * Zero", (bigint("123123") * bigint("0")), "0");

    // Large Number * Small Number
    check("Large Number * Small Number", (bigint("1111111111111111") * bigint("2")), "2222222222222222");

    // Self-multiplication
    check("Self Multiplication", (bigint("100") * bigint("100")), "10000");
}

/**
 * @brief Tests the operator/= for bigint division.
 */
void Division_Equal_Operator()
{
    std::cout << "\n Test Division Operator (/=)\n";

    // Basic test (also large numbers)
    bigint a("33333333333333333333");
    bigint b("3");
    a /= b;
    check("Large Number / Small Number", a, "11111111111111111111");
    check("Negative / Positive", (bigint("-100") /= bigint("2")), "-50");

    // Self-division
    check("Self Division", (bigint("11111") /= bigint("11111")), "1");

    // Special case: dividend is smaller than divisor
    check("Small / Large", (bigint("1") /= bigint("999")), "0");
}

/**
 * @brief Tests the operator/  for bigint division.
 */
void Division_Operator()
{
    std::cout << "\n Test Division Operator (/)\n";
    // Basic test (also large numbers)
    bigint a("33333333333333333333");
    bigint b("3");
    bigint c = a / b;
    check("Large Number / Small Number", c, "11111111111111111111");
    check("Self-division", (bigint("111") / bigint("111")), "1");

    // Negative division tests
    check("-Negative / Positive", (bigint("-100") / bigint("2")), "-50");
    check("Negative / Negative", (bigint("-100") / bigint("-2")), "50");
}

/**
 * @brief Tests the operator%= for bigint modulus.
 */
void Modulus_Equal_Operator()
{
    std::cout << "\n Test Modulus Operator (%=)\n";

    // Basic test (also tests large numbers)
    bigint a("33333333333333333333");
    bigint b("3");
    a %= b;
    check("Large Number % Small Number", a, "0");
    check("Basic Modulus", (bigint("100") %= bigint("3")), "1");
    check("Negative % Positive", (bigint("-100") %= bigint("3")), "-1");
    check("Positive % Negative", (bigint("100") %= bigint("-3")), "1");
    check("Negative % Negative", (bigint("-100") %= bigint("-3")), "-1");
}

/**
 * @brief Tests the operator% for bigint modulus.
 */
void Modulus_Operator()
{
    std::cout << "\n Test Modulus Operator (%)\n";

    // Basic test (also large numbers)
    bigint a("1000000000000000");
    bigint b("3");
    bigint c = a % b;
    check("Large Number % Small Number", c, "1");
    // Because % reuse %=, the rest of the tests are no different from %=.
}

/**
 * @brief Tests the operator++ for bigint prefix increment.
 */
void Prefix_Increment_Operator()
{
    std::cout << "\n Test Prefix Increment Operator (++)\n";

    // Basic test (also large numbers)
    bigint a("11111111111111111111");
    ++a;
    check("Large Number ++", a, "11111111111111111112");
    check("Carry Test", (++bigint("9")), "10");

    // Multi times increments
    bigint i("999");
    ++(++i);
    check("Multi Times Increments", i, "1001");
}

/**
 * @brief Tests the operator-- for bigint prefix decrement.
 */
void Prefix_Decrement_Operator()
{
    std::cout << "\n Test Prefix Decrement Operator (--)\n";

    // Basic test (also large numbers)
    bigint a("1000000000000000000");
    --a;
    check("Large Number --", a, "999999999999999999");
    check("Borrow Test", (--bigint("10")), "9");
    check("Negative Decrement", (--bigint("-100")), "-101");

    // Multi times decrements
    bigint i("1");
    --(--i);
    check("Multi Times Decrements", i, "-1");
}

/**
 * @brief Tests the operator++ for bigint postfix increment.
 */
void Postfix_Increment_Operator()
{
    std::cout << "\n Test Postfix Increment Operator (++)\n";

    // Basic test (also large numbers)
    bigint a("999999999999999999");
    check("Postfix ++ Large Number (return)", (a++), "999999999999999999");
    check("Postfix ++ Large Number (final)", a, "1000000000000000000");
    bigint b("0");
    check("Postfix ++ 0 (return value)", b++, "0");
    check("Postfix ++ 0 (final value)", b, "1");
}

/**
 * @brief Tests the operator-- for bigint postfix decrement.
 */
void Postfix_Decrement_Operator()
{
    std::cout << "\n Test Postfix Decrement Operator (--)\n";

    // Basic test (also large numbers)
    bigint a("1000000000000000000");
    check("Postfix -- Large Number (return)", (a--), "1000000000000000000");
    check("Postfix -- Large Number (final)", a, "999999999999999999");

    bigint c("0");
    check("Postfix -- 0 (return)", (c--), "0");
    check("Postfix -- 0 (final)", c, "-1");
}

/**
 * @brief Tests the operator+ for bigint unary plus.
 */
void Unary_Plus_Operator()
{
    std::cout << "\n Test Unary Plus Operator (+)\n";

    // Basic test (also large numbers)
    bigint a("111111111111111111111111111111");
    check("Unary + Large Number", (+a), "111111111111111111111111111111");
    check("Unary + Negative", (+bigint("-1111111111")), "-1111111111");

    // Reference check
    bigint b("1111111");
    if (&b == &(+b))
    {
        std::cout << "Pass: Reference check for +1111111\n";
        ++pass_unit;
    }
    else
    {
        std::cout << "Fail: Reference check for +1111111\n";
        ++fail_unit;
    }
}

/**
 * @brief Tests the operator- for bigint unary minus.
 */
void Unary_Minus_Operator()
{
    std::cout << "\n Test Unary Minus Operator (-)\n";

    // Basic test (also large numbers)
    bigint a("111111111111111111111111111");
    check("Unary - Large Positive Number", (-a), "-111111111111111111111111111");
    check("Unary - Negative", (-bigint("-111111")), "111111");

    // Reference check
    bigint b("111111");
    bigint temp = -b;
    if (&b != &temp)
    {
        std::cout << "Pass: Reference check for -111111\n";
        ++pass_unit;
    }
    else
    {
        std::cout << "Fail: Reference check for -111111\n";
        ++fail_unit;
    }
}

/**
 * @brief Tests the operator> for bigint Bigger than comparison.
 */
void Bigger_Than_Operator()
{
    std::cout << "\n Test Bigger Than Operator (>)\n";

    // Basic test (also large numbers)
    bigint a("33333333333333333333333333333");
    bigint b("22222222222222222222222222222");
    check("Large Numbers", (a > b), true);
    check("Equal Numbers", (bigint("1111") > bigint("1111")), false);
    check("Positive > Negative", (bigint("111") > bigint("-111")), true);
    check("Negative > Positive", (bigint("-111") > bigint("111")), false);
    check("Negative > Negative", (bigint("-1") > bigint("-2")), true);
    check("Negative > Larger Negative", (bigint("-100") > bigint("-99")), false);
    // Zero comparisons
    check("Positive > Zero", (bigint("1") > bigint("0")), true);
    check("Zero > Positive", (bigint("0") > bigint("1")), false);
}

/**
 * @brief Tests the operator== for bigint equality comparison.
 */
void Equal_Operator()
{
    std::cout << "\n Test Equality Operator (==)\n";

    // Basic test (also large numbers)
    bigint a("33333333333333333333333333333");
    bigint b("33333333333333333333333333333");
    check("Large Numbers Equality", (a == b), true);
    check("Positive != Negative", (bigint("111") == bigint("-111")), false);
    check("Negative == Negative", (bigint("-1") == bigint("-1")), true);
    check("Negative != Larger Negative", (bigint("-100") == bigint("-99")), false);
    // Zero comparisons
    check("Zero == Zero", (bigint("0") == bigint("0")), true);
    check("Zero == Negative Zero", (bigint("0") == bigint("-0")), true);
}

/**
 * @brief Tests the operator>= for bigint bigger than or equal comparison.
 */
void Bigger_Or_Equal_Operator()
{
    std::cout << "\n Test Bigger Than or Equal Operator (>=)\n";

    // Basic test (also large numbers)
    bigint a("33333333333333333333333333333");
    bigint b("33333333333333333333333333333");
    check("Large Numbers Bigger Or Equal", (a >= b), true);
    check("Positive >= Negative", (bigint("111") >= bigint("-111")), true);
    check("Negative >= Positive", (bigint("-111") >= bigint("111")), false);
    check("Negative >= Negative (Equal)", (bigint("-1") >= bigint("-1")), true);
    check("Negative >= Larger Negative", (bigint("-99") >= bigint("-100")), true);
    check("Smaller Negative >= Larger Negative", (bigint("-100") >= bigint("-99")), false);

    // Zero comparisons
    check("Zero >= Zero", (bigint("0") >= bigint("0")), true);
    check("Positive >= Zero", (bigint("1") >= bigint("0")), true);
    check("Negative >= Zero", (bigint("-1") >= bigint("0")), false);
}

// Other comparison tests are not really necessary, because they reuse operator> and operator==!! but still try.

/**
 * @brief Tests the operator< for bigint Less than comparison.
 */
void Less_Operator()
{
    std::cout << "\n Test Less Than Operator (<)\n";

    // Basic test (also large numbers)
    bigint a("22222222222222222222222222222");
    bigint b("33333333333333333333333333333");
    check("Large Numbers", (a < b), true);
    check("Equal Numbers", (bigint("1111") < bigint("1111")), false);
    check("Positive < Negative", (bigint("111") < bigint("-111")), false);
    check("Negative < Positive", (bigint("-111") < bigint("111")), true);
    check("Negative < Negative", (bigint("-2") < bigint("-1")), true);
    check("Negative < Larger Negative", (bigint("-100") < bigint("-99")), true);

    // Zero comparisons
    check("Zero < Positive", (bigint("0") < bigint("1")), true);
    check("Positive < Zero", (bigint("1") < bigint("0")), false);
}

/**
 * @brief Tests the operator<= for bigint Less than or equal comparison.
 */
void Less_Or_Equal_Operator()
{
    std::cout << "\n Test Less or Equal Operator (<=)\n";

    // Basic test (also large numbers)
    bigint a("22222222222222222222222222222");
    bigint b("33333333333333333333333333333");
    check("Large Numbers", (a <= b), true);
    check("Equal Numbers", (bigint("1111") <= bigint("1111")), true);
    check("Positive <= Negative", (bigint("111") <= bigint("-111")), false);
    check("Negative <= Positive", (bigint("-111") <= bigint("111")), true);
    check("Negative <= Negative", (bigint("-2") <= bigint("-1")), true);
    check("Negative <= Larger Negative", (bigint("-100") <= bigint("-99")), true);

    // Zero comparisons
    check("Zero <= Positive", (bigint("0") <= bigint("1")), true);
    check("Positive <= Zero", (bigint("1") <= bigint("0")), false);
}

/**
 * @brief Tests the operator!= for bigint comparison.
 */
void Not_Equal_Operator()
{
    std::cout << "\n Test Not Equal Operator (!=)\n";

    // Basic test (also large numbers)
    bigint a("33333333333333333333333333333");
    bigint b("22222222222222222222222222222");
    check("Large Numbers", (a != b), true);
    check("Equal Numbers", (bigint("1111") != bigint("1111")), false);
    check("Negative != Negative", (bigint("-2") != bigint("-1")), true);
    check("Negative != Same Negative", (bigint("-100") != bigint("-100")), false);

    // Zero comparisons
    check("Zero != Zero", (bigint("0") != bigint("0")), false);
    check("Zero != Negative Zero", (bigint("0") != bigint("-0")), false);
}

/**
 * @brief Tests the operator<< for bigint output.
 */
void Output_Operator()
{
    std::cout << "\n Test Output Operator (<<)\n";

    // Basic test (also large numbers)
    bigint a("33333333333333333333333333333");
    check_output("Large Number", a, "33333333333333333333333333333");
    check_output("Positive Number", bigint("1111"), "1111");
    check_output("Negative Number", bigint("-1111"), "-1111");

    // Zero comparisons
    check_output("Zero", bigint("0"), "0");
    check_output("Negative Zero", bigint("-0"), "0");
}

/**
 * @brief Tests the pow function.
 */
void Power_Function()
{
    std::cout << "\n Test Power Function (pow)\n";

    // Basic test (also large numbers)
    bigint a("100000");
    check("Basic Power_large number", pow(a, bigint("10")), "100000000000000000000000000000000000000000000000000");

    check("Positive Base & Positive Exponent", pow(bigint("2"), bigint("10")), "1024");
    check("Negative Base & Positive Exponent", pow(bigint("-2"), bigint("3")), "-8");
    // Zero test
    check("Zero Base", pow(bigint("0"), bigint("5")), "0");
    check("Zero Exponent", pow(bigint("5"), bigint("0")), "1");
}

/**
 * @brief Tests the trim() function for bigint.
 */
void Trim_Function()
{
    std::cout << "\n Test trim() Function\n";

    // Basic test (also large numbers)
    bigint a("000000000111");
    check("Trim Leading Zeros", a, "111");
    check("Trim All", bigint("0000"), "0");
    check("Trim Zero", bigint("0"), "0");
    check("Trim Negative Leading Zeros", bigint("-000123"), "-123");

    // Large number test
    std::string large_number = std::string(1000, '0') + "123";
    bigint large_num(large_number);
    check("Trim Large numbers with 1000 Zeros", large_num, "123");
}

// ==================================
//        Integration Test
// ==================================

/**
 * @brief Combining multiple operations for integration tests: .
 */
void Integration_Tests()
{
    std::cout << "\n Test Integration Tests of Multiple Operations\n";

    // Construct, addition, multiplication combination(also large numbers)
    bigint a("11111111111111111111111");
    bigint b("11111111111111111111111");
    check_integration("Construct&Addition&Multiplication", ((a + b) * a), "246913580246913580246908641975308641975308642");

    // Addition, subtraction, division combination
    bigint c("1000");
    bigint d("500");
    check_integration("Addition&Subtraction&Division", (((c + d) - c) / bigint("5")), "100");

    // Division, modulus, multiplication combination
    bigint e("100");
    bigint f("50");
    check_integration("Division&Modulus&Multiplication", (((e / f) % bigint("7")) * bigint("3")), "6");

    // Increment, addition, multiplication, division combination
    bigint g("10");
    ++g;
    check_integration("Increment&Addition&Multiplication&Division", ((g + bigint("10")) * bigint("2") / bigint("5")), "8"); // (11 + 10) * 2 / 4 = 10

    // Addition, subtraction, multiplication, division, modulus combination
    bigint h("100");
    bigint k("20");
    check_integration("Include All Operations", ((((h + k) * bigint("3")) - k) / bigint("3") % bigint("5")), "3");
    // ((100 + 20) * 3 - 20) / 3 % 5 = 3
}

// ==================================
//        Edge Test
// ==================================
// In fact, part of the edge test is already done during the unit test, and the edge test here is supplementary.

/**
 * @brief Tests edge cases for the bigint class.
 */
void Edge_Case_Tests()
{
    std::cout << "\n Test Edge Cases\n";

    //  Addition
    check_edge("Carry test", bigint("9999999999") + bigint("1"), "10000000000");
    // Subtraction
    check_edge("Borrow test", bigint("10000000000") - bigint("1"), "9999999999");
    // Multiplication
    check_edge("Zero test", bigint("999") * bigint("0"), "0");
    // Division
    check_edge("Divide by big Number", bigint("1") / bigint("11111111"), "0");
    // Modulus
    check_edge("Modulus Zero", bigint("0") % bigint("7"), "0");
    // Pow
    check_edge("Zero to Zero", pow(bigint("0"), bigint("0")), "1");
    ;
}

// ==================================
//        Error Test
// ==================================

/**
 *
 * @brief Tests for error cases in the bigint class.
 */
void Error_Tests()
{
    std::cout << "\n Test Error Cases\n";
    // Test String constructor
    // String constructor inputs error test
    try
    {
        bigint c("111111qq111");
        std::cout << "Fail: Invalid character.\n";
        ++fail_error;
    }
    catch (const std::invalid_argument &e)
    {
        std::cout << "Pass: Invalid character: Exception caught: " << e.what() << "\n";
        ++pass_error;
    }

    // Input with only '-' character erro test.
    try
    {
        bigint d("-");
        std::cout << "Fail: Only negative sign.\n";
        ++fail_error;
    }
    catch (const std::invalid_argument &e)
    {
        std::cout << "Pass: Only negative sign: Exception caught: " << e.what() << "\n";
        ++pass_error;
    }

    // Input with an empty string error
    try
    {
        bigint e("");
        std::cout << "Fail: Empty string.\n";
        ++fail_error;
    }
    catch (const std::invalid_argument &e)
    {
        std::cout << "Pass: Empty string: Exception caught: " << e.what() << "\n";
        ++pass_error;
    }

    // Test string assignment
    // Empty string assignment
    try
    {
        bigint b;
        b = "";
        std::cout << "Fail: Empty string.\n";
        ++fail_error;
    }
    catch (const std::invalid_argument &e)
    {
        std::cout << "Pass: Empty string: Exception caught: " << e.what() << "\n";
        ++pass_error;
    }

    // Assignment with only '-' character
    try
    {
        bigint c;
        c = "-";
        std::cout << "Fail: Only negative sign.\n";
        ++fail_error;
    }
    catch (const std::invalid_argument &e)
    {
        std::cout << "Pass: Only negative sign: Exception caught: " << e.what() << "\n";
        ++pass_error;
    }

    // Division by zero in /= operator
    try
    {
        bigint d("11111");
        d /= bigint("0");
        std::cout << "Fail: Division by zero.\n";
        ++fail_error;
    }
    catch (const std::invalid_argument &e)
    {
        std::cout << "Pass: Division by zero: Exception caught:" << e.what() << "\n";
        ++pass_error;
    }

    // Division by zero in / operator
    try
    {
        bigint result = bigint("111111") / bigint("0");
        std::cout << "Fail: Division by zero.\n";
        ++fail_error;
    }
    catch (const std::invalid_argument &e)
    {
        std::cout << "Pass: Division by zero: Exception caught: " << e.what() << "\n";
        ++pass_error;
    }

    // modulus by zero in %= operator
    try
    {
        bigint e("111111");
        e %= bigint("0");
        std::cout << "Fail: Modulus by zero.\n";
        ++fail_error;
    }
    catch (const std::invalid_argument &e)
    {
        std::cout << "Pass: Modulus by zero: Exception caught: " << e.what() << "\n";
        ++pass_error;
    }

    // Modulus by zero in % operator
    try
    {
        bigint f("1111111");
        bigint result = f % bigint("0");
        std::cout << "Fail: Modulus by zero.\n";
        ++fail_error;
    }
    catch (const std::invalid_argument &e)
    {
        std::cout << "Pass: Modulus by zero: Exception caught: " << e.what() << "\n";
        ++pass_error;
    }

    // Negative exponent in pow
    try
    {
        pow(bigint("5"), bigint("-1"));
        std::cout << "Fail: Negative exponent.\n";
        ++fail_error;
    }
    catch (const std::invalid_argument &e)
    {
        std::cout << "Pass: Negative exponent: Exception caught: " << e.what() << "\n";
        ++pass_error;
    }

    // Negative exponent in pow with int64
    try
    {
        pow(bigint("3"), -1);
        std::cout << "Fail: Negative exponent.\n";
        ++fail_error;
    }
    catch (const std::invalid_argument &e)
    {
        std::cout << "Pass: Negative exponent: Exception caught: " << e.what() << "\n";
        ++pass_error;
    }
}

// ========================================
//        Consistency Test(Randomly)
// ========================================

/**
 * @brief Generates a random bigint string.
 *
 * @param length Length of the bigint.
 * @return A random bigint as a string.
 */
std::string Random_Bigint(int64_t length)
{
    static std::random_device rd;
    static std::mt19937 mt(rd());
    std::uniform_int_distribution<int64_t> digit(0, 9);
    std::uniform_int_distribution<int64_t> first_digit(1, 9);
    std::uniform_int_distribution<int64_t> sign_dist(0, 1);

    std::string result;
    result += std::to_string(first_digit(mt)); // Ensure first digit is non-zero
    for (int64_t i = 1; i < length; ++i)
    {
        result += std::to_string(digit(mt));
    }

    if (sign_dist(mt) == 1)
    {
        result = "-" + result;
    }

    return result;
}

/**
 * @brief Tests the consistency of (A + B) - C == (A - C) + B
 *
 * @param count Number of random tests to run.
 */
void Addition_Subtraction_Consistency(int64_t count = 5)
{
    std::cout << "\n Test Addition and Subtraction Consistency\n";

    for (int64_t i = 0; i < count; ++i)
    {
        bigint A(Random_Bigint(11));
        bigint B(Random_Bigint(22));
        bigint C(Random_Bigint(33));
        check_consistency("Addition, Subtraction", (A + B) - C, (A - C) + B);
    }
}

/**
 * @brief Tests the consistency of A * (B + C) == (A * B) + (A * C) for random bigints.
 *
 * @param count Number of random tests to run.
 */
void Distributive_Multiplication_Consistency(int64_t count = 5)
{
    std::cout << "\n Test Distributive of multiplication Consistency\n";

    for (int64_t i = 0; i < count; ++i)
    {
        bigint A(Random_Bigint(22));
        bigint B(Random_Bigint(13));
        bigint C(Random_Bigint(24));
        check_consistency("Distributive of Multiplication", A * (B + C), (A * B) + (A * C));
    }
}

/**
 * @brief Tests the consistency of (A + B) / C == A / C + B / C for random bigints.
 *
 * @param count Number of random tests to run.
 */
void Distributive_Division_Consistency(int64_t count = 5)
{
    std::cout << "\n Test Distributive of Division Consistency\n";

    for (int64_t i = 0; i < count; ++i)
    {
        bigint A(Random_Bigint(11));
        bigint B(Random_Bigint(11));
        bigint C(Random_Bigint(22));

        check_consistency("Distributive of Division", (A + B) / C, (A / C) + (B / C));
    }
}

/**
 * @brief Tests the consistency of (A * B) / B == A for random bigints.
 *
 * @param count Number of random tests to run .
 */
void Multiplication_Division_Consistency(int64_t count = 5)
{
    std::cout << "\n Test Multiplication-Division Consistency\n";

    for (int64_t i = 0; i < count; ++i)
    {
        bigint A(Random_Bigint(10));
        bigint B(Random_Bigint(3));
        check_consistency("Multiplication-Division", (A * B) / B, A);
    }
}

// ==================================
//        Strees Test
// ==================================

/**
 * @brief Strees test for addition of large numbers.
 *
 */
void Stress_Test()
{
    std::string large_a = std::string(2000, '0') + "1";
    std::string large_b = std::string(2000, '0') + "5";

    bigint big_a(large_a);
    bigint big_b(large_b);
    bigint big_c = big_a + big_b;
    bigint big_d = big_a * big_b;
    bigint goal_addition(std::string(2000, '0') + "6");
    bigint goal_multiply(std::string(4000, '0') + "5");

    check_stress("Stress test(addition)", big_c, goal_addition);
    check_stress("Stress Test(multiplication)", big_d, goal_multiply);
}

// ==================================
//        Comparison Test
// ==================================

/**
 * @brief Comparison tests using input from "input.txt", which generated by R language.
 *
 * The input file should contain columns of the form:
 * first big integer, operator,  first big integer, calculate result
 * @param file is the filename
 */
void Comparison_Test(const std::string &file)
{
    std::ifstream inputfile("data/" + file);
    if (!inputfile)
    {
        throw std::invalid_argument("Cannot open " + file);
    }

    std::string bigint_1, operator_1, bigint_2, cal_bigint;
    while (inputfile >> bigint_1 >> operator_1 >> bigint_2 >> cal_bigint)
    {
        bigint a(bigint_1);
        bigint b(bigint_2);
        bigint expected(cal_bigint);
        bigint result;

        if (operator_1 == "+")
        {
            result = a + b;
        }
        else if (operator_1 == "-")
        {
            result = a - b;
        }
        else if (operator_1 == "*")
        {
            result = a * b;
        }
        else if (operator_1 == "/")
        {
            result = a / b;
        }
        else
        {
            result = a % b;
        }

        check_comparison(bigint_1 + " " + operator_1 + " " + bigint_2, result, cal_bigint);
    }
}

int main()
{
    // Unit Tests
    Default_Constructor();
    Integer_Constructor();
    String_Constructor();
    Copy_Constructor();
    Assignment_Operator();
    Int64_Assignment_Operator();
    String_Assignment_Operator();
    Get_Value();
    Get_Positive();
    Plus_Equal_Operator();
    Plus_Operator();
    Subtraction_Equal_Operator();
    Subtraction_Operator();
    Multiply_Equal_Operator();
    Multiplication_Operator();
    Division_Equal_Operator();
    Division_Operator();
    Modulus_Equal_Operator();
    Modulus_Operator();
    Prefix_Increment_Operator();
    Prefix_Decrement_Operator();
    Postfix_Increment_Operator();
    Postfix_Decrement_Operator();
    Unary_Plus_Operator();
    Unary_Minus_Operator();
    Bigger_Than_Operator();
    Equal_Operator();
    Bigger_Or_Equal_Operator();
    Less_Operator();
    Less_Or_Equal_Operator();
    Not_Equal_Operator();
    Power_Function();
    Trim_Function();
    std::cout << "_______Unit Test Finish line_______\n";

    // Integration Tests
    Integration_Tests();
    std::cout << "_______Integration Test Finish line_______\n\n";

    // Edge Case Tests
    Edge_Case_Tests();
    std::cout << "_______Edge Test Finish line_______\n\n";

    // Error Handling Tests
    Error_Tests();
    std::cout << "_______Error Test Finish line_______\n\n";

    // Consistency Tests
    Addition_Subtraction_Consistency();
    Distributive_Multiplication_Consistency();
    Distributive_Division_Consistency();
    Multiplication_Division_Consistency();
    std::cout << "_______Consistency Test Finish line_______\n\n";

    // Stress Test
    Stress_Test();
    std::cout << "_______Stress Test Finish line_______\n\n";

    // Comparison Test
    Comparison_Test("input.txt");
    std::cout << "_______Comparison Test Finish line_______\n\n";

    // Ouput the summary of tests.
    std::cout << " Unit Test Section Summary\n";
    std::cout << "Total: " << (pass_unit + fail_unit) << "\n";
    std::cout << "Passed: " << pass_unit << "\n";
    std::cout << "Failed: " << fail_unit << "\n\n";

    std::cout << "Integration Test Section Summary\n";
    std::cout << "Total: " << (pass_integration + fail_integration) << "\n";
    std::cout << "Passed: " << pass_integration << "\n";
    std::cout << "Failed: " << fail_integration << "\n\n";

    std::cout << " Edge Test Section Summary\n";
    std::cout << "Total: " << (pass_edge + fail_edge) << "\n";
    std::cout << "Passed: " << pass_edge << "\n";
    std::cout << "Failed: " << fail_edge << "\n\n";

    std::cout << " Error Test Section Summary\n";
    std::cout << "Total: " << (pass_error + fail_error) << "\n";
    std::cout << "Passed: " << pass_error << "\n";
    std::cout << "Failed: " << fail_error << "\n\n";

    std::cout << " Consistency Test Section Summary \n";
    std::cout << "Total: " << (pass_consistency + fail_consistency) << "\n";
    std::cout << "Passed: " << pass_consistency << "\n";
    std::cout << "Failed: " << fail_consistency << "\n\n";

    std::cout << " Stress Test Section Summary \n";
    std::cout << "Total: " << (pass_stress + fail_stress) << "\n";
    std::cout << "Passed: " << pass_stress << "\n";
    std::cout << "Failed: " << fail_stress << "\n\n";

    std::cout << " Comparison Test Section Summary \n";
    std::cout << "Total: " << (pass_comparison + fail_comparison) << "\n";
    std::cout << "Passed: " << pass_comparison << "\n";
    std::cout << "Failed: " << fail_comparison << "\n\n";

    if (fail_consistency == 0 && fail_error == 0 && fail_edge == 0 && fail_integration == 0 && fail_unit == 0 && fail_stress == 0 && fail_comparison == 0)
    {
        std::cout << "Completely Success" << std::endl;
    }
    else
    {
        std::cout << "Need to check again!" << std::endl;
    }
}
