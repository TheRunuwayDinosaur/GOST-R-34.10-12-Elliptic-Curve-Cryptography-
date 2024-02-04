#ifndef OPENKEYS_H
#define OPENKEYS_H

#include <QObject>
#include "BigInteger.h"
#include "EllipticPoint.h"
#pragma once

class COpenKeys{

public:
    COpenKeys(CBigInteger q_ = 1,
              CEllipticPoint ellipticP_ = {},
              CEllipticPoint ellipticQ_ = {});
    void set_q(const CBigInteger &q_);
    void set_ellipticP(const CEllipticPoint &ellipticP_);
    void set_ellipticQ(const CEllipticPoint &ellipticQ_);
    CBigInteger get_q() const;
    CBigInteger get_A() const;
    CBigInteger get_B() const;
    CEllipticPoint get_ellipticP() const;
    CEllipticPoint get_ellipticQ() const;
    void operator=(const COpenKeys &copy);

private:
    CBigInteger q;
    const CBigInteger A = 2;
    const CBigInteger B = 6;
    CEllipticPoint ellipticP;
    CEllipticPoint ellipticQ;

};

#endif // OPENKEYS_H
