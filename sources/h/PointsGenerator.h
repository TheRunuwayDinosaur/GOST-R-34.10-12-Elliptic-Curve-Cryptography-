#ifndef POINTSGENERATOR_H
#define POINTSGENERATOR_H

#include <QObject>
#include <QtWidgets>
#include "MathWorker.h"
#pragma once

class CMathWorker;
class CPointsGenerator{

public:
    CPointsGenerator();
    ~CPointsGenerator();
    CBigInteger calc_points(const CBigInteger &p, const CBigInteger &A,const CBigInteger&B,
                            const CBigInteger &l,const CBigInteger &r);

private:
    CMathWorker *mathWorker;

};

#endif // POINTSGENERATOR_H
