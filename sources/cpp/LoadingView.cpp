#include "LoadingView.h"

CLoadingView::CLoadingView(QWidget *parent) : QFrame(parent){
    mainBox = new QVBoxLayout();
    lbGif = new QLabel();
    gifAnimation = new QMovie(":/gifs/appGraphic/loading.gif");
    lbGif->setMovie(gifAnimation);
    lbGif->raise();
    mainBox->addWidget(lbGif);
    gifAnimation->start();
    this->setLayout(mainBox);
    this->resize(500,450);
    this->setWindowTitle("Идёт генерация, пожалуйста подождите...");
    this->setGeometry(QStyle::alignedRect(Qt::LeftToRight,Qt::AlignCenter,this->size(),QApplication::desktop()->availableGeometry()));
    this->setWindowIcon(QIcon(":/icons/appGraphic/loading.ico"));
}

CLoadingView::~CLoadingView(){
    gifAnimation->stop();
}
