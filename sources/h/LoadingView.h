#ifndef LOADINGVIEW_H
#define LOADINGVIEW_H

#include <QObject>
#include <QtWidgets>
#pragma once

class CLoadingView : public QFrame{
    Q_OBJECT

public:
    CLoadingView(QWidget *parent = 0);
    ~CLoadingView();

private:
   // v,h boxes
    QVBoxLayout *mainBox;
   // labels
    QLabel *lbGif;
   // movies
    QMovie *gifAnimation;

};

#endif // LOADINGVIEW_H
