#include "KeysGenerator.h"

CKeysGenerator::CKeysGenerator(){
    mathWorker = new CMathWorker();
    int n = 20000;
    QVector <bool> isPrimes(n + 1,true);
    isPrimes[0] = isPrimes[1] = false;
    for (int i = 2;i <= n;i++){
        if (!isPrimes[i]) continue;
        for (int j = 2 * i;j <= n;j += i) isPrimes[j] = false;
    }
    for (int i = 2;i <= n;i++){
        if (!isPrimes[i]) continue;
        primes.push_back(i);
    }
}

CKeysGenerator::~CKeysGenerator(){
    delete mathWorker;
}

CCloseKeys CKeysGenerator::generate_keys(){
    CCloseKeys keys;
    while(true){
        CBigInteger p = primes[mathWorker->generate_random_number(1,primes.size() - 1).get_number().toInt()];
        std::pair <CBigInteger,CBigInteger> ellipticCurveParams = mathWorker->generate_elliptic_params(p);
        CBigInteger A = ellipticCurveParams.first;
        CBigInteger B = ellipticCurveParams.second;
        CBigInteger pointCount = mathWorker->cnt_points_on_elliptic_curve(p,A,B);
        if (mathWorker->check_prime(pointCount)){
            CEllipticPoint basePoint = mathWorker->generate_elliptic_point(p,A,B);
            basePoint.set_p(p); basePoint.set_A(A); basePoint.set_B(B);
            CEllipticPoint infPoint = basePoint * pointCount;
            if (!infPoint.is_inf() || pointCount == p) continue;
            keys.set_p(p); keys.set_A(A); keys.set_B(B); keys.set_q(pointCount);
            return keys;
        }
    }
    return keys;
}
