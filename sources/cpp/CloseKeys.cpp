#include "CloseKeys.h"

CCloseKeys::CCloseKeys(CBigInteger p_, CBigInteger q_, CEllipticPoint ellipticP_, CEllipticPoint ellipticQ_, CBigInteger d_){
    this->p = p_,this->q = q_;
    this->ellipticP = ellipticP_,this->ellipticQ = ellipticQ_;
    this->d = d_;
}

void CCloseKeys::set_p(const CBigInteger &p_){
    this->p = p_;
}

void CCloseKeys::set_A(const CBigInteger &A_){
    this->A = A_;
}

void CCloseKeys::set_B(const CBigInteger &B_){
    this->B = B_;
}

void CCloseKeys::set_q(const CBigInteger &q_){
    this->q = q_;
}

void CCloseKeys::set_ellipticP(const CEllipticPoint &ellipticP_){
    this->ellipticP = ellipticP_;
}

void CCloseKeys::set_ellipticQ(const CEllipticPoint &ellipticQ_){
    this->ellipticQ = ellipticQ_;
}

void CCloseKeys::set_d(const CBigInteger &d_){
    this->d = d_;
}

CBigInteger CCloseKeys::get_p() const{
    return this->p;
}

CBigInteger CCloseKeys::get_A() const{
    return this->A;
}

CBigInteger CCloseKeys::get_B() const{
    return this->B;
}

CBigInteger CCloseKeys::get_q() const{
    return this->q;
}

CEllipticPoint CCloseKeys::get_ellipticP() const{
    return this->ellipticP;
}

CEllipticPoint CCloseKeys::get_ellipticQ() const{
        return this->ellipticQ;
}

CBigInteger CCloseKeys::get_d() const{
    return this->d;
}

void CCloseKeys::operator=(const CCloseKeys &copy){
    this->p = copy.p;
    this->q = copy.q;
    this->ellipticP = copy.ellipticP;
    this->ellipticQ = copy.ellipticQ;
    this->d = copy.d;
}
