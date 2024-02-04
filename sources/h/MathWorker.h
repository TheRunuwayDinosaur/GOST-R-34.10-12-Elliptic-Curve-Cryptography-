#ifndef MATHWORKER_H
#define MATHWORKER_H

#include "BigInteger.h"
#include "EllipticPoint.h"
#include "CloseKeys.h"
#include "OpenKeys.h"
#include "PointsGenThread.h"
#pragma once

class CMathWorker{

public:
    CMathWorker();
    CBigInteger pow(const CBigInteger &a,CBigInteger p) const;
    CBigInteger bin_pow(const CBigInteger &a,CBigInteger p,const CBigInteger &mod) const;
    CBigInteger inverse_element(const CBigInteger &a,const CBigInteger &m) const;
    CBigInteger gcd(CBigInteger a,CBigInteger b) const;
    bool check_prime(CBigInteger &value) const;
    CBigInteger add_mod(const CBigInteger &a,const CBigInteger &b,const CBigInteger &mod) const;
    CBigInteger sub_mod(const CBigInteger &a,const CBigInteger &b,const CBigInteger &mod) const;
    CBigInteger mul_mod(const CBigInteger &a,const CBigInteger &b,const CBigInteger &mod) const;
    CBigInteger div_mod(const CBigInteger &a,const CBigInteger &b,const CBigInteger &mod) const;
    std::pair <CBigInteger,CBigInteger> generate_elliptic_params(const CBigInteger &p) const;
    CEllipticPoint generate_elliptic_point(const CBigInteger &p,const CBigInteger &A,const CBigInteger &B) const;
    CBigInteger generate_random_number(int64_t from, int64_t to) const;
    std::pair <CBigInteger,CBigInteger> generate_digital_signature(const CCloseKeys &closeKeys,const QString &hash) const;
    bool check_digital_signature(const std::pair <CBigInteger,CBigInteger> &digitalSignature,
                                 const COpenKeys &openKeys,const QString &hash) const;
    CBigInteger hex_to_big_integer(const QString &hex) const;
    CBigInteger sqrt(const CBigInteger &value) const;
    CBigInteger sqrt4(const CBigInteger &value) const;
    std::pair <CBigInteger,CEllipticPoint> find_cyclic_group(const CBigInteger &p,const CBigInteger &A,const CBigInteger &B) const;
    CBigInteger cnt_points_on_elliptic_curve(const CBigInteger &p,const CBigInteger &A,const CBigInteger &B) const;

private:
    QVector <int> primesForDelTest;
    bool ferm_test(CBigInteger value) const;
    bool del_test(CBigInteger value) const;
    QMap <QChar,CBigInteger> hexValue;
};

#endif // MATHWORKER_H
