#ifndef BIGINTEGER_H
#define BIGINTEGER_H

#include <QtWidgets>
#include <iostream>
#include <iomanip>
#include <string.h>
#include <sstream>
#pragma once

class CBigInteger{

public:
    CBigInteger();
    CBigInteger(std::string str);
    CBigInteger(int x);
    CBigInteger(unsigned int x);
    CBigInteger(long long x);
    CBigInteger(unsigned long long x);
    void set_number(std::string str);
    void shift_right();
    bool odd();
    bool even();
    void remove_leading_zeros();
    void divide_by_2();
    QString get_number() const;
    int log2() const;
   // operators
    CBigInteger operator +() const;
    CBigInteger operator -() const;
    friend std::ostream& operator <<(std::ostream& os, const CBigInteger& bi);
    friend bool operator == (const CBigInteger& left, const CBigInteger& right);
    friend bool operator < (const CBigInteger& left, const CBigInteger& right);
    friend bool operator !=(const CBigInteger& left, const CBigInteger& right);
    friend bool operator <=(const CBigInteger& left, const CBigInteger& right);
    friend bool operator > (const CBigInteger& left, const CBigInteger& right);
    friend bool operator >= (const CBigInteger& left, const CBigInteger& right);
    friend const CBigInteger operator +(CBigInteger left, const CBigInteger& right);
    friend const CBigInteger operator -(CBigInteger left, const CBigInteger& right);
    friend const CBigInteger operator *(const CBigInteger& left, const CBigInteger& right);
    friend const CBigInteger operator /(const CBigInteger& left, const CBigInteger& right);
    friend const CBigInteger operator %(const CBigInteger& left, const CBigInteger& right);
    CBigInteger operator +=(const CBigInteger &value);
    CBigInteger operator -=(const CBigInteger &value);
    CBigInteger operator *= (const CBigInteger &value);
    CBigInteger operator /= (const CBigInteger &value);
    CBigInteger operator %= (const CBigInteger &value);
    CBigInteger operator ++();
    CBigInteger operator ++(int);
    CBigInteger operator --();
    CBigInteger operator --(int);

private:
    static const int BASE = 1000000000;
    std::vector <int> numbers;
    bool isNegative;
};

#endif // BIGINTEGER_H
