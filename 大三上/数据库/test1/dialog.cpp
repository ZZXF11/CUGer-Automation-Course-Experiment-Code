#include "dialog.h"
#include "ui_dialog.h"
QString in;
QString in1;
QString in2;
QString in3;
QString in4;

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui_1(new Ui::Dialog)
{
    ui_1->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui_1;
}

void Dialog::on_save_clicked()
{
    in1="";
    in2="";
    in3="";
    in4="";
    in="";
    in=ui_1->lineEdit->text();
    in1=ui_1->lineEdit_2->text();
    in2=ui_1->lineEdit_3->text();
    in3=ui_1->lineEdit_4->text();
    in4=ui_1->lineEdit_7->text();
    ui_1->lineEdit->clear();
    ui_1->lineEdit_2->clear();
    ui_1->lineEdit_3->clear();
    ui_1->lineEdit_4->clear();
    ui_1->lineEdit_7->clear();


    if(in!=""&&in1!=""&&in2!=""&&in3!=""&&in4!="")
    {
        QSqlQuery qr;
        qr.prepare("insert into student(sno,sname,ssex,sage,Sdept)"
                      "values(?,?,?,?,?)");
        qr.bindValue(0,in);
        qr.bindValue(1,in1);
        qr.bindValue(2,in2);
        qr.bindValue(3,in4);
        qr.bindValue(4,in3);
        qr.exec();
     }




}


void Dialog::on_save_3_clicked()
{
    in1="";
    in2="";
    in3="";
    //in4="";
    in="";
    in=ui_1->lineEdit_15->text();
    in1=ui_1->lineEdit_14->text();
    in2=ui_1->lineEdit_13->text();
    in3=ui_1->lineEdit_17->text();
    //in4=ui_1->lineEdit_7->text();
    ui_1->lineEdit_15->clear();
    ui_1->lineEdit_14->clear();
    ui_1->lineEdit_13->clear();
    ui_1->lineEdit_17->clear();
    //ui_1->lineEdit_7->clear();


    if(in!=""&&in1!=""&&in2!=""&&in3!="")
    {
        QSqlQuery qr;
        qr.prepare("insert into course(cno,cname,cpno,ccredit)"
                      "values(?,?,?,?)");
        qr.bindValue(0,in);
        qr.bindValue(1,in2);
        qr.bindValue(2,in1);
        qr.bindValue(3,in3);
       // qr.bindValue(4,in3);
        qr.exec();
     }

}


void Dialog::on_save_10_clicked()
{
    in1="";
    in2="";
    //in3="";
    //in4="";
    in="";
    in=ui_1->lineEdit_26->text();
    in1=ui_1->lineEdit_27->text();
    in2=ui_1->lineEdit_39->text();
    //in3=ui_1->lineEdit_17->text();
    //in4=ui_1->lineEdit_7->text();
    ui_1->lineEdit_26->clear();
    ui_1->lineEdit_27->clear();
    ui_1->lineEdit_39->clear();
    //ui_1->lineEdit_17->clear();
    //ui_1->lineEdit_7->clear();


    if(in!=""&&in1!=""&&in2!="")
    {
        QSqlQuery qr;
        qr.prepare("insert into sc(sno,cno,grade)"
                      "values(?,?,?)");
        qr.bindValue(0,in);
        qr.bindValue(1,in1);
        qr.bindValue(2,in2);
        //qr.bindValue(3,in3);
       // qr.bindValue(4,in3);
        qr.exec();
     }
}

