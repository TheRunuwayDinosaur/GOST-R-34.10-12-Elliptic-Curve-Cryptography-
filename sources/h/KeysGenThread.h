#ifndef KEYSGENTHREAD_H
#define KEYSGENTHREAD_H

#include <QObject>
#include <QtWidgets>
#include "KeysGenerator.h"

class CKeysGenThread : public QThread{
    Q_OBJECT

public:
    CKeysGenThread();
    ~CKeysGenThread();

private:
    CKeysGenerator *keysGenerator;

protected:
    void run();

signals:
    void keys_generated(QString p,QString A,QString B,QString q);

};

#endif // KEYSGENTHREAD_H
