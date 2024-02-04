#ifndef PRIMESGENERATOR_H
#define PRIMESGENERATOR_H

#include <QObject>
#include <QtWidgets>
#include <BigInteger.h>
#include <MathWorker.h>
#include <random>
#include <deque>

#define number_size 8

class CPrimesGenerator{

public:
    CPrimesGenerator();
    CBigInteger generate_p() const;

private:
    QVector <CBigInteger> startPrimes;
    CMathWorker mathWorker;

};

#endif // PRIMESGENERATOR_H
