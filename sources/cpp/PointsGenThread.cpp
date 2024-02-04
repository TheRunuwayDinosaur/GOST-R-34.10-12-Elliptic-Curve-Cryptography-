#include "PointsGenThread.h"

CPointsGenThread::CPointsGenThread(){
    pointsGenerator = new CPointsGenerator();
}

CPointsGenThread::~CPointsGenThread(){
    delete pointsGenerator;
}

void CPointsGenThread::set_p(const CBigInteger &p){
    this->p = p;
}

void CPointsGenThread::set_A(const CBigInteger &A){
    this->A = A;
}

void CPointsGenThread::set_B(const CBigInteger &B){
    this->B = B;
}

void CPointsGenThread::set_l(const CBigInteger &l){
    this->l = l;
}

void CPointsGenThread::set_r(const CBigInteger &r){
    this->r = r;
}

CBigInteger CPointsGenThread::get_points() const{
    return this->pointsCount;
}

void CPointsGenThread::run(){
    pointsCount = pointsGenerator->calc_points(p,A,B,l,r);
}
