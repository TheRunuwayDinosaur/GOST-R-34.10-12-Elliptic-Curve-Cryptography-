#include <QApplication>
#include "MainView.h"

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    CMainView window;
    window.show();
    return a.exec();
}
