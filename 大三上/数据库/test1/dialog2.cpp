#include "dialog2.h"
#include "ui_dialog2.h"

Dialog2::Dialog2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog2)
{
    ui->setupUi(this);
}

Dialog2::~Dialog2()
{
    delete ui;
}

void Dialog2::on_pushButton_clicked()
{
    in="";
    lookqrModel= new QSqlQueryModel(this);
    in=ui->lineEdit->text();
        QString sno=in;
        QSqlQuery qr;
        qr.prepare("select * from student where sno = ?");
        qr.addBindValue(sno);
        qr.exec();
        lookqrModel->setQuery(qr);
        ui->tableView->setModel(lookqrModel);
}

