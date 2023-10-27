#include "sc_set.h"
#include "ui_sc_set.h"

sc_set::sc_set(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sc_set)
{
    ui->setupUi(this);
}

sc_set::~sc_set()
{
    delete ui;
}

void sc_set::on_new_sc_clicked()
{
    QString sno;
    QString cno;
    QString grade;
    sno=ui->lineEdit->text();
    cno=ui->lineEdit_2->text();
    grade=ui->lineEdit_3->text();
    emit new_sc(sno,cno,grade);
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
}


void sc_set::on_del_sc_clicked()
{
    QString sno;
    QString cno;
    sno=ui->lineEdit_4->text();
    cno=ui->lineEdit_5->text();
    emit del_sc(sno,cno);
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
}


void sc_set::on_cha_sc_clicked()
{
    QString sno;
    QString cno;
    QString grade;
    sno=ui->lineEdit_6->text();
    cno=ui->lineEdit_7->text();
    grade=ui->lineEdit_8->text();
    emit cha_sc(sno,cno,grade);//发送
    ui->lineEdit_6->clear();
    ui->lineEdit_7->clear();
    ui->lineEdit_8->clear();
}

