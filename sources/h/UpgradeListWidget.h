#ifndef UPGRADELISTWIDGET_H
#define UPGRADELISTWIDGET_H

#include <QObject>
#include <QtWidgets>
#pragma once

class CUpgradeListWidget : public QListWidget{
    Q_OBJECT

public:
    CUpgradeListWidget(QWidget *parent = 0);

private slots:
    void mousePressEvent(QMouseEvent *e);

signals:
    void rightButtonClicked(int X,int Y);

};

#endif // UPGRADELISTWIDGET_H
