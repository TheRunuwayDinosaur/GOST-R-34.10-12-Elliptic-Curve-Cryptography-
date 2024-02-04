#include "ChatWithUserView.h"

CChatWithUserView::CChatWithUserView(const QString &userNameFrom, QWidget *parent) : QFrame(parent){
    hashFunction = new CStreebogMain(this);
    mathWorker = new CMathWorker();
    mainBox = new QVBoxLayout();
    gbMessagesLayout = new QVBoxLayout();
    buttonsBox = new QHBoxLayout();
    gbMessages = new QGroupBox("Чат с ");
    gbMessages->setStyleSheet("QGroupBox{"
                           "font: bold;"
                           "color: purple;"
                           "border: 1px solid silver;"
                           "border-radius: 30px;"
                           "margin-top: 6px; }"
                           "QGroupBox::title{"
                           "subcontrol-origin: margin;"
                           "left: 7px;"
                           "padding: 0px 5px 0px 5px;}");
    gbMessages->setFont(QFont("Times",10));
    lbMessage = new QLabel("Ваше сообщение: ");
    lbMessage->setFont(QFont("Times",10));
    lbMessage->setStyleSheet("font: bold");
    lbHash = new QLabel("Хеш-сумма последнего отправленного сообщения: ");
    lbHash->setFont(QFont("Times",10));
    lbHash->setStyleSheet("font: bold");
    teMessage = new QTextEdit();
    teMessage->setFont(QFont("Times",10));
    teMessage->setFixedHeight(150);
    teHash = new QTextEdit();
    teHash->setFont(QFont("Times",10));
    teHash->setFixedHeight(90);
    teHash->setStyleSheet("color: red; font: bold");
    teHash->setEnabled(false);
    pbSendMessage = new QPushButton("Отправить сообщение");
    pbSendMessage->setStyleSheet("QPushButton{"
                                 "border:none;"
                                 "color: white;"
                                 "font: bold;"
                                 "background-color: QLinearGradient(x1: 1, y1: 0, x2: 0, y2: 1,stop: 0 #00FA9A,stop: 0.4999 #00FA9A,stop: 0.5 #00FA9A,stop: 1 #238);"
                                 "border-radius: 15px}"
                                 "QPushButton:hover{"
                                 "background-color: QLinearGradient(x1: 1, y1: 0, x2: 0, y2: 1,stop: 0 #87CEFA,stop: 0.4999 #BA55D3,stop: 0.5 #BA55D3,stop: 1 #238);}"
                                 "QPushButton:pressed{"
                                 "background-color: QLinearGradient(x1: 1, y1: 0, x2: 0, y2: 1,stop: 0 #DA70D6,stop: 0.4999 #FFF0F5,stop: 0.5 #FFF0F5,stop: 1 #238);}");
    pbSendMessage->setFixedSize(250,50);
    pbSendMessage->setFont(QFont("Times",10));
    messagesList = new CUpgradeListWidget(this);
    messagesList->setStyleSheet("QListView{"
                             "color: green; font: bold}");
    messagesList->setFont(QFont("Times",10));
    menu = new QMenu();
    actionCheckHash = new QAction("Посмотреть хеш-сумму сообщения");
    actionCheckHash->setFont(QFont("Times",10));
    actionCheckDigitalSignature = new QAction("Проверить цифровую подпись");
    actionCheckDigitalSignature->setFont(QFont("Times",10));
    menu->addAction(actionCheckHash);
    menu->addAction(actionCheckDigitalSignature);
    gbMessagesLayout->addWidget(messagesList);
    gbMessagesLayout->addWidget(lbMessage);
    gbMessagesLayout->addWidget(teMessage);
    gbMessagesLayout->addWidget(lbHash);
    gbMessagesLayout->addWidget(teHash);
    gbMessages->setLayout(gbMessagesLayout);
    buttonsBox->setAlignment(Qt::AlignRight);
    buttonsBox->addWidget(pbSendMessage);
    mainBox->addWidget(gbMessages);
    mainBox->addLayout(buttonsBox);
    this->setLayout(mainBox);
    this->setFont(QFont("Times",10));
    this->resize(700,850);
    this->setGeometry(QStyle::alignedRect(Qt::LeftToRight,Qt::AlignCenter,this->size(),QApplication::desktop()->availableGeometry()));
    this->setWindowTitle(QString("Пользователь: %1").arg(userNameFrom));
    this->setWindowIcon(QIcon(":/icons/appGraphic/messages.ico"));
   // connects
    connect(pbSendMessage,SIGNAL(clicked()),SLOT(on_pbSendMessage_clicked()));
    connect(messagesList,&CUpgradeListWidget::rightButtonClicked,this,&CChatWithUserView::on_rightButtonClicked);
    connect(actionCheckHash,&QAction::triggered,this,&CChatWithUserView::on_actionCheckHash_triggered);
    connect(actionCheckDigitalSignature,&QAction::triggered,this,&CChatWithUserView::on_actionCheckDigitalSignature_triggered);
}

CChatWithUserView::~CChatWithUserView(){
    delete mathWorker;
}

void CChatWithUserView::set_user_name_from(const QString &userNameFrom_){
    this->userNameFrom = userNameFrom_;
}

void CChatWithUserView::set_user_name_to(const QString &userNameTo_){
    this->userNameTo = userNameTo_;
    gbMessages->setTitle(QString("Чат с %1").arg(this->userNameTo));
}

void CChatWithUserView::set_close_keys(const CCloseKeys &closeKeys_){
    this->closeKeys = closeKeys_;
}

void CChatWithUserView::update_close_keys(const CCloseKeys &closeKeys_){
    this->closeKeys = closeKeys_;
}

QString CChatWithUserView::get_user_name_to() const{
    return this->userNameTo;
}

void CChatWithUserView::add_new_message(const QString &userNameFrom, const QString &message, std::pair<CBigInteger, CBigInteger> &digitalSignature){
    QString finalMessage = userNameFrom + ": " + message;
    messagesList->addItem(finalMessage);
    messagesDigitalSignature.push_back(digitalSignature);
}

void CChatWithUserView::add_user_keys(const QString &userName, const COpenKeys &key){
    userKeys[userName] = key;
}

void CChatWithUserView::delete_user_keys(const QString &userName){
    userKeys.remove(userName);
}

void CChatWithUserView::on_pbSendMessage_clicked(){
    QString message = teMessage->toPlainText();
    if (message.size() == 0){
        QMessageBox::critical(this,"Ошибка","Сообщение не должно быть пустым!");
        return;
    }
    if (this->closeKeys.get_q() == -1){
        QMessageBox::critical(this,"Ошибка","Вы не можете подписать и отправить сообщение, без генерации ключей!");
        return;
    }
    std::pair <CBigInteger,CBigInteger> digitalSignature = {};
    this->add_new_message(this->userNameFrom,message,digitalSignature);
    teMessage->setPlainText("");
    QString finalMessage = this->userNameFrom + ": " + message;
    QString messageHash = hashFunction->get_hash_from_string(finalMessage);
    teHash->setPlainText(messageHash);
    digitalSignature = mathWorker->generate_digital_signature(this->closeKeys,messageHash);
    emit send_message(message,userNameTo,digitalSignature);
}

void CChatWithUserView::on_actionCheckHash_triggered(){
    QModelIndex index = messagesList->currentIndex();
    if (!index.isValid()) return;
    QString message = messagesList->model()->index(index.row(),0).data().toString();
    QString messageHash = hashFunction->get_hash_from_string(message);
    QMessageBox messageBox;
    messageBox.setWindowIcon(this->windowIcon());
    messageBox.setWindowTitle("Хеш-сумма");
    messageBox.setIcon(QMessageBox::Question);
    messageBox.setText(messageHash);
    messageBox.setFont(QFont("Times",10));
    messageBox.setStyleSheet("QLabel{"
                             "color: red;"
                             "font: bold;}");
    messageBox.exec();
}

void CChatWithUserView::on_actionCheckDigitalSignature_triggered(){
    QModelIndex index = messagesList->currentIndex();
    if (!index.isValid()) return;
    QString message = messagesList->model()->index(index.row(),0).data().toString();
    QString messageHash = hashFunction->get_hash_from_string(message);
    QString userName = "";
    for (auto& ch : message){
        if (ch == ":") break;
        userName += ch;
    }
    std::pair <CBigInteger,CBigInteger> digitalSignature = messagesDigitalSignature[index.row()];
    if (userKeys.find(userName) == userKeys.end()){
        QMessageBox::critical(this,"Ошибка","Невозможно проверить цифровую подпись, т.к. пользователь не поделился своим открытом ключом!");
        return;
    }
    COpenKeys userOpenKeys = userKeys[userName];
    if (mathWorker->check_digital_signature(digitalSignature,userOpenKeys,messageHash)){
        QMessageBox::information(this,"Успех","Подпись верна!");
    }
    else{
        QMessageBox::critical(this,"Ошибка","Подпись не верна!");
    }
}

void CChatWithUserView::on_rightButtonClicked(int X, int Y){
    QModelIndex index = messagesList->currentIndex();
    if (!index.isValid()) return;
    QString message = messagesList->model()->index(index.row(),0).data().toString();
    QString userName = "";
    for (auto& ch : message){
        if (ch == ":") break;
        userName += ch;
    }
    if (userNameFrom == userName) return;
    menu->setGeometry(X,Y,320,60);
    menu->show();
}
