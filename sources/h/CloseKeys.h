#ifndef CLOSEKEYS_H
#define CLOSEKEYS_H

#include <QtWidgets>
#include "BigInteger.h"
#include "EllipticPoint.h"
#pragma once

class CCloseKeys{

public:
    CCloseKeys(CBigInteger p_ = -1,CBigInteger q_ = -1,
              CEllipticPoint ellipticP_ = {},CEllipticPoint ellipticQ_ = {},
              CBigInteger d_ = -1);
    void set_p(const CBigInteger &p_);
    void set_A(const CBigInteger &A_);
    void set_B(const CBigInteger &B_);
    void set_q(const CBigInteger &q_);
    void set_ellipticP(const CEllipticPoint &ellipticP_);
    void set_ellipticQ(const CEllipticPoint &ellipticQ_);
    void set_d(const CBigInteger &d_);
    CBigInteger get_p() const;
    CBigInteger get_A() const;
    CBigInteger get_B() const;
    CBigInteger get_q() const;
    CEllipticPoint get_ellipticP() const;
    CEllipticPoint get_ellipticQ() const;
    CBigInteger get_d() const;
    void operator=(const CCloseKeys &copy);

private:
    CBigInteger p;
    CBigInteger q;
    CBigInteger A;
    CBigInteger B;
    CEllipticPoint ellipticP;
    CEllipticPoint ellipticQ;
    CBigInteger d;

};

#endif // CLOSEKEYS_H
