#ifndef KEYSVIEW_H
#define KEYSVIEW_H

#include <QObject>
#include <QtWidgets>
#include <QtConcurrent>
#include "BigInteger.h"
#include "EllipticPoint.h"
#include "MathWorker.h"
#include "PrimesGenThread.h"
#include "LoadingView.h"
#include "OpenKeys.h"
#include "CloseKeys.h"
#include "KeysGenThread.h"
#pragma once

class CKeysView : public QFrame{
    Q_OBJECT

public:
    CKeysView(QWidget *parent = 0);
    ~CKeysView();
    CCloseKeys get_close_keys() const;
    CBigInteger get_p() const;
    CBigInteger get_q() const;
    CEllipticPoint get_ellipticP() const;
    CEllipticPoint get_ellipticQ() const;
    CBigInteger get_d() const;

private:
   // v,h boxes
    QVBoxLayout *mainBox;
    QHBoxLayout *buttonsBox;
   // form layouts
    QFormLayout *formBox;
   // labels
    QLabel *lbP;
    QLabel *lbQ;
    QLabel *lbA;
    QLabel *lbB;
    QLabel *lbEllipticP;
    QLabel *lbEllipticQ;
   // line/text edits
    QTextEdit *leP;
    QTextEdit *leQ;
    QTextEdit *leA;
    QTextEdit *leB;
    QTextEdit *leEllipticP;
    QTextEdit *leEllipticQ;
   // buttons, spin boxes...
    QPushButton *pbGenerateKeys;
    QPushButton *pbPublishKeys;
   // other
   //
    CBigInteger p;
    CBigInteger q;
    CBigInteger A;
    CBigInteger B;
    CEllipticPoint ellipticP;
    CEllipticPoint ellipticQ;
    CBigInteger d;
   //
    QVector <CPrimesGeneratorThread*> ths;
    QVector <CBigInteger> bigPrimes;
    CLoadingView *loadingView;
    CKeysGenThread *keysGenerator;
   //
    CMathWorker *mathWorker;
    const int needPrimes = 1;
   // methods
    void generate_primes(int cnt);
    void generate_all_keys();

private slots:
    void on_prime_generated(QString prime);
    void on_pbGenerateKeys_clicked();
    void on_pbPublishKeys_clicked();
    void on_keys_generated(QString p,QString A,QString B,QString q);

signals:
    void publish_keys_to_user(COpenKeys userOpenKeys);
    void close_keys_generated();

};

#endif // KEYSVIEW_H
