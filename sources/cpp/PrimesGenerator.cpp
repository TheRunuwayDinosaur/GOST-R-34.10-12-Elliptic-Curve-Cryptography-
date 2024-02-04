#include "PrimesGenerator.h"

CPrimesGenerator::CPrimesGenerator(){
    int n = 100000;
    QVector <bool> isPrime(n + 1,true);
    isPrime[0] = isPrime[1] = false;
    for (int i = 2;i <= n;i++){
        if (!isPrime[i] || i == 3) continue;
        for (int j = 2 * i;j <= n;j += i){
            isPrime[j] = false;
        }
    }
    for (int i = 2;i <= n;i++){
        if (!isPrime[i]) continue;
        startPrimes.push_back(i);
    }
}

CBigInteger CPrimesGenerator::generate_p() const{
   // 3 * 7 * 2 + 1 = 43 - простое
    std::vector <CBigInteger> ost1,ost2;
    for (auto& p : startPrimes){
        if (p % 3 == 1) ost1.push_back(p);
        else if (p % 3 == 2) ost2.push_back(p);
    }
    int maxLog = 0;
    std::uniform_int_distribution<int> dist1((int)0, (int)ost1.size() - 1);
    static std::mt19937 gen1(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    CBigInteger two = 2;
    while(maxLog < number_size){
        std::vector <CBigInteger> newPrimes;
        int cntIterations = 35;
        for (int i = 0;i < cntIterations;i++){
            std::uniform_int_distribution<int> dist2((int)0, (int)ost2.size() - 1);
            CBigInteger newNumber = ost1[dist1(gen1)] * ost2[dist2(gen1)] * 2 + 1;
            if (!mathWorker.check_prime(newNumber)) continue;
            newPrimes.push_back(newNumber);
            maxLog = std::max(maxLog,newNumber.log2());
        }
        if (newPrimes.size() > 0){
            std::sort(newPrimes.begin(),newPrimes.end());
            newPrimes.erase(std::unique(newPrimes.begin(),newPrimes.end()),newPrimes.end());
            ost2 = std::move(newPrimes);
        }
    }
    CBigInteger result;
    for (auto& p : ost2){
        if (p.log2() == maxLog){
            result = p; break;
        }
    }
    return result;
}
