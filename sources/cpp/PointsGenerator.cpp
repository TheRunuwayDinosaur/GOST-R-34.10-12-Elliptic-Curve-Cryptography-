#include "PointsGenerator.h"

CPointsGenerator::CPointsGenerator(){
    mathWorker = new CMathWorker();
}

CPointsGenerator::~CPointsGenerator(){
    delete mathWorker;
}

CBigInteger CPointsGenerator::calc_points(const CBigInteger &p, const CBigInteger &A, const CBigInteger &B, const CBigInteger &l, const CBigInteger &r){
    CBigInteger cnt = 0;
    for (CBigInteger x = l;x < r;x++){
        CBigInteger xValue = mathWorker->add_mod((mathWorker->add_mod(mathWorker->bin_pow(x,3,p),
                                           mathWorker->mul_mod(A,x,p),
                                           p)),
                                           B,
                                           p);
        if (mathWorker->bin_pow(xValue,(p - 1) / 2,p) != 1){
            if (mathWorker->bin_pow(xValue,(p - 1) / 2,p) == 0){
                cnt++;
            }
            continue;
        }
        cnt += 2;
    }
    return cnt;
}
