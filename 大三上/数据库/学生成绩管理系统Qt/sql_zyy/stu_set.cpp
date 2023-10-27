#include "stu_set.h"
#include "ui_stu_set.h"

stu_set::stu_set(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::stu_set)
{
    ui->setupUi(this);
}

stu_set::~stu_set()
{
    delete ui;
}

void stu_set::on_new_stu_clicked()
{
    QString Sno;
    QString Sname;
    QString Ssex;
    QString Sage;
    QString Sdept;
    Sno=ui->lineEdit->text();
    Sname=ui->lineEdit_2->text();
    Ssex=ui->lineEdit_3->text();
    Sage=ui->lineEdit_4->text();
    Sdept=ui->lineEdit_5->text();
    emit new_student(Sno,Sname,Ssex,Sage,Sdept);
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();

}


void stu_set::on_pushButton_clicked()
{
    emit del_student(ui->lineEdit_6->text());
    ui->lineEdit_6->clear();

}


void stu_set::on_rename_clicked()
{
    QString Sno;
    QString Sname;
    Sno=ui->lineEdit_7->text();
    Sname=ui->lineEdit_8->text();
    emit rename_stu(Sno,Sname);
    ui->lineEdit_8->clear();

}


void stu_set::on_reage_clicked()
{
    QString Sno;
    QString Sage;
    Sno=ui->lineEdit_7->text();
    Sage=ui->lineEdit_8->text();
    emit reage_stu(Sno,Sage);
    ui->lineEdit_8->clear();

}


void stu_set::on_resex_clicked()
{
    QString Sno;
    QString Ssex;
    Sno=ui->lineEdit_7->text();
    Ssex=ui->lineEdit_8->text();
    emit resex_stu(Sno,Ssex);
    ui->lineEdit_8->clear();

}


void stu_set::on_redept_clicked()
{
    QString Sno;
    QString Sdept;
    Sno=ui->lineEdit_7->text();
    Sdept=ui->lineEdit_8->text();
    emit redept_stu(Sno,Sdept);
    ui->lineEdit_8->clear();
}

