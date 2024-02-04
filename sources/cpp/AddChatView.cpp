#include "AddChatView.h"

CAddChatView::CAddChatView(CMessengerModel *messModel_, QWidget *parent) : QFrame(parent){
    mainBox = new QVBoxLayout();
    gbUsersLayout = new QVBoxLayout();
    buttonsBox = new QHBoxLayout();
    gbUsers = new QGroupBox("Выберите пользователя");
    gbUsers->setStyleSheet("QGroupBox{"
                           "font: bold;"
                           "color: purple;"
                           "border: 1px solid silver;"
                           "border-radius: 30px;"
                           "margin-top: 6px; }"
                           "QGroupBox::title{"
                           "subcontrol-origin: margin;"
                           "left: 7px;"
                           "padding: 0px 5px 0px 5px;}");
    gbUsers->setFont(QFont("Times",10));
    pbChoise = new QPushButton("Создать");
    pbChoise->setStyleSheet("QPushButton{"
                            "border:none;"
                            "color: white;"
                            "font: bold;"
                            "background-color: QLinearGradient(x1: 1, y1: 0, x2: 0, y2: 1,stop: 0 #00FA9A,stop: 0.4999 #00FA9A,stop: 0.5 #00FA9A,stop: 1 #238);"
                            "border-radius: 15px}"
                            "QPushButton:hover{"
                            "background-color: QLinearGradient(x1: 1, y1: 0, x2: 0, y2: 1,stop: 0 #87CEFA,stop: 0.4999 #BA55D3,stop: 0.5 #BA55D3,stop: 1 #238);}"
                            "QPushButton:disabled{"
                            "background-color: QLinearGradient(x1: 1, y1: 0, x2: 0, y2: 1,stop: 0 #E83812,stop: 0.4999 #E83812,stop: 0.5 #E83812,stop: 1 #238);}"
                            "QPushButton:pressed{"
                            "background-color: QLinearGradient(x1: 1, y1: 0, x2: 0, y2: 1,stop: 0 #DA70D6,stop: 0.4999 #FFF0F5,stop: 0.5 #FFF0F5,stop: 1 #238);}");
    pbChoise->setFixedSize(250,50);
    pbChoise->setFont(QFont("Times",10));
    listView = new QListView();
    listView->setStyleSheet("QListView{"
                             "color: black;}");
    this->messModel = messModel_;
    listView->setFont(QFont("Times",10));
    listView->setSelectionMode(QAbstractItemView::SingleSelection);
    listView->setModel(messModel);
    gbUsersLayout->addWidget(listView);
    gbUsers->setLayout(gbUsersLayout);
    buttonsBox->setAlignment(Qt::AlignRight);
    buttonsBox->addWidget(pbChoise);
    mainBox->addWidget(gbUsers);
    mainBox->addLayout(buttonsBox);
    this->setLayout(mainBox);
    this->setFont(QFont("Times",10));
    this->setFixedSize(500,600);
    this->setGeometry(QStyle::alignedRect(Qt::LeftToRight,Qt::AlignCenter,this->size(),QApplication::desktop()->availableGeometry()));
    this->setWindowTitle("Новый чат");
    this->setWindowIcon(QIcon(":/icons/appGraphic/addChat.ico"));
   // connects
    connect(pbChoise,SIGNAL(clicked()),SLOT(on_pbChoise_clicked()));
}

void CAddChatView::on_pbChoise_clicked(){
    this->close();
    QModelIndex index = listView->currentIndex();
    QString userNameWith = messModel->get_user(index.row())->get_name();
    emit chat_choised(userNameWith);
}
