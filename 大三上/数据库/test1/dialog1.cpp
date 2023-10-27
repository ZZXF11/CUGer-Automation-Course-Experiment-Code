#include "dialog1.h"
#include "ui_dialog1.h"



Dialog1::Dialog1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog1)
{
    ui->setupUi(this);
}

Dialog1::~Dialog1()
{
    delete ui;
}

void Dialog1::on_pushButton_clicked()
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


void Dialog1::on_delete_sure_clicked()
{
     in="";
     in=ui->lineEdit->text();
     QSqlQuery qr;
     qr.prepare("delete from student where sno = ?");
     qr.addBindValue(in);
     qr.exec();
     lookqrModel= new QSqlQueryModel(this);

     //qr.prepare("select * from student where sno = ?");
     //qr.addBindValue(in);
     //qr.exec();
     lookqrModel->setQuery(qr);
     ui->tableView->setModel(lookqrModel);

}


void Dialog1::on_pushButton_2_clicked()
{
    in="";
    lookqrModel= new QSqlQueryModel(this);
    in=ui->lineEdit_2->text();
        QString cname=in;
        QSqlQuery qr;
        qr.prepare("select * from course where cname = ?");
        qr.addBindValue(cname);
        qr.exec();
        lookqrModel->setQuery(qr);
        ui->tableView_2->setModel(lookqrModel);

}


void Dialog1::on_delete_sure_2_clicked()
{
    in="";
    in=ui->lineEdit_2->text();
    QSqlQuery qr;
    qr.prepare("delete from course where cname = ?");
    qr.addBindValue(in);
    qr.exec();
    lookqrModel= new QSqlQueryModel(this);

    //qr.prepare("select * from student where sno = ?");
    //qr.addBindValue(in);
    //qr.exec();
    lookqrModel->setQuery(qr);
    ui->tableView_2->setModel(lookqrModel);
}


void Dialog1::on_pushButton_3_clicked()
{
    in="";
    lookqrModel= new QSqlQueryModel(this);
    in=ui->lineEdit_3->text();
        QString sno=in;
        QSqlQuery qr;
        qr.prepare("select * from sc where sno = ?");
        qr.addBindValue(sno);
        qr.exec();
        lookqrModel->setQuery(qr);
        ui->tableView_3->setModel(lookqrModel);
}


void Dialog1::on_delete_sure_3_clicked()
{
    in="";
    in=ui->lineEdit_3->text();
    QSqlQuery qr;
    qr.prepare("delete from sc where cname = ?");
    qr.addBindValue(in);
    qr.exec();
    lookqrModel= new QSqlQueryModel(this);

    //qr.prepare("select * from student where sno = ?");
    //qr.addBindValue(in);
    //qr.exec();
    lookqrModel->setQuery(qr);
    ui->tableView_3->setModel(lookqrModel);
}

