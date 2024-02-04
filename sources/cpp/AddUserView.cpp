#include "AddUserView.h"

CAddUserView::CAddUserView(QWidget *parent) : QFrame(parent){
    mainBox = new QVBoxLayout();
    buttonsBox = new QHBoxLayout();
    lbUserName = new QLabel("Введите имя пользователя (1-50 символов): ");
    lbUserName->setFont(QFont("Times",10));
    lbUserName->setStyleSheet("font: bold;"
                              "color: purple;");
    leUserName = new QTextEdit();
    leUserName->setFont(QFont("Times",10));
    pbAdd = new QPushButton("Добавить");
    pbAdd->setStyleSheet("QPushButton{"
                                 "border:none;"
                                 "color: white;"
                                 "font: bold;"
                                 "background-color: QLinearGradient(x1: 1, y1: 0, x2: 0, y2: 1,stop: 0 #00FA9A,stop: 0.4999 #00FA9A,stop: 0.5 #00FA9A,stop: 1 #238);"
                                 "border-radius: 15px;}"
                                 "QPushButton:hover{"
                                 "background-color: QLinearGradient(x1: 1, y1: 0, x2: 0, y2: 1,stop: 0 #87CEFA,stop: 0.4999 #BA55D3,stop: 0.5 #BA55D3,stop: 1 #238);}"
                                 "QPushButton:pressed{"
                                 "background-color: QLinearGradient(x1: 1, y1: 0, x2: 0, y2: 1,stop: 0 #DA70D6,stop: 0.4999 #FFF0F5,stop: 0.5 #FFF0F5,stop: 1 #238);}");
    pbAdd->setFixedSize(250,50);
    pbAdd->setFont(QFont("Times",9));
    mainBox->addWidget(lbUserName);
    mainBox->addWidget(leUserName);
    buttonsBox->setAlignment(Qt::AlignRight);
    buttonsBox->addWidget(pbAdd);
    mainBox->addLayout(buttonsBox);
    this->setLayout(mainBox);
    this->setFont(QFont("Times",10));
    this->setFixedSize(450,300);
    this->setGeometry(QStyle::alignedRect(Qt::LeftToRight,Qt::AlignCenter,this->size(),QApplication::desktop()->availableGeometry()));
    this->setWindowTitle("Добавление нового пользователя");
    this->setWindowIcon(QIcon(":/icons/appGraphic/add.ico"));
   // connects
    connect(pbAdd,SIGNAL(clicked()),SLOT(on_pbAdd_clicked()));
   // other
    wasSendSignal = false;
}

void CAddUserView::set_users(CMessengerModel *messModel_){
    this->messModel = messModel_;
}

void CAddUserView::closeEvent(QCloseEvent *e){
    Q_UNUSED(e);
    if (!wasSendSignal) emit add_user("");
}

void CAddUserView::on_pbAdd_clicked(){
    QString userName = leUserName->toPlainText();
    if (userName.size() == 0) QMessageBox::critical(this,"Ошибка","Имя пользователя не может быть пустым!");
    else if (userName.size() > 50) QMessageBox::critical(this,"Ошибка","Имя пользователя длиннее 50 символов!");
    else{
        bool wasName = false;
        for (int user = 0;user < messModel->size();user++){
            CUserView *curUser = messModel->get_user(user);
            if (curUser->get_name() == userName){
                wasName = true; break;
            }
        }
        if (!wasName){
            wasSendSignal = true;
            emit add_user(userName);
        }
        else QMessageBox::critical(this,"Ошибка","Такое имя пользователя уже занято, используйте другое!");
    }
}
