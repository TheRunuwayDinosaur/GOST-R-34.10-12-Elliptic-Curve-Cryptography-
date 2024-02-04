#include "KeysView.h"

CKeysView::CKeysView(QWidget *parent) : QFrame(parent){
    mainBox = new QVBoxLayout();
    buttonsBox = new QHBoxLayout();
    formBox = new QFormLayout();
    mathWorker = new CMathWorker();
    lbP = new QLabel("p: ");
    lbP->setFont(QFont("Times",10));
    lbP->setStyleSheet("font: bold;"
                              "color: purple;");
    lbQ = new QLabel("q: ");
    lbQ->setFont(QFont("Times",10));
    lbQ->setStyleSheet("font: bold;"
                              "color: purple;");
    lbA = new QLabel("A: ");
    lbA->setFont(QFont("Times",10));
    lbA->setStyleSheet("font: bold;"
                              "color: purple;");
    lbB = new QLabel("B: ");
    lbB->setFont(QFont("Times",10));
    lbB->setStyleSheet("font: bold;"
                              "color: purple;");
    lbEllipticP = new QLabel("P{}: ");
    lbEllipticP->setFont(QFont("Times",10));
    lbEllipticP->setStyleSheet("font: bold;"
                              "color: purple;");
    lbEllipticQ = new QLabel("Q{}: ");
    lbEllipticQ->setFont(QFont("Times",10));
    lbEllipticQ->setStyleSheet("font: bold;"
                              "color: purple;");
    leP = new QTextEdit();
    leP->setFont(QFont("Times",10));
    leP->setStyleSheet("color: black; font: bold");
    leP->setEnabled(false);
    leQ = new QTextEdit();
    leQ->setFont(QFont("Times",10));
    leQ->setStyleSheet("color: black; font: bold");
    leQ->setEnabled(false);
    leA = new QTextEdit();
    leA->setFont(QFont("Times",10));
    leA->setStyleSheet("color: black; font: bold");
    leA->setEnabled(false);
    leB = new QTextEdit();
    leB->setFont(QFont("Times",10));
    leB->setStyleSheet("color: black; font: bold");
    leB->setEnabled(false);
    leEllipticP = new QTextEdit();
    leEllipticP->setFont(QFont("Times",10));
    leEllipticP->setStyleSheet("color: black; font: bold");
    leEllipticP->setEnabled(false);
    leEllipticQ = new QTextEdit();
    leEllipticQ->setFont(QFont("Times",10));
    leEllipticP->setStyleSheet("color: black; font: bold");
    leEllipticQ->setEnabled(false);
    leEllipticQ->setStyleSheet("color: black; font: bold");
    pbGenerateKeys = new QPushButton("Сгенерировать ключи");
    pbGenerateKeys->setStyleSheet("QPushButton{"
                             "border:none;"
                             "color: white;"
                             "font: bold;"
                             "background-color: QLinearGradient(x1: 1, y1: 0, x2: 0, y2: 1,stop: 0 #00FA9A,stop: 0.4999 #00FA9A,stop: 0.5 #00FA9A,stop: 1 #238);"
                             "border-radius: 15px;}"
                             "QPushButton:hover{"
                             "background-color: QLinearGradient(x1: 1, y1: 0, x2: 0, y2: 1,stop: 0 #87CEFA,stop: 0.4999 #BA55D3,stop: 0.5 #BA55D3,stop: 1 #238);}"
                             "QPushButton:disabled{"
                             "background-color: QLinearGradient(x1: 1, y1: 0, x2: 0, y2: 1,stop: 0 #E83812,stop: 0.4999 #E83812,stop: 0.5 #E83812,stop: 1 #238);}"
                             "QPushButton:pressed{"
                             "background-color: QLinearGradient(x1: 1, y1: 0, x2: 0, y2: 1,stop: 0 #DA70D6,stop: 0.4999 #FFF0F5,stop: 0.5 #FFF0F5,stop: 1 #238);}");
    pbGenerateKeys->setFont(QFont("Times",10));
    pbGenerateKeys->setFixedSize(250,50);
    pbPublishKeys = new QPushButton("Опубликовать ключи");
    pbPublishKeys->setStyleSheet("QPushButton{"
                             "border:none;"
                             "color: white;"
                             "font: bold;"
                             "background-color: QLinearGradient(x1: 1, y1: 0, x2: 0, y2: 1,stop: 0 #00FA9A,stop: 0.4999 #00FA9A,stop: 0.5 #00FA9A,stop: 1 #238);"
                             "border-radius: 15px;}"
                             "QPushButton:hover{"
                             "background-color: QLinearGradient(x1: 1, y1: 0, x2: 0, y2: 1,stop: 0 #87CEFA,stop: 0.4999 #BA55D3,stop: 0.5 #BA55D3,stop: 1 #238);}"
                             "QPushButton:disabled{"
                             "background-color: QLinearGradient(x1: 1, y1: 0, x2: 0, y2: 1,stop: 0 #E83812,stop: 0.4999 #E83812,stop: 0.5 #E83812,stop: 1 #238);}"
                             "QPushButton:pressed{"
                             "background-color: QLinearGradient(x1: 1, y1: 0, x2: 0, y2: 1,stop: 0 #DA70D6,stop: 0.4999 #FFF0F5,stop: 0.5 #FFF0F5,stop: 1 #238);}");
    pbPublishKeys->setFont(QFont("Times",10));
    pbPublishKeys->setFixedSize(250,50);
    formBox->addRow(lbP,leP);
    formBox->addRow(lbQ,leQ);
    formBox->addRow(lbA,leA);
    formBox->addRow(lbB,leB);
    formBox->addRow(lbEllipticP,leEllipticP);
    formBox->addRow(lbEllipticQ,leEllipticQ);
    buttonsBox->setAlignment(Qt::AlignRight);
    buttonsBox->addWidget(pbPublishKeys);
    buttonsBox->addSpacing(50);
    buttonsBox->addWidget(pbGenerateKeys);
    mainBox->addLayout(formBox);
    mainBox->addLayout(buttonsBox);
    this->setLayout(mainBox);
    this->setFont(QFont("Times",10));
    this->resize(600,590);
    this->setGeometry(QStyle::alignedRect(Qt::LeftToRight,Qt::AlignCenter,this->size(),QApplication::desktop()->availableGeometry()));
    // connects
    connect(pbGenerateKeys,SIGNAL(clicked()),SLOT(on_pbGenerateKeys_clicked()));
    connect(pbPublishKeys,SIGNAL(clicked()),SLOT(on_pbPublishKeys_clicked()));

}

CKeysView::~CKeysView(){
    delete mathWorker;
}

CCloseKeys CKeysView::get_close_keys() const{
    return CCloseKeys(this->p,this->q,this->ellipticP,this->ellipticQ,this->d);
}

CBigInteger CKeysView::get_p() const{
    return this->p;
}

CBigInteger CKeysView::get_q() const{
    return this->q;
}

CEllipticPoint CKeysView::get_ellipticP() const{
    return this->ellipticP;
}

CEllipticPoint CKeysView::get_ellipticQ() const{
    return this->ellipticQ;
}

CBigInteger CKeysView::get_d() const{
    return this->d;
}

void CKeysView::generate_primes(int cnt){
    for (int i = 0;i < cnt;i++){
        CPrimesGeneratorThread *th = new CPrimesGeneratorThread();
        ths.push_back(th);
        connect(ths.back(),&CPrimesGeneratorThread::prime_generated,this,&CKeysView::on_prime_generated,Qt::QueuedConnection);
        ths.back()->start();
    }
}

void CKeysView::generate_all_keys(){
    ellipticP = mathWorker->generate_elliptic_point(p,A,B);
    ellipticP.set_p(p); ellipticP.set_A(A); ellipticP.set_B(B);
    d = mathWorker->generate_random_number(2,q.get_number().toLongLong() - 1);
    ellipticQ = ellipticP * d;
    while(ellipticQ.get_x() == 0){
        d = mathWorker->generate_random_number(2,q.get_number().toLongLong() - 1);
        ellipticQ = ellipticP * d;
    }
    ellipticQ.set_A(A); ellipticQ.set_B(B); ellipticQ.set_p(p);
    //
    leP->setText(p.get_number());
    leQ->setText(q.get_number());
    leA->setText(A.get_number());
    leB->setText(B.get_number());
    leEllipticP->setText(QString("{%1;%2}").arg(ellipticP.get_x().get_number()).arg(ellipticP.get_y().get_number()));
    leEllipticQ->setText(QString("{%1;%2}").arg(ellipticQ.get_x().get_number()).arg(ellipticQ.get_y().get_number()));
    emit close_keys_generated();
}

void CKeysView::on_prime_generated(QString prime){
    CBigInteger result(prime.toStdString().c_str());
    bigPrimes.push_back(result);
    QVector <int> needDeleteTh;
    for (int i = 0;i < ths.size();i++){
        if (ths[i]->isFinished()){
            needDeleteTh.push_back(i);
        }
        else ths[i]->blockSignals(true);
    }
    for (auto& th : needDeleteTh){
        delete ths[th];
        ths.remove(th);
    }
    if (bigPrimes.size() == needPrimes){
        loadingView->close();
        this->setEnabled(true);
        delete loadingView;
        p = bigPrimes.front();
        while(ths.size() > 0){
            disconnect(ths.back(),&CPrimesGeneratorThread::prime_generated,this,&CKeysView::on_prime_generated);
            delete ths.back();
            ths.pop_back();
        }
        this->generate_all_keys();
    }
    for (int i = 0;i < ths.size();i++) ths[i]->blockSignals(false);
}

void CKeysView::on_pbGenerateKeys_clicked(){
    this->bigPrimes.clear();
    this->setEnabled(false);
    loadingView = new CLoadingView();
    loadingView->show();
//    this->generate_primes(needPrimes);
    keysGenerator = new CKeysGenThread();
    connect(keysGenerator,&CKeysGenThread::keys_generated,this,&CKeysView::on_keys_generated);
    keysGenerator->start();
}

void CKeysView::on_pbPublishKeys_clicked(){
    if (this->p == 0){
        QMessageBox::critical(this,"Ошибка","Перед отправкой нужно сгенерировать ключи!");
        return;
    }
    this->setEnabled(false);
    COpenKeys openKeys;
    openKeys.set_q(this->q);
    openKeys.set_ellipticP(this->ellipticP);
    openKeys.set_ellipticQ(this->ellipticQ);
    emit publish_keys_to_user(openKeys);
}

void CKeysView::on_keys_generated(QString p, QString A, QString B, QString q){
    loadingView->close();
    this->setEnabled(true);
    delete loadingView;
    if (keysGenerator->isFinished()){
        disconnect(keysGenerator,&CKeysGenThread::keys_generated,this,&CKeysView::on_keys_generated);
        delete keysGenerator;
    }
    this->p.set_number(p.toStdString().c_str()); this->A.set_number(A.toStdString().c_str());
    this->B.set_number(B.toStdString().c_str()); this->q.set_number(q.toStdString().c_str());
    this->generate_all_keys();
}
