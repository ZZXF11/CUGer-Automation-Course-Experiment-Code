#include "load.h"
#include "ui_load.h"
#include <QMessageBox>
QString flag_log="0";

load::load(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::load)
{
    ui->setupUi(this);
}

load::~load()
{
    delete ui;
}

void load::on_pushButton_clicked()
{
    QString uname;
    QString password;
    uname=ui->lineEdit->text();
    password=ui->lineEdit_2->text();
    if(uname == "root" && password =="123"){
        flag_log="1";

    }
    else if(uname == "stu" && password =="123"){
        flag_log="2";
    }
    else{
        flag_log="0";
        log->show();
    }
    emit man_mode(flag_log);
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
}

