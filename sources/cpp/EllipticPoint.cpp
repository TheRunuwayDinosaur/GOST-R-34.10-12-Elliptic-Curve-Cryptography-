#include "EllipticPoint.h"

CEllipticPoint::CEllipticPoint(CBigInteger x_,CBigInteger y_){
    this->x = x_,this->y = y_;
}

void CEllipticPoint::set_A(const CBigInteger &A_){
    this->A = A_;
}

void CEllipticPoint::set_B(const CBigInteger &B_){
    this->B = B_;
}

void CEllipticPoint::set_p(const CBigInteger &p_){
    this->p = p_;
}

CBigInteger CEllipticPoint::get_x() const{
    return this->x;
}

CBigInteger CEllipticPoint::get_y() const{
    return this->y;
}

CBigInteger CEllipticPoint::get_A() const{
    return this->A;
}

CBigInteger CEllipticPoint::get_B() const{
    return this->B;
}

CBigInteger CEllipticPoint::get_p() const{
    return this->p;
}

void CEllipticPoint::write_point() const{
    qDebug() << this->x.get_number() << ' ' << this->y.get_number();
}

bool CEllipticPoint::is_inf() const{
    return this->x == 0 && this->y == 0;
}

CEllipticPoint CEllipticPoint::operator +=(const CEllipticPoint &right){
    return *this = *this + right;
}

CEllipticPoint CEllipticPoint::operator *=(const CBigInteger &x){
    return *this = *this * x;
}
