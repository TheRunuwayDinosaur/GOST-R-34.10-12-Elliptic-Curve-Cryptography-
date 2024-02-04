#include "OpenKeys.h"

COpenKeys::COpenKeys(CBigInteger q_,
           CEllipticPoint ellipticP_, CEllipticPoint ellipticQ_){
    this->q = q_;
    this->ellipticP = ellipticP_;
    this->ellipticQ = ellipticQ_;
}

void COpenKeys::set_q(const CBigInteger &q_){
    this->q = q_;
}

void COpenKeys::set_ellipticP(const CEllipticPoint &ellipticP_){
    this->ellipticP = ellipticP_;
}

void COpenKeys::set_ellipticQ(const CEllipticPoint &ellipticQ_){
    this->ellipticQ = ellipticQ_;
}

CBigInteger COpenKeys::get_q() const{
    return this->q;
}

CBigInteger COpenKeys::get_A() const{
    return this->A;
}

CBigInteger COpenKeys::get_B() const{
    return this->B;
}

CEllipticPoint COpenKeys::get_ellipticP() const{
    return this->ellipticP;
}

CEllipticPoint COpenKeys::get_ellipticQ() const{
    return this->ellipticQ;
}

void COpenKeys::operator=(const COpenKeys &copy){
    this->q = copy.q;
    this->ellipticP = copy.ellipticP;
    this->ellipticQ = copy.ellipticQ;
}
