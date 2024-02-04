#ifndef PRIMESGENTHREAD_H
#define PRIMESGENTHREAD_H

#include <QThread>
#include "PrimesGenerator.h"
#include "BigInteger.h"
#pragma once

class CPrimesGeneratorThread : public QThread{
    Q_OBJECT

public:
    CPrimesGeneratorThread();
    ~CPrimesGeneratorThread();

private:
    CPrimesGenerator *generator;

protected:
    void run();

signals:
    void prime_generated(QString prime);

};

#endif // PRIMESGENTHREAD_H
