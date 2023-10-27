#include "course_set.h"
#include "ui_course_set.h"

course_set::course_set(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::course_set)
{
    ui->setupUi(this);
}

course_set::~course_set()
{
    delete ui;
}

void course_set::on_newsc_clicked()
{
    QString cno;
    QString cname;
    QString cpno;
    QString credit;
    cno=ui->lineEdit->text();
    cname=ui->lineEdit_2->text();
    cpno=ui->lineEdit_3->text();
    credit=ui->lineEdit_4->text();
    emit new_course(cno,cname,cpno,credit);
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
}


void course_set::on_delsc_clicked()
{
    emit del_course(ui->lineEdit_5->text());
    ui->lineEdit_5->clear();
}


void course_set::on_recname_clicked()
{
    QString cno;
    QString cname;
    cno=ui->lineEdit_6->text();
    cname=ui->lineEdit_7->text();
    emit rcname_course(cno,cname);
    ui->lineEdit_7->clear();
}


void course_set::on_recpno_clicked()
{
    QString cno;
    QString cpno;
    cno=ui->lineEdit_6->text();
    cpno=ui->lineEdit_7->text();
    emit rcpno_course(cno,cpno);
    ui->lineEdit_7->clear();
}


void course_set::on_recredit_clicked()
{
    QString cno;
    QString credit;
    cno=ui->lineEdit_6->text();
    credit=ui->lineEdit_7->text();
    emit rcredit_course(cno,credit);
    ui->lineEdit_7->clear();
}

