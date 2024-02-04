#include "UpgradeListWidget.h"

CUpgradeListWidget::CUpgradeListWidget(QWidget *parent) : QListWidget(parent){

}

void CUpgradeListWidget::mousePressEvent(QMouseEvent *e){
    QListWidget::mousePressEvent(e);
    if (e->button() == Qt::RightButton) emit rightButtonClicked(e->globalX(),e->globalY());
}
