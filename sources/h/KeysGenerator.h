#ifndef KEYSGENERATOR_H
#define KEYSGENERATOR_H

#include <QObject>
#include <QtWidgets>
#include "MathWorker.h"
#pragma once

class CKeysGenerator{

public:
    CKeysGenerator();
    ~CKeysGenerator();
    CCloseKeys generate_keys();

private:
    CMathWorker *mathWorker;
    QVector <CBigInteger> primes;
};

#endif // KEYSGENERATOR_H
