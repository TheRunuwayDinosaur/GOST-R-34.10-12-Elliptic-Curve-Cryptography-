#ifndef POINTSGENTHREAD_H
#define POINTSGENTHREAD_H

#include <QObject>
#include <QtWidgets>
#include "PointsGenerator.h"
#pragma once

class CPointsGenerator;
class CPointsGenThread : public QThread{

public:
    CPointsGenThread();
    ~CPointsGenThread();
    void set_p(const CBigInteger &p);
    void set_A(const CBigInteger &A);
    void set_B(const CBigInteger &B);
    void set_l(const CBigInteger &l);
    void set_r(const CBigInteger &r);
    CBigInteger get_points() const;

private:
    CPointsGenerator *pointsGenerator;
    CBigInteger p;
    CBigInteger A;
    CBigInteger B;
    CBigInteger l;
    CBigInteger r;
    CBigInteger pointsCount;

protected:
    void run();

};

#endif // POINTSGENTHREAD_H
