#ifndef ELLIPTICPOINTH_H
#define ELLIPTICPOINTH_H

#include <QObject>
#include <QtWidgets>
#include "BigInteger.h"

class CEllipticPoint{

public:
    CEllipticPoint(CBigInteger x_ = -1,CBigInteger y_ = -1);
    void set_A(const CBigInteger &A_);
    void set_B(const CBigInteger &B_);
    void set_p(const CBigInteger &p_);
    CBigInteger get_x() const;
    CBigInteger get_y() const;
    CBigInteger get_A() const;
    CBigInteger get_B() const;
    CBigInteger get_p() const;
    void write_point() const;
    bool is_inf() const;
    friend const CEllipticPoint operator +(const CEllipticPoint &left,const CEllipticPoint &right);
    friend const CEllipticPoint operator *(CEllipticPoint point,CBigInteger x);
    friend const CBigInteger operator &(const CEllipticPoint &left,const CEllipticPoint &right); // calc lambda
    CEllipticPoint operator +=(const CEllipticPoint &right);
    CEllipticPoint operator *=(const CBigInteger &x);

private:
    CBigInteger x;
    CBigInteger y;
    CBigInteger p;
    CBigInteger q;
    CBigInteger A;
    CBigInteger B;
};

#endif // ELLIPTICPOINTH_H
