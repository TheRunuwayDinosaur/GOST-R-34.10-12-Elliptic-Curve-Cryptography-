#ifndef STREEBOGMAIN_H
#define STREEBOGMAIN_H

#include <QObject>
#include <QtWidgets>
#include "StreebogCalc.h"
#include "StreebogTests.h"

#define DEFAULT_HASH_SIZE 256

class CStreebogMain : public QObject{
    Q_OBJECT

public:
    CStreebogMain(QObject *parent = 0);
    ~CStreebogMain();
    QString get_hash_from_string(const QString &message) const;

private:
    TGOSTHashContext *CTX;

};

#endif // STREEBOGMAIN_H
