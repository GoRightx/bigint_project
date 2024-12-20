#ifndef BIG_INT_HPP
#define BIG_INT_HPP
/**
 * @file bigint.hpp
 * @author Zuoxiang Bu(Student NO.:400553917) (buz2@mcmaster.ca)
 * @date 2024-12-20
 * @brief The header file for the bigint class.
 *
 * This file contains the declaration of the bigint class, also overloaded operators
 * and necessary member functions for arithmetic operations, comparisons, and other functions.
 */

#include <string>    // std::string for string manipulation
#include <vector>    // std::vector for dynamic arrays
#include <iostream>  // std::cout for output
#include <stdexcept> // std::invalid_argument, std::logic_error for exceptions

/**
 * @class bigint
 * @brief A class for handling big integers
 *
 * This class provides operations for big integers, including initialization, addition, subtraction, multiplication, division,
 * modulus, and comparison operations.
 */

class bigint
{

public:
    // ============================
    //         Constructors
    // ============================

    /**
     * @brief Constructors for creating bigint objects from different types of inputs.
     */
    bigint();                    // Default constructor: initializes bigint to zero.
    bigint(const int64_t &);     // Constructor for a integer input.
    bigint(const std::string &); // Constructor for a string input.
    bigint(const bigint &);      // Constructor for creating a new bigint by copying another one.

    // ==================================
    //         Operator Overloading
    // ==================================

    /**
     * @name Assignment operators
     * @brief Overloaded assignment operators for the bigint class.
     *
     */
    bigint &operator=(const bigint &);      // Assign values to a bigint object from another bigint.
    bigint &operator=(const int64_t &);     // Assign values to a bigint object from a 64-bit integer.
    bigint &operator=(const std::string &); // Assign values to a bigint object from a a string.

    /**
     * @name Arithmetic and unary operators
     * @brief Overloaded operators for arithmetic operations, increment/decrement, and unary operations.
     *
     * Including addition, subtraction ,multiplication, division, modulus,
     * , increment, decrement, and unary operations.
     */
    // Addition
    bigint &operator+=(const bigint &rhs);
    friend bigint operator+(const bigint &lhs, const bigint &rhs); // Designed as a friend, it can be calculated in bigint and normal integers, such as bigint(1) + 2, although it is not needed
    // Subtraction
    bigint &operator-=(const bigint &rhs);
    friend bigint operator-(const bigint &lhs, const bigint &rhs);
    // Multiplication
    bigint &operator*=(const bigint &rhs);
    friend bigint operator*(const bigint &lhs, const bigint &rhs);
    // Division
    bigint &operator/=(const bigint &rhs);
    friend bigint operator/(const bigint &lhs, const bigint &rhs);
    // Modulus
    bigint &operator%=(const bigint &);
    friend bigint operator%(const bigint &, const bigint &);
    // Increment and Decrement
    bigint &operator++();         // Prefix increment (++a).
    bigint &operator--();         // Prefix decrement (--a).
    const bigint operator++(int); // Postfix increment (a++).
    const bigint operator--(int); // Postfix decrement (a--).
    // Unary
    bigint &operator+();      // return itself
    bigint operator-() const; // returns the negation.

    /**
     * @name Comparison operators
     * @brief Overloaded comparison operators for the bigint class. And return a boolean result.
     *
     */
    friend bool operator>(const bigint &lhs, const bigint &rhs);
    friend bool operator==(const bigint &lhs, const bigint &rhs);
    friend bool operator>=(const bigint &lhs, const bigint &rhs);
    friend bool operator<(const bigint &lhs, const bigint &rhs);
    friend bool operator<=(const bigint &lhs, const bigint &rhs);
    friend bool operator!=(const bigint &lhs, const bigint &rhs);

    /**
     * @name Stream operators
     * @brief Overloaded output stream for the bigint class.
     *
     */
    friend std::ostream &operator<<(std::ostream &, const bigint &);

    /**
     * @brief Calculate the power of a bigint raised to another bigint or an integer exponent
     */
    friend bigint pow(const bigint &, const bigint &);

    /**
     * @brief Returns the bigint value as a string.
     *
     * @return Get the string representation of the bigint.
     */
    std::string get_value() const;

    /**
     * @brief Checks if the bigint is positive.
     *
     * @return if the bigint is positive return true, otherwise return false.
     */
    bool get_positive();

    /**
     * @brief Returns the size of the vec.
     *
     * @return The size of the vec.
     */
    size_t get_vec_size() const
    {
        return vec.size();
    }

    /**
     * @brief Remove any leading zeros from the stored digits
     *
     */
    void trim();

private:
    /**
     * @name Private members
     * @brief These are private member variables and functions for internal use.
     */

    /**
     * @brief A vector to store the digits of the bigint.Each element of the vector represents a single decimal digit (0-9)
     * stored as an 8-bit unsigned integer (uint8_t). In reverse order.
     */
    std::vector<uint8_t> vec;

    /**
     * @brief Initializes constexpr static member variables. These members representing zero, one, two, and ten respectively
     */
    static const bigint s_zero;
    static const bigint s_one;
    static const bigint s_two;
    static const bigint s_ten;

    /**
     * @brief Represent the bigint wether is positive.
     */
    bool is_Positive;
};

/**
 * @brief Initializes static member variables.
 */

const bigint bigint::s_zero = bigint(0);
const bigint bigint::s_one = bigint(1);
const bigint bigint::s_two = bigint(2);
const bigint bigint::s_ten = bigint(10);

/**
 * @brief Default constructor for bigint. Initializes the bigint to zero with a positive sign.
 *
 */
bigint::bigint()
{
    // vec.clear();
    vec.push_back(0);
    is_Positive = true;
}

/**
 * @brief Constructs a bigint from a 64-bit integer.
 *
 * @param a The 64-bit integer, initializing the bigint.
 */

bigint::bigint(const int64_t &a)
{
    vec.clear();
    vec.reserve(20); // Reserve vec for efficiency.

    if (a >= 0)
    {
        is_Positive = true;
    }
    else
    {
        is_Positive = false;
    }
    // If the value is zero, store it and exit
    if (a == 0)
    {
        vec.push_back(0);
        return;
    }

    // use uint64_t to handle the negative number to avoid overflow of int64_t
    uint64_t temp_val;
    if (a == INT64_MIN)
    {
        temp_val = static_cast<uint64_t>(INT64_MAX) + 1;
    }
    else
    {
        if (a >= 0)
        {
            temp_val = static_cast<uint64_t>(a);
        }
        else
        {
            temp_val = static_cast<uint64_t>(-a);
        }
    }

    // Extract each digit and store it in vec
    while (temp_val > 0)
    {
        uint8_t t = static_cast<uint8_t>(temp_val % 10);
        vec.push_back(t);
        temp_val /= 10;
    }
}

/**
 * @brief Constructs a bigint from a string.
 *
 * @param str The string used to initialize the bigint.
 */
bigint::bigint(const std::string &str)
{
    // check wether the str is empty.
    if (str.empty())
    {
        throw std::invalid_argument("Input string is empty"); // std::invalid_argument: If the string is empty.
    }
    vec.clear();
    vec.reserve(str.length());
    is_Positive = true;
    size_t temp = 0;
    if (str[0] == '-')
    {
        is_Positive = false;
        temp = 1; // The indicator for skipping the '-'.
    }
    if (str.length() == temp)
    {
        throw std::invalid_argument("Input string is only '-' or empty"); // std::invalid_argument: If the string is '-'.
    }

    for (size_t i = str.length(); i-- > temp;)
    {
        if (!std::isdigit(str[i]))
        {
            throw std::invalid_argument("Input string contains non-digit character"); // std::invalid_argument: If the string contains non-digit character.
        }
        vec.push_back(static_cast<uint8_t>(str[i] - '0'));
    }
    trim();
}

/**
 * @brief Copy constructor for bigint.
 *
 * @param a This is bigint object which be copied.
 */
bigint::bigint(const bigint &a)
{
    vec.clear();
    if (a.is_Positive == true)
    {
        is_Positive = true;
    }
    else
    {
        is_Positive = false;
    }
    vec.reserve(a.vec.size());
    for (size_t i = 0; i < a.vec.size(); ++i)
    {
        vec.push_back(a.vec[i]); // Copy each digit from the source bigint
    }
}

/**
 * @brief Overloaded assignment operator for bigint.
 *
 * @param a The bigint to be assigned.
 * @return A reference to the current bigint.
 */
bigint &bigint::operator=(const bigint &a)
{

    bigint temp(a);
    vec.clear();
    is_Positive = temp.is_Positive; // Align the sign.

    for (size_t i = 0; i < temp.vec.size(); ++i)
    {
        vec.push_back(temp.vec[i]); // Copy each digit from the source bigint
    }
    trim();
    return *this;
}

/**
 * @brief Assigns an int64_t value to the bigint.
 *
 * @param a The 64-bit integer to be assigned.
 * @return A reference to the current bigint.
 */
bigint &bigint::operator=(const int64_t &a)
{
    bigint temp(a);
    *this = temp;
    trim();
    return *this;
}

/**
 * @brief Assigns a string value to this bigint.
 *
 * @param str The string which will be assigned to the bigint.
 * @return A reference to the current bigint.
 */
bigint &bigint::operator=(const std::string &str)
{
    if (str.empty())
    {
        throw std::invalid_argument("Input string is empty"); // std::invalid_argument If the string is empty
    }
    vec.clear();
    vec.reserve(str.length());
    size_t temp = 0;
    is_Positive = true;
    if (str[0] == '-')
    {
        is_Positive = false;
        temp = 1;
    }

    if (str.length() == temp)
    {
        throw std::invalid_argument("Input string is only '-' or empty"); // std::invalid_argument If the string is only '-'.
    }

    size_t i = str.length() - 1; // initialize i to start from last.
    // Extract each character from the string and store its value in vec
    while (i >= temp)
    {
        if (!std::isdigit(str[i]))
        {
            throw std::invalid_argument("Input string contains non-digit character"); // std::invalid_argument If the string contains any non-digit characters.
        }
        vec.push_back(static_cast<uint8_t>(str[i] - '0'));

        if (i == temp) // Avoid size_t underflow
        {
            break;
        }
        --i;
    }

    trim();
    return *this;
}

/**
 * @brief Returns the representation of the string of the bigint.
 *
 * @return A string representing the bigint.
 */
std::string bigint::get_value() const
{
    if (vec.empty())
    {
        throw std::invalid_argument("vec is empty, invalid for bigint."); // std::invalid_argument If the internal vector `vec` is empty.
    }
    std::string a;
    if (!is_Positive)
    {
        a = "-";
    }

    // find the first non-zero position
    size_t i = vec.size() - 1;
    while (i > 0 && vec[i] == 0)
    {
        --i;
    }

    // Append each digit from vec to the result string
    for (size_t j = i; j > 0; --j)
    {
        a += static_cast<char>('0' + static_cast<unsigned>(vec[j]));
    }
    a += static_cast<char>('0' + static_cast<unsigned>(vec[0])); // Add the last digit
    return a;
}

/**
 * @brief Checks if the bigint is positive.
 *
 * @return If the bigint is positive, then return true, otherwise return false.
 */
bool bigint::get_positive()
{
    return is_Positive;
}

/**
 * @brief Overloads the += operator for bigint addition.
 *
 * @param rhs is the bigint value to be added.
 * @return A reference to the current bigint.
 */
bigint &bigint::operator+=(const bigint &rhs)
{
    bigint copy_rhs(rhs); // Copy rhs to avoid self-addition issue.

    if (is_Positive == copy_rhs.is_Positive) // If it's an addition with the same sign
    {
        while (vec.size() <= copy_rhs.vec.size())
        {
            vec.push_back(0);
        }
        uint8_t temp = 0; // Carry for addition
        size_t i = 0;
        for (i = 0; i < copy_rhs.vec.size(); ++i)
        {
            vec.at(i) = static_cast<unsigned char>(vec.at(i) + temp + copy_rhs.vec.at(i));
            if (vec[i] >= 10)
            {
                temp = 1; // Go to the next position
                vec[i] = static_cast<unsigned char>(vec[i] - 10);
            }
            else
            {
                temp = 0;
            }
        }

        for (; i < vec.size(); ++i)
        {
            vec.at(i) = static_cast<unsigned char>(vec[i] + temp + 0);
            if (vec[i] >= 10)
            {
                temp = 1; // Go to the next position
                vec[i] -= 10;
            }
            else
                temp = 0;
        }
        if (temp > 0)
        {
            vec.push_back(temp); // Handle final carry
        }
    }
    else // else it's an addition with the different sign
    {
        if (is_Positive == true && copy_rhs.is_Positive == false)
        {
            bigint temp(copy_rhs);
            temp.is_Positive = true; // Make the rhs positive
            *this -= temp;
        }
        else
        {
            bigint temp(*this);
            temp.is_Positive = true; // Make the current bigint positive
            *this = copy_rhs - temp;
        }
    }
    trim(); // Remove leading zeros.
    return *this;
}

/**
 * @brief Overloads the + operator for bigint addition.
 *
 * @param lhs The first bigint.
 * @param rhs The second bigint.
 * @return The result of adding lhs and rhs.
 */
bigint operator+(const bigint &lhs, const bigint &rhs)
{
    bigint ret(lhs);
    ret += rhs; // Reuse the += operator.
    return ret;
}

/**
 * @brief Overloads the -= operator for bigint subtraction.
 *
 * @param rhs The bigint value to be subtracted.
 * @return A reference to the current bigin.
 */
bigint &bigint::operator-=(const bigint &rhs)
{

    if (!rhs.is_Positive) // If rhs is negative, perform addition
    {
        bigint temp(rhs);
        temp.is_Positive = true;
        *this += temp;
        return *this;
    }
    if (!is_Positive && rhs.is_Positive) // If rhs is positive and lhs is negative, perform addition
    {
        bigint temp(rhs);
        temp.is_Positive = false; // Convert rhs to negative
        *this += temp;            // Perform addition
        return *this;
    }
    bigint a;
    if (*this < rhs) // If current bigint is less than rhs, swap them
    {
        a = *this;
        *this = rhs;
        this->is_Positive = false;
    }
    else
    {
        a = rhs;
    }

    uint8_t temp = 0; // Borrow for subtraction
    size_t i = 0;
    // std::cout << *this << "-" << val2  << std::endl;
    for (i = 0; i < a.vec.size(); ++i)
    {
        if (vec[i] < temp + a.vec[i]) // Handle borrow
        {

            vec[i] = static_cast<unsigned char>(10 + vec[i] - (temp + a.vec[i]));
            temp = 1; // Set borrow for next position
        }
        else
        {
            vec[i] = static_cast<unsigned char>(vec[i] - temp - a.vec[i]);
            temp = 0;
        }
    }
    // Handle borrow for remaining digits
    for (; i < vec.size(); ++i)
    {
        if (vec[i] < temp)
        {
            vec[i] = static_cast<unsigned char>(10 + vec[i] - temp);
            temp = 1;
        }
        else
        {
            vec[i] = static_cast<unsigned char>(vec[i] - temp);
            temp = 0;
        }
    }
    // if(i < vec.size() && temp > 0){
    //     vec[i] = static_cast<unsigned char>( vec[i] - temp);
    // }
    trim();
    //    std::cout << " = " << *this << std::endl;
    return *this;
}

/**
 * @brief Overloads the - operator for bigint subtraction.
 *
 * @param lhs The first bigint.
 * @param rhs The subtrahend bigint.
 * @return The result of subtracting rhs from lhs.
 */
bigint operator-(const bigint &lhs, const bigint &rhs)
{

    bigint ret(lhs);
    ret -= rhs; // Reuse the -= operator.
    return ret;
}

/**
 * @brief Overloads the *= operator for bigint multiplication.
 *
 * @param rhs The bigint value to multiply.
 * @return A reference to the current bigint.
 */
bigint &bigint::operator*=(const bigint &rhs)
{
    bigint result;
    if (this->is_Positive == rhs.is_Positive)
        result.is_Positive = true;
    else
        result.is_Positive = false;

    std::vector<uint64_t> res_vec;
    res_vec.resize(this->vec.size() + rhs.vec.size());
    result.vec.resize(this->vec.size() + rhs.vec.size());

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

    // Check if there is an extra carry left
    if (temp > 0)
    {
        result.vec.push_back(static_cast<uint8_t>(temp % 10)); // Store the carry as a digit
    }

    result.trim();
    *this = result;
    return *this;
}

/**
 * @brief Overloads the * operator for bigint multiplication.
 *
 * @param lhs The first bigint(multiplicand).
 * @param rhs The second bigint(multiplier).
 * @return The result of multiplying lhs by rhs.
 */
bigint operator*(const bigint &lhs, const bigint &rhs)
{
    bigint ret(lhs);
    ret *= rhs; // Reuse *= operator.
    return ret;
}

/**
 * @brief Overloads the /= operator for bigint division.
 *
 * @param rhs The bigint divisor.
 * @return A reference to the current bigint.
 */
bigint &bigint::operator/=(const bigint &rhs)
{
    if (rhs == bigint::s_zero)
    {
        throw std::invalid_argument("Cannot divide by zero."); // std::invalid_argument if the division is 0.
    }
    if (*this == rhs) // If both values are equal, result is 1 or -1
    {
        *this = bigint::s_one;
        this->is_Positive = (is_Positive == rhs.is_Positive); // Ensure correct sign.
        return *this;
    }

    bigint ret(0); // Store the result
    bool sign_indicator = true;
    if (is_Positive == rhs.is_Positive)
    {
        sign_indicator = true;
    }
    else
    {
        sign_indicator = false;
    }

    bigint divider(rhs);
    bigint positive_val(rhs);
    positive_val.is_Positive = true;

    this->is_Positive = true;
    divider.is_Positive = true;

    if (*this < divider) // If the dividend is smaller than the divisor, the result is 0
    {
        *this = bigint::s_zero;
        return *this;
    }

    bigint cnt = 0; // Keeps track of the current power of 10
    while (*this > bigint::s_zero)
    {
        // std::cout << *this  << " " << divider  << " " << ret << std::endl;
        if (*this >= divider) // Subtract divider from current value.
        {
            *this -= divider;
            ret += pow(bigint::s_ten, bigint(cnt)); // Update the result with the power of 10
            divider *= bigint::s_ten;               // Increase the divider by a factor of 10.
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
        divider.is_Positive = true; // Make sure the divider is positive.
    }

    ret.trim();
    // std:: cout << "ret:" << ret << std::endl;
    ret.is_Positive = sign_indicator; // Align the correct sign to the result
    *this = ret;
    return *this;
}

/**
 * @brief Overloads the / operator for bigint division.
 *
 *
 * @param lhs The dividend bigint.
 * @param rhs The divisor bigint.
 * @return The quotient of dividing lhs by rhs.
 */
bigint operator/(const bigint &lhs, const bigint &rhs)
{
    bigint ret(lhs);
    ret /= rhs; // reuse /= operator.
    return ret;
}

/**
 * @brief Overloads the %= operator for bigint modulus.
 *
 * @param rhs The bigint divisor.
 * @return A reference to the current bigint object.
 */
bigint &bigint::operator%=(const bigint &rhs)
{

    if (rhs == bigint::s_zero)
    {
        throw std::invalid_argument("Cannot divide by zero."); // std::invalid_argument if division by zero
    }

    *this -= (*this / rhs) * rhs;                      // calculate the modulus.
    if (!this->is_Positive && *this != bigint::s_zero) // make sure the correct sign of result
    {
        this->is_Positive = false;
    }

    return *this;
}

/**
 * @brief Overloads the % operator for bigint modulus.
 *
 * @param lhs The dividend bigint.
 * @param rhs The divisor bigint.
 * @return The remainder of dividing lhs by rhs.
 */
bigint operator%(const bigint &lhs, const bigint &rhs)
{
    bigint ret(lhs);
    ret %= rhs; // reuse %= operator
    return ret;
}

/**
 * @brief Overloads the prefix ++ operator for bigint.
 * *
 * @return A reference to the incremented bigint.
 */
bigint &bigint::operator++()
{
    *this += bigint::s_one;
    return *this;
}

/**
 * @brief Overloads the prefix -- operator for bigint.
 *
 * @return A reference to the decremented bigint.
 */
bigint &bigint::operator--()
{
    *this -= bigint::s_one;
    return *this;
}

/**
 * @brief Overloads the postfix ++ operator for bigint.
 * *
 * @return The value of the bigint before the increment.
 */
const bigint bigint::operator++(int)
{
    bigint temp = *this;
    ++(*this);
    return bigint(temp);
}

/**
 * @brief Overloads the postfix -- operator for bigint.
 * *
 * @return The value of the bigint before the decrement.
 */
const bigint bigint::operator--(int)
{
    bigint temp = *this;
    --(*this);
    return bigint(temp);
}

/**
 * @brief Overloads the unary + operator for bigint.
 * *
 * @return A reference to the current bigint object.
 */
bigint &bigint::operator+()
{
    return *this;
}

/**
 * @brief Overloads the unary - operator for bigint.
 * *
 * @return A bigint with the opposite sign.
 */
bigint bigint::operator-() const
{
    bigint ret(*this);
    // Avoid bigint a('0') output '-0' error, tested by test.
    if (ret.vec.size() == 1 && ret.vec[0] == 0)
    {
        ret.is_Positive = true;
    }
    else
    {
        ret.is_Positive = !ret.is_Positive;
    }
    return ret;
}

/**
 * @brief Overloads the > operator for bigint.
 *
 * @param lhs The first bigint object.
 * @param rhs The second bigint object.
 * @return If lhs is greater than rhs, return true, otherwise false.
 */
bool operator>(const bigint &lhs, const bigint &rhs)
{
    if (lhs.is_Positive != rhs.is_Positive)
    {
        return lhs.is_Positive; // Positive numbers > negative numbers
    }

    if (lhs.is_Positive)
    {
        if (lhs.vec.size() > rhs.vec.size())
            return true; // The larger number of digits means greater
        else if (lhs.vec.size() < rhs.vec.size())
            return false;
    }
    else
    {
        if (lhs.vec.size() > rhs.vec.size())
            return false; // For negative numbers, more digits means smaller
        else if (lhs.vec.size() < rhs.vec.size())
            return true;
    }

    for (size_t i = lhs.vec.size(); i > 0;) // i-- > 0 ensures all indices from size()-1 to 0 are traversed
    {
        i--;
        if (lhs.vec[i] > rhs.vec[i])
            return lhs.is_Positive;
        else if (lhs.vec[i] < rhs.vec[i])
            return !lhs.is_Positive;
    }

    return false;
}

/**
 * @brief Overloads the == operator for bigint.
 *
 * @param lhs The first bigint object.
 * @param rhs The second bigint object.
 * @return If lhs is equal to rhs, return true, otherwise false.
 */
bool operator==(const bigint &lhs, const bigint &rhs)
{
    // Handle the test problem: if lhs and rhs are zero, keeping them in same sign.
    if (lhs.vec.size() == 1 && lhs.vec[0] == 0 && rhs.vec.size() == 1 && rhs.vec[0] == 0)
        return true;

    if (lhs.is_Positive != rhs.is_Positive || lhs.vec.size() != rhs.vec.size())
        return false; // different sign or size means they are not equal
    for (size_t i = 0; i < lhs.vec.size(); i++)
    {
        if (lhs.vec[i] != rhs.vec[i])
            return false; // If any digit differs, then not equal.
    }
    return true;
}

/**
 * @brief Overloads the >= operator for bigint.
 *
 * @param lhs The first bigint object.
 * @param rhs The second bigint object.
 * @return If lhs is greater than or equal to rhs, return true, otherwise false.
 */
bool operator>=(const bigint &lhs, const bigint &rhs)
{
    return (lhs > rhs) || (lhs == rhs); // convert to the > and == case.
}

/**
 * @brief Overloads the < operator for bigint.
 *
 * @param lhs The first bigint object.
 * @param rhs The second bigint object.
 * @return If lhs is less than rhs, return true, otherwise false.
 */
bool operator<(const bigint &lhs, const bigint &rhs)
{
    return !(lhs >= rhs); // convert to the !>= case.
}

/**
 * @brief Overloads the <= operator for bigint.
 *
 * @param lhs The first bigint object.
 * @param rhs The second bigint object.
 * @return If lhs is less than or equal to rhs, return true, otherwise false.
 */
bool operator<=(const bigint &lhs, const bigint &rhs)
{
    return !(lhs > rhs); // convert to the !> case.
}

/**
 * @brief Overloads the != operator for bigint.
 * *
 * @param lhs The first bigint object.
 * @param rhs The second bigint object.
 * @return If lhs is not equal to rhs, return true, otherwise false.
 */
bool operator!=(const bigint &lhs, const bigint &rhs)
{
    return !(lhs == rhs); // convert to the !== case.
}

/**
 * @brief Overloads the << operator for bigint output.
 *
 * @param out The output stream.
 * @param rhs A constant reference to the bigint object to be output.
 * @return A reference to the output stream.
 */
std::ostream &operator<<(std::ostream &out, const bigint &rhs)
{
    if (rhs.vec.empty() || (rhs.vec.size() == 1 && rhs.vec[0] == 0)) // Handle the bigint is 0
    {
        out << "0";
        return out;
    }

    if (!rhs.is_Positive)
    {
        out << '-';
    }

    for (size_t i = rhs.vec.size(); i-- > 0;)
    {
        out << static_cast<unsigned>(rhs.vec[i]); // Output each digit
    }

    return out;
}

/**
 * @brief Calculate the power of a bigint raised to a bigint exponent.
 *
 * @param base The base bigint.
 * @param exponent The exponent bigint.
 * @return The result of base raised to the power of exponent.
 */
bigint pow(const bigint &base, const bigint &exponent)
{
    if (!exponent.is_Positive) // Exponent must be non negative
    {
        throw std::invalid_argument("Negative exponent is not supported for bigint."); // std::invalid_argument If the exponent is negative.
    }

    if (exponent == bigint::s_zero) // Any number raised to the power of 0 is 1.
    {
        return bigint::s_one;
    }

    if (base == bigint::s_zero) // 0 raised to any power is 0
    {
        return bigint::s_zero;
    }

    bigint ret(bigint::s_one); // Result starts at 1
    bigint base2(base);        // Copy of the base
    bigint exp(exponent);      // Copy of the exponent

    while (exp > bigint::s_zero)
    {
        if (exp % bigint::s_two == bigint::s_one) // If the current exponent is odd
        {
            ret *= base2;
        }
        base2 *= base2;       // Square the base
        exp /= bigint::s_two; // Divide the exponent by 2
    }
    return ret;
}

/**
 * @brief Trims the leading zeros from the bigint vector.
 */
void bigint::trim()
{
    while (vec.size() > 1 && vec[vec.size() - 1] == 0) // Remove zeros.
    {
        vec.pop_back();
    }
    // If all the digits are 0, making vec to positive zero.
    if (vec.size() == 1 && vec[0] == 0)
    {
        is_Positive = true;
    }
}

#endif